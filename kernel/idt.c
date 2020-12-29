#include "idt.h"

// global

idt_entry_t idt[256];
idt_ptr_t idt_ptr_o;

void init_idt(int index, uint32_t isr){

	idt[index].l_base = low_16(isr);
	idt[index].select = 0x8; // BOOT_GDT_CODE
	idt[index].null = 0x0;
	idt[index].flags = 0x8e; // 10001110 ; run privilleged
	idt[index].h_base = high_16(isr);
}

void init_idt_ptr(){
	idt_ptr_o.base = (uint32_t) &idt;
	idt_ptr_o.lim = (uint16_t) 256 * sizeof(idt_entry_t) - 1;

	__asm__ __volatile__(
		" lidtl (%0) "
		:
		:
			"r" (&idt_ptr_o)
	);
}