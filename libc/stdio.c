#include "stdio.h"

void vga_print_color(const char *s, uint8_t color) {
	unsigned int i = 0;
	while (s[i])
		vga_set_chr(s[i++], color);
}

void mprints(char *s, unsigned int length) {
	char temp[length + 1];
	for (unsigned int i = 0; i < length; i++) {
		temp[i] = s[i];
	}
	temp[length] = '\0';
	vga_print_color(temp, 0xf);
}

void prints(char *s) {
	vga_print_color(s, 0xf);
}

void printsln(char *s) {
	vga_print_color(s, 0xf);
	vga_set_chr('\n', 0xf);
}
void printe(const char *e) {          // red
	vga_print_color(e, 0xC);
}

void printeln(const char *e) {
	vga_print_color(e, 0xC);
	vga_set_chr('\n', 0xC);
}

void printsucs(const char *s) {       // green
	vga_print_color(s, 0x2);
}

void printsucsln(const char *s) {
	vga_print_color(s, 0x2);
	vga_set_chr('\n', 0x2);
}

void printinfs(const char *inf) {     // blue
	vga_print_color(inf, 0x1);
}

void printinfsln(const char *inf) {
	vga_print_color(inf, 0x1);
	vga_set_chr('\n', 0x1);
}

void printc(char c) {
	char temp[2] = {c, '\0'};
	vga_print_color(temp, 0xf);
}

// max digits = 16
void printi(int i) {
	char is[16];
	int_to_ascii(i, is);
	vga_print_color(is, 0xf);
}

void clrscr() {
	vga_clr();
}