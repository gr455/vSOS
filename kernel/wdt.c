/*
 * WATCHDOG TIMER
 * 
 * sourced from https://github.com/cfenollosa/os-tutorial/blob/master/20-interrupts-timer/cpu/timer.c
 */

#include "wdt.h"

uint32_t g_tick = 0;
uint32_t g_watch = 0;
uint32_t g_lim = 0;
uint8_t ticking = 0;

static void timer_callback(isr_reg_t regs) {
	reset_watchdog(10);
	if(g_tick >= 2147483646) g_tick = 0;
	if(g_watch != 0 && g_tick >= g_watch) cpu_watchdog_triggered();
	g_tick++;
}

void init_timer(uint32_t freq) {
	new_handler(0x20, timer_callback);

	/* Get the PIT value: hardware clock at 1193180 Hz */
	uint32_t divisor = 1193180 / freq;
	uint8_t low  = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)( (divisor >> 8) & 0xFF);
	/* Send the command */
	port_byte_out(0x43, 0x36); /* Command port */
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}

/* Stall CPU for ticks */
void stall_time(uint32_t ticks){
	g_lim = g_tick + ticks;
	ticking = 1;
	while(ticking){
		if(g_tick >= g_lim){
			ticking = 0;
			return;
		} 
	};
}

/* CPU is required to reset the global counter. Failing to do so must cause panic */
void reset_watchdog(uint32_t cutoff){
	g_watch = g_tick + cutoff;
}

void cpu_watchdog_triggered(){
	panic("CPU watchdog timed out, might have hung");
	init(0);
}