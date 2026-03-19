#pragma once

#include "../../libc/util_types.h"
#include "../paging/page_directory.h"
#include "../isr.h"

typedef struct cpu_state {
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t eip;
	uint32_t eflags;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t es;
	uint32_t fs;
	uint32_t gs;
} cpu_state_t;

typedef struct task {
	uint32_t pid;
	page_directory_t* pd; // Page directory for this task's virtual address space
	uint32_t* presentbits; // Bitset tracking allocated pages for this task
	cpu_state_t cpu_state; // Saved CPU state for context switching
    uint32_t stack_base; // Base of the task's stack
} task_t;

// Task management functions
void task_init();
int32_t task_create(void (*entry_point)(uint32_t), uint32_t arg);
task_t* task_get_current();
task_t* task_get_by_pid(uint32_t pid);
void task_schedule();
void task_yield();
void task_exit(uint32_t exit_code);
void task_print_info();
uint32_t task_get_count();
uint32_t task_get_pid();
void _task_copy_kernel_mappings(page_directory_t* user_pd);

// Assembly functions
extern void context_switch_asm(cpu_state_t* old_state, cpu_state_t* new_state);
extern void jump_to_task(cpu_state_t* state);
