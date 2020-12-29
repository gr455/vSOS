#include "ports.h"
#include "utils.h"
#include "panic.h"
#include "../libc/stdio.h"
#include "isr.h"

void k_main(){

	init_isr();

	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	printsln("vSOS:/home > ");
	__asm__ __volatile__ ("int $2");
	// panic("fatal: attempt to kill init");
}	