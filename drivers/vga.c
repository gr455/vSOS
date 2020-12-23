/*
 * XMAX x YMAX
 */
#include "vga.h"

void vga_set_chr(unsigned char chr, unsigned char attr){
	unsigned char * vga_start = (unsigned char *) 0xb8001;
	unsigned int crsr = get_crsr();
	unsigned int offset = crsr;

	if(offset > XMAX * YMAX) return;

	if(chr == '\n'){
		int rows = offset / (2 * XMAX);
		offset = make_offset(XMAX - 1, rows) + 1;
	}

	else{
		vga_start[offset] = chr;
		vga_start[offset+1] = attr;
	}

	offset += 2;
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
	unsigned char lo = (offset << 8) >> 8;
	unsigned char hi = (offset - lo) >> 8;

	port_byte_out(VGA_CTRL, 14);
    port_byte_out(VGA_DATA, hi);
    port_byte_out(VGA_CTRL, 15);
    port_byte_out(VGA_DATA, lo);
}

void vga_clr(){
	unsigned char * vga_start = (unsigned char *) 0xb8001;
	for(unsigned int i = 0; i < YMAX * XMAX; i+=2){
		vga_start[i] = ' ';
		vga_start[i+1] = 0xf;
	}
}

unsigned int handle_scroll(unsigned int offset){
	// if(offset < XMAX * YMAX) return offset;
	// for(unsigned int i = 0; i < YMAX; i++){

	// }
	return offset;
}