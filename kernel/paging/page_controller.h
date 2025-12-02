#pragma once

#include "../../libc/util_types.h"
#include "page_directory.h"
#include "../mmu/frame_controller.h"

extern page_directory_t kpd __attribute__((aligned(4096)));;
extern uint32_t _start;

void pgctl_init();
extern void set_paging_enable(uint32_t kpd_phys_addr);