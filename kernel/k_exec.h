#ifndef KEXEC_H
#define KEXEC_H

#include "ports.h"
#include "utils.h"
#include "panic.h"
#include "../libc/stdio.h"
#include "isr.h"
#include "../drivers/keyboard.h"
#include "vsh.h"
#include "wdt.h"
#include "mmu/frame_controller.h"
#include "paging/page_controller.h"
#include "task/task.h"

void init(uint8_t mode);

#endif