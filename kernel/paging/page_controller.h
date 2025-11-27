#pragma once

#include "../../libc/util_types.h"
#include "page_directory.h"
#include "../mmu/frame_controller.h"


page_directory_t kpd;

void pgctl_init();
extern void set_paging_enable(uint32_t kpd_phys_addr);