#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "../drivers/vga.h"
#include "utils.h"
#include "isr.h"
#include "panic.h"
#include "k_exec.h"

void init_timer(uint32_t freq);
static void timer_callback(isr_reg_t regs);
void cpu_watchdog_triggered();
void stall_time(uint32_t ticks);
void reset_watchdog(uint32_t cutoff);

#endif