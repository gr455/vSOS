#ifndef IDT_H
#define IDT_H

#include "utils.h"
#include "../libc/util_types.h"

extern const int BOOT_GDT_CODE;

typedef struct idt_entry {
	uint16_t l_base;
	uint16_t select;
	uint8_t null;
	uint8_t flags;
	uint16_t h_base;
	
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
	uint16_t lim;
	uint32_t base;
} __attribute__((packed)) idt_ptr_t;


void init_idt(int index, uint32_t isr);
void init_idt_ptr();

#endif