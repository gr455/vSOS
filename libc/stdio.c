#include "stdio.h"

void mprints(char * s, unsigned int length){
	int i = 0;
	while(i < length) vga_set_chr(s[i++], 0xf);
}

void prints(char * s){
	unsigned int i = 0;
	while(s[i]) vga_set_chr(s[i++], 0xf);
}

void printsln(char * s){
	unsigned int i = 0;
	while(s[i]) vga_set_chr(s[i++], 0xf);
	vga_set_chr('\n', 0xf);
}

void printe(char * e){
	unsigned int i = 0;
	while(e[i]) vga_set_chr(e[i++], 0xc);
}

void clrscr(){
	vga_clr();
}