#include "task.h"
#include "../isr.h"
#include "../panic.h"
#include "../../libc/stdio.h"
#include "../../libc/string.h"
#include "../paging/page_controller.h"
#include "../mmu/frame_controller.h"

#define MAX_TASKS 16
#define KERNEL_PID 0
#define USER_STACK_BASE 0xC0000000
#define USER_STACK_SIZE 0x10000 // 64KB per user task

// Task management structures
typedef struct {
	task_t tasks[MAX_TASKS];
	uint32_t task_count;
	uint32_t current_task_idx;
	uint32_t next_pid;
} task_manager_t;

static task_manager_t task_manager = {0};
static task_t* current_task = NULL;

// Forward declarations
extern void context_switch_asm(cpu_state_t* old_state, cpu_state_t* new_state);
extern void jump_to_task(cpu_state_t* state);

/**
 * Initialize the task manager with the kernel task
 */
void task_init() {
	memset(&task_manager, 0, sizeof(task_manager_t));
	
	// Initialize kernel task (PID 0)
	task_manager.tasks[0].pid = KERNEL_PID;
	task_manager.tasks[0].pd = NULL; // Kernel uses current page directory
	task_manager.tasks[0].presentbits = NULL;
	task_manager.tasks[0].stack_base = 0; // Kernel stack
	task_manager.task_count = 1;
	task_manager.current_task_idx = 0;
	task_manager.next_pid = 1;
	
	current_task = &task_manager.tasks[0];
	
	prints("Task manager initialized\n");
}

/**
 * Create a new user task with given entry point and argument
 * Returns PID on success, -1 on failure
 */
int32_t task_create(void (*entry_point)(uint32_t), uint32_t arg) {
	if (task_manager.task_count >= MAX_TASKS) {
		printe("task_create: MAX_TASKS reached\n");
		return -1;
	}
	
	uint32_t task_idx = task_manager.task_count;
	task_t* new_task = &task_manager.tasks[task_idx];
	
	// Assign PID
	new_task->pid = task_manager.next_pid++;
	
	// Create page directory for the task
	new_task->pd = (page_directory_t*)vmalloc(sizeof(page_directory_t));
	if (!new_task->pd) {
		printe("task_create: Failed to allocate page directory\n");
		return -1;
	}
	
	// Initialize page directory (copy kernel mappings, add user space)
	pd_init(new_task->pd);
	_task_copy_kernel_mappings(new_task->pd);
	
	// Allocate presentbits for task
	new_task->presentbits = (uint32_t*)vmalloc((MAX_TASKS * 1024) / 32 * sizeof(uint32_t));
	if (!new_task->presentbits) {
		printe("task_create: Failed to allocate presentbits\n");
		vfree((uint32_t)new_task->pd, sizeof(page_directory_t));
		return -1;
	}
	memset(new_task->presentbits, 0, (MAX_TASKS * 1024) / 32 * sizeof(uint32_t));
	
	// Allocate user stack
	uint32_t stack_addr = vmalloc(USER_STACK_SIZE);
	if (!stack_addr) {
		printe("task_create: Failed to allocate user stack\n");
		vfree((uint32_t)new_task->pd, sizeof(page_directory_t));
		vfree((uint32_t)new_task->presentbits, (MAX_TASKS * 1024) / 32 * sizeof(uint32_t));
		return -1;
	}
	new_task->stack_base = stack_addr + USER_STACK_SIZE;
	
	// Initialize CPU state
	memset(&new_task->cpu_state, 0, sizeof(cpu_state_t));
	new_task->cpu_state.eip = (uint32_t)entry_point;
	new_task->cpu_state.esp = new_task->stack_base;
	new_task->cpu_state.ebp = new_task->stack_base;
	new_task->cpu_state.eax = arg; // Pass argument in EAX
	new_task->cpu_state.eflags = 0x200; // IF bit set (interrupts enabled)
	new_task->cpu_state.cs = 0x8; // Kernel code segment
	new_task->cpu_state.ss = 0x10; // Kernel data segment
	new_task->cpu_state.ds = 0x10;
	new_task->cpu_state.es = 0x10;
	new_task->cpu_state.fs = 0x10;
	new_task->cpu_state.gs = 0x10;
	
	task_manager.task_count++;
	
	return new_task->pid;
}

