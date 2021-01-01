#ifndef KEYBR_H
#define KEYBR_H

#define MAX_KEYBUFF_S 256

#include "../kernel/ports.h"
#include "../kernel/isr.h"
#include "../libc/stdio.h"

static void keyboard_callback();
void init_keyboard();
void print_letter(uint8_t scancode);
void push_buff(char k[]);
char * pop_buff();
char * peek_buff();
uint8_t get_buffsize();

#endif
