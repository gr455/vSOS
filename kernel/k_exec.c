#include "k_exec.h"

void init(uint8_t mode);
void norace(uint8_t h);

extern unsigned char __bss_start;
extern unsigned char __bss_end;
extern unsigned char __kernel_heap_start;

void k_main(){
	printsucsln("Boot OK");
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
			printsucsln("ISRs OK");
			init_keyboard();
			printsucsln("Keyboard OK");
			init_timer(50);
			reset_watchdog(100);
			printsucsln("Timer OK");
			printsln("");
			fctl_init((char*)&__kernel_heap_start, 40 * 1024 * 1024); // up to 32 MiB
			printsucsln("MMU OK");
			__asm__ __volatile__("sti");
			break;
	}

}

// TODO: probably some define byte is getting overwritten here. Call this wayyyy before kernel entry.
void zero_bss() {
    unsigned char *p = (unsigned char *) &__bss_start;
    unsigned char *end = (unsigned char *) &__bss_end;
	printsucs("BSS starts at: ");
	printi((uint32_t)&__bss_start);
	printsln("");
	printsucs("BSS ends at: ");
	printi((uint32_t)&__bss_end);
	printsln("");
    
	while (p < end) {
		*p++ = 0;
	}
}