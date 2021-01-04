#include "ports.h"
#include "utils.h"
#include "panic.h"
#include "../libc/stdio.h"
#include "isr.h"
#include "../drivers/keyboard.h"
#include "vsh.h"

void init(uint8_t mode);

void k_main(){

	init(1);
	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	shell();
}

void init(uint8_t level){
	switch(level){
		case 0:
			__asm__ __volatile__("hlt");
			break;
		case 1:
			__asm__ __volatile__("cli");
			init_isr();
			__asm__ __volatile__("sti");
			init_keyboard();
			break;
	}

}