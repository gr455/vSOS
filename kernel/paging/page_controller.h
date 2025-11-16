#pragma once

#include "../../libc/util_types.h"
#include "page_directory.h"
#include "../mmu/frame_controller.h"


page_directory_t kpd;

void pgctl_init();