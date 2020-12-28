#include "panic.h"

void panic(char * panicstr){
	clrscr();
	printe("kernel panic: ");
	printe(panicstr);
	printe("\n");
	printe("system will now reboot");
	// idle();
	// init(0);
}