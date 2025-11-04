#ifndef STDIO_H
#define STDIO_H

#include "../drivers/vga.h"
#include "string.h"

void mprints(char *s, unsigned int length);
void prints(char *s);
void printsln(char *s);
void printe(const char *e);
void printeln(const char *e);
void printsucs(const char *s);
void printsucsln(const char *s);
void printinfs(const char *inf);
void printinfsln(const char *inf);
void printc(char c);
void printi(int i);
void clrscr();

#endif