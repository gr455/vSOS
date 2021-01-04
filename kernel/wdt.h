#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../drivers/vga.h"
#include "utils.h"
#include "isr.h"

void init_timer(uint32_t freq);
static void timer_callback(isr_reg_t regs);

#endif