#include "panic.h"

void panic(char * panicstr){
	clrscr();
	printe("kernel panic: ");
	printe(panicstr);
	printe("\n");
	printe("Halting cpu. please restart the system");
	// idle();
	init(0);
}