/**
 * Copy kernel memory mappings to a user task's page directory
 */
void _task_copy_kernel_mappings(page_directory_t* user_pd) {
	extern page_directory_t kpd;
	
	// Copy kernel high memory mappings (kernel space)
	// This is typically everything above 0xC0000000 or similar
	// For now, copy lower kernel mappings to allow task to run
	for (uint32_t i = 0; i < 256; i++) {
		uint32_t phys = pd_get_entry_phys_addr(&kpd, i);
		uint32_t flags = pd_get_entry_flags(&kpd, i);
		if (phys != 0) {
			pd_set_entry(user_pd, i, phys, flags);
		}
	}
}

/**
 * Get the current running task
 */
task_t* task_get_current() {
	return current_task;
}

/**
 * Get task by PID
 */
task_t* task_get_by_pid(uint32_t pid) {
	for (uint32_t i = 0; i < task_manager.task_count; i++) {
		if (task_manager.tasks[i].pid == pid) {
			return &task_manager.tasks[i];
		}
	}
	return NULL;
}

/**
 * Schedule next task (round-robin)
 * Called from timer interrupt
 */
void task_schedule() {
	if (task_manager.task_count <= 1) {
		return; // Only kernel task, no scheduling needed
	}
	
	// Save current task state is handled by interrupt handler
	
	// Move to next task (round-robin)
	task_manager.current_task_idx++;
	if (task_manager.current_task_idx >= task_manager.task_count) {
		task_manager.current_task_idx = 0;
	}
	
	current_task = &task_manager.tasks[task_manager.current_task_idx];
	
	// Switch page directory if needed (not kernel)
	if (current_task->pd != NULL) {
		extern page_directory_t* switch_cr3_ctx(page_directory_t* new_pd);
		switch_cr3_ctx(current_task->pd);
	}
}

/**
 * Yield control to next task
 */
void task_yield() {
	task_schedule();
}

/**
 * Exit current task
 */
void task_exit(uint32_t exit_code) {
	if (current_task->pid == KERNEL_PID) {
		panic("Cannot exit kernel task");
		return;
	}
	
	// Free task resources
	if (current_task->pd) {
		vfree((uint32_t)current_task->pd, sizeof(page_directory_t));
	}
	if (current_task->presentbits) {
		vfree((uint32_t)current_task->presentbits, (MAX_TASKS * 1024) / 32 * sizeof(uint32_t));
	}
	if (current_task->stack_base) {
		vfree(current_task->stack_base - USER_STACK_SIZE, USER_STACK_SIZE);
	}
	
	// Mark task as invalid
	current_task->pid = 0xFFFFFFFF;
	
	// Schedule next task
	task_schedule();
}

/**
 * Print task information (debug)
 */
void task_print_info() {
	prints("=== Task Information ===\n");
	for (uint32_t i = 0; i < task_manager.task_count; i++) {
		task_t* t = &task_manager.tasks[i];
		if (t->pid == 0xFFFFFFFF) continue;
		
		prints("PID: ");
		printi(t->pid);
		prints(" | EIP: 0x");
		printi(t->cpu_state.eip);
		prints(" | ESP: 0x");
		printi(t->cpu_state.esp);
		if (t == current_task) prints(" [RUNNING]");
		prints("\n");
	}
	prints("========================\n");
}

/**
 * Get number of active tasks
 */
uint32_t task_get_count() {
	return task_manager.task_count;
}

/**
 * Get current task PID
 */
uint32_t task_get_pid() {
	return current_task ? current_task->pid : -1;
}
