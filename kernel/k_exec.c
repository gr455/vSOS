#include "k_exec.h"

void init(uint8_t mode);
void norace(uint8_t h);

extern unsigned char __bss_start;
extern unsigned char __bss_end;
extern uint16_t kb_popper;
extern uint16_t kb_pusher;
extern uint16_t kb_buff_size;
extern char keybuff[256];


void k_main(){
	printsln("Boot OK");
	init(1);
	printsln("init 1 finished. Wait 100ms");
	stall_time(100);
	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	irq_unmsk();
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
			__asm__ __volatile__("cli");
			init_isr();
			printsln("ISRs OK");
			init_keyboard();
			printsln("Keyboard OK");
			init_timer(50);
			reset_watchdog(100);
			printsln("Timer OK");
			printsln("");
			__asm__ __volatile__("sti");
			break;
	}

}


void zero_bss() {
	// return;
    unsigned char *p = (unsigned char *) &__bss_start;
    unsigned char *end = (unsigned char *) &__bss_end;
    
	while (p < end) {
		*p++ = 0;
	}
}