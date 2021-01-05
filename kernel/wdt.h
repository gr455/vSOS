#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../drivers/vga.h"
#include "utils.h"
#include "isr.h"
#include "panic.h"

void init_timer(uint32_t freq);
static void timer_callback(isr_reg_t regs);
void cpu_watchdog_triggered();
void reset_watchdog(uint32_t cutoff);
void init(uint8_t level);

#endif