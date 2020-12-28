#include "isr.h"

void init_isr() {
	init_idt(0, (uint32_t)isr0);
	init_idt(1, (uint32_t)isr1);
	init_idt(2, (uint32_t)isr2);
	init_idt(3, (uint32_t)isr3);
	init_idt(4, (uint32_t)isr4);
	init_idt(5, (uint32_t)isr5);
	init_idt(6, (uint32_t)isr6);
	init_idt(7, (uint32_t)isr7);
	init_idt(8, (uint32_t)isr8);
	init_idt(9, (uint32_t)isr9);
	init_idt(10, (uint32_t)isr10);
	init_idt(11, (uint32_t)isr11);
	init_idt(12, (uint32_t)isr12);
	init_idt(13, (uint32_t)isr13);
	init_idt(14, (uint32_t)isr14);
	init_idt(15, (uint32_t)isr15);
	init_idt(16, (uint32_t)isr16);
	init_idt(17, (uint32_t)isr17);
	init_idt(18, (uint32_t)isr18);
	init_idt(19, (uint32_t)isr19);
	init_idt(20, (uint32_t)isr20);
	init_idt(21, (uint32_t)isr21);
	init_idt(22, (uint32_t)isr22);
	init_idt(23, (uint32_t)isr23);
	init_idt(24, (uint32_t)isr24);
	init_idt(25, (uint32_t)isr25);
	init_idt(26, (uint32_t)isr26);
	init_idt(27, (uint32_t)isr27);
	init_idt(28, (uint32_t)isr28);
	init_idt(29, (uint32_t)isr29);
	init_idt(30, (uint32_t)isr30);
	init_idt(31, (uint32_t)isr31);

	init_idt_ptr();
}

char * exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(isr_reg_t r) {
    prints("received interrupt: ");
    // char s[3];
    // int_to_ascii(r.int_no, s);
    // prints(s);
    prints("\n");
    prints(exception_messages[r.int_no]);
    prints("\n");
}

