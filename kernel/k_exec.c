#include "ports.h"
#include "utils.h"
#include "panic.h"
#include "../libc/stdio.h"
#include "isr.h"
#include "../drivers/keyboard.h"
#include "vsh.h"
#include "wdt.h"

void init(uint8_t mode);
void norace(uint8_t h);

extern unsigned int __bss_start;
extern unsigned int __bss_end;
extern uint16_t kb_popper;

void k_main(){
	printi(kb_popper);
	init(1);
	printsln("Finished boot sequence");
	stall_time(100);
	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	while(1){

		shell();
	}
}

void init(uint8_t level){
	switch(level){
		case 0:
			__asm__ __volatile__("hlt");
			break;
		case 1:
			init_isr();
			__asm__ __volatile__("sti");
			init_keyboard();
			init_timer(50);
			reset_watchdog(100);
			break;
	}

}

void zero_bss() {
    unsigned int *p = &__bss_start;
    unsigned int *end = &__bss_end;
    while (p < end) {
        *p++ = 0;
    }
}