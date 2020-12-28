#include "idt.h"

// global

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

void init_idt(int index, uint32_t isr){
	idt_entry_t table = idt[index];

	table.l_base = low_16(isr);
	table.select = 0x8; // BOOT_GDT_CODE
	table.null = 0x0;
	table.flags = 0x8e; // 10001110 ; run privilleged
	table.h_base = high_16(isr);
}

void init_idt_ptr(){
	idt_ptr.base = (uint32_t) &idt;
	idt_ptr.lim = (uint16_t) 256 * sizeof(idt) - 1;

	__asm__ __volatile__(
		" lidtl (%0) "
		:
		:
			"r" (&idt_ptr)
	);
}