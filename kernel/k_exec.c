#include "k_exec.h"

void init(uint8_t mode);
void norace(uint8_t h);

extern unsigned char __bss_start;
extern unsigned char __bss_end;
extern unsigned char __kernel_heap_start;

void k_main(){
	prints("Boot      "); printsucsln("OK");
	init(1);
	printsln("init 1 finished. Please wait...");
	stall_time(100);
	clrscr();
	printsln("                                vSOS v1.0\n");
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
			prints("ISRs      ");
			init_isr();
			printsucsln("OK");
			prints("Keyboard  ");
			init_keyboard();
			printsucsln("OK");
			prints("Timer     ");
			init_timer(50);
			reset_watchdog(100);
			printsucsln("OK");
			prints("Init framectl. heap phys: ");
			printi((uint32_t)&__kernel_heap_start);
			printsln("");
			prints("MMU       ");
			fctl_init((char*)&__kernel_heap_start + FRAMECTL_KPG_START_FRAME_OFFSET, 4 * 1024 * 1024);
			printsucsln("OK");
			prints("Paging    ");
			pgctl_init();
			printsucsln("OK");
			prints("Tasks     ");
			task_init();
			printsucsln("OK");
			printsln("");
			__asm__ __volatile__("sti");
			break;
	}

}

void zero_bss() {
    unsigned char *p = (unsigned char *) &__bss_start;
    unsigned char *end = (unsigned char *) &__bss_end;
	prints("BSS starts at: ");
	printi((uint32_t)&__bss_start);
	printsln("");
	prints("BSS ends at: ");
	printi((uint32_t)&__bss_end);
	printsln("");
	printsln("");
    
	while (p < end) {
		*p++ = 0;
	}
}