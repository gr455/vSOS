#include "ports.h"
#include "utils.h"
#include "../libc/stdio.h"
#include "../drivers/vga.h"

void main(){
	unsigned char word[] = "Hello";
	// *word = 'h';
	// *(word + 0x1) = 'e';
	// *(word + 0x2) = 'l';

	// *(word + 0x3) = 's';
	mprints(word, 5);
	// vga_set_chr(word[0],0xf);
	// vga_set_chr('e',0xf);
	// vga_set_chr('l',0xf);
	
}