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

void k_main(){

	init(1);
	printsln("Finished boot sequence");
	stall_time(100);
	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	while(1){
		prints("");
		norace(1);
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
			break;
	}

}

void norace(uint8_t h){
	mask_keybr_intr();
	stall_time(h);
	unmask_keybr_intr();
}