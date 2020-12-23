#ifndef VGA_H
#define VGA_H

#include "../kernel/ports.h"

#define VGA_CTRL 0x3d4
#define VGA_DATA 0x3d5
#define XMAX 80
#define YMAX 25

void vga_set_chr(unsigned char chr, unsigned char attr);
unsigned int make_offset(int row, int col);
unsigned int get_crsr();
void set_crsr(unsigned int offset);
void vga_clr();
unsigned int handle_scroll(unsigned int offset);

#endif