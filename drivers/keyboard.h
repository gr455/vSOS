#ifndef KEYBR_H
#define KEYBR_H

#include "../kernel/ports.h"
#include "../kernel/isr.h"
#include "../libc/stdio.h"

static void keyboard_callback();
void init_keyboard();
void print_letter(uint8_t scancode);

#endif
