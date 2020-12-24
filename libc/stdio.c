#include "stdio.h"

void mprints(char * s, unsigned int length){
	int i = 0;
	while(i < length) vga_set_chr(s[i++], 0xf);
}

void prints(char * s){
	unsigned int i = 0;
	while(s[i]) vga_set_chr(s[i++], 0xf);
}

void clrscr(){
	vga_clr();
}