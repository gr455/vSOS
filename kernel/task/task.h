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

#endif
