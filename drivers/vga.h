#ifndef VGA_H
#define VGA_H

#include "../kernel/ports.h"
#include "../kernel/utils.h"
#include "../libc/stdio.h"
#include "../libc/string.h"

#define VGA_CTRL 0x3d4
#define VGA_DATA 0x3d5
#define XMAX 80
#define YMAX 24

void vga_set_chr(unsigned char chr, unsigned char attr);
unsigned int make_offset(int row, int col);
unsigned int get_crsr();
void set_crsr(unsigned int offset);
void vga_clr();
void clr_back();
unsigned int handle_scroll(unsigned int offset);

#endif