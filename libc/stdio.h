#ifndef STDIO_H
#define STDIO_H

#include "../drivers/vga.h"

void mprints(char * s, unsigned int length);
void prints(char * s);
void printsln(char* s);
void printe(char* s);
void clrscr();

#endif