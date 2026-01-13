#pragma once

#include "../../libc/util_types.h"
#include "page_directory.h"
#include "../mmu/frame_controller.h"

#define MAXPAGES 1024

// bitset to track used pages.
// TODO: make this more representative.
// Per process tracking is TODO. kpg will still need to always be mapped though.
// Even through context transfer to kernel, kernel will need to keep cr3 of process
// and still access kpg.

// each int32 tracks 32 pages. So 1024 / 32 int32s for 1024 pages.
extern uint32_t kpg_presentbits[MAXPAGES / 32];

// kpg_presentbits maps to physical pages starting from heap_start + FRAMECTL_KPG_START_FRAME_OFFSET
extern uint32_t FRAMECTL_KPG_START_FRAME_OFFSET;


// extern page_directory_t kpd __attribute__((aligned(4096)));
extern uint32_t _start;

void pgctl_init();
// void pgctl_alloc_and_map(uint32_t virt, page_directory_t* pd);
// uint32_t pgctl_alloc_pages(uint32_t k, bool use_cr3);
extern void set_paging_enable(uint32_t kpd_phys_addr);
// uint32_t pgctl_free_pages(uint32_t virt, uint32_t k);
uint32_t kmalloc(size_t size);
void kfree(uint32_t addr, size_t size);

// test

void __test__k_setmem(uint32_t vaddr, char value);
char __test__k_getmem(uint32_t vaddr);