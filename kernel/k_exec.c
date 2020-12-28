#include "ports.h"
#include "utils.h"
#include "panic.h"
#include "../libc/stdio.h"
#include "../drivers/vga.h"

void k_main(){

	clrscr();
	printsln("                                vSOS v1.0 beta\n");
	printsln("vSOS:/home > ");
	__asm__ __volatile__ ("int $2");
	// panic("fatal: attempt to kill init");
}	