/*
 * XMAX x YMAX
 */
#include "vga.h"

void vga_set_chr(unsigned char chr, unsigned char attr){
	unsigned char * vga_start = (unsigned char *) 0xb8000;
	unsigned int crsr = get_crsr();
	unsigned int offset = crsr;

	if(offset > XMAX * YMAX * 2) return;
	if(offset < 0) return;

	if(chr == '\n'){
		int rows = offset / (2 * XMAX);
		offset = make_offset(rows + 1, 0);
	}

	else{
		vga_start[offset] = chr;
		vga_start[offset+1] = attr;
		offset += 2;
	}

	offset = handle_scroll(offset);
	set_crsr(offset);
}

unsigned int make_offset(int row, int col){
	return (row * XMAX + col)*2;
}

unsigned int get_crsr(){
	// vga control register reports character offset
	port_byte_out (VGA_CTRL, 14); // take high byte
	unsigned int offset = port_byte_in (VGA_DATA) << 8; // shift
	port_byte_out (VGA_CTRL, 15); //take low byte
	offset += port_byte_in (VGA_DATA); // add
	offset *= 2; // char offset to byte offset

	return offset;
}

void set_crsr(unsigned int offset){
	offset /= 2;
	unsigned char lo = offset & 0xff;
	unsigned char hi = offset >> 8;

	port_byte_out(VGA_CTRL, 14);
    port_byte_out(VGA_DATA, hi);
    port_byte_out(VGA_CTRL, 15);
    port_byte_out(VGA_DATA, lo);
}

void vga_clr(){
	unsigned char * vga_start = (unsigned char *) 0xb8000;
	unsigned int i = 0;
	for(i; i < YMAX * XMAX * 2; i+=2){
		vga_start[i] = ' ';
		vga_start[i+1] = 0xf;
	}
	set_crsr(0);
}

unsigned int handle_scroll(unsigned int offset){
	unsigned char * vga_start = (unsigned char *) 0xb8000;
	if(offset < XMAX * YMAX * 2) return offset;
	c_memcpy((char*) 0xb8000 + 2 * XMAX,(char *) 0xb8000, XMAX*2*(YMAX - 1));
	offset = XMAX*2*(YMAX - 1);
	unsigned int i = 0;
	for(i; i < XMAX * 2; i += 2) vga_start[i + offset] = ' ';
	return offset;
}

void clr_back(){
	unsigned int crsr = get_crsr();
	if(crsr <= 0) return;
	unsigned char * vga_start = (unsigned char *) 0xb8000;
	vga_start[crsr - 2] = ' ';
	set_crsr(crsr - 2);
}