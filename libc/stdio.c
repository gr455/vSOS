#include "stdio.h"

void mprints(char * s, unsigned int length){
	for(unsigned int i = 0; i < length; i++) vga_set_chr(s[i], 0xf);
}

void prints(char * s){
	unsigned int i = 0;
	while(s[i++] != '\0') vga_set_chr(s[i - 1], 0xf);
}