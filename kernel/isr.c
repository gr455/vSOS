#include "isr.h"

//global
isr_h handlers[256];

void init_isr() {
	/* Map system ISRs */
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

	/* Remap PIC */

	// fetch masks
	uint8_t mask_m = port_byte_in(0x21);
	uint8_t mask_s = port_byte_in(0xA1);

	// init requred
	port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // set irq offsets
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    port_byte_out(0x21, 0x04); // configure slave with master
    port_byte_out(0xA1, 0x02);

    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    // restore masks
    port_byte_out(0x21, mask_m);
    port_byte_out(0xA1, mask_s);

    /* Map IRQs */
    init_idt(32, (uint32_t)irq0);
    init_idt(33, (uint32_t)irq1);
    init_idt(34, (uint32_t)irq2);
    init_idt(35, (uint32_t)irq3);
    init_idt(36, (uint32_t)irq4);
    init_idt(37, (uint32_t)irq5);
    init_idt(38, (uint32_t)irq6);
    init_idt(39, (uint32_t)irq7);
    init_idt(40, (uint32_t)irq8);
    init_idt(41, (uint32_t)irq9);
    init_idt(42, (uint32_t)irq10);
    init_idt(43, (uint32_t)irq11);
    init_idt(44, (uint32_t)irq12);
    init_idt(45, (uint32_t)irq13);
    init_idt(46, (uint32_t)irq14);
    init_idt(47, (uint32_t)irq15);


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

void isr_handler(isr_reg_t r){
    prints("received interrupt: ");
    char s[3];
    int_to_ascii(r.int_no, s);
    prints(s);
    prints("\n");
    prints(exception_messages[r.int_no]);
    prints("\n");
}

void irq_handler(isr_reg_t r){

	// if(handlers[r.int_no] == 0) return; // not implemented


	// printsln("recieved hardware interrupt ");
	// char s[4];
	// int_to_ascii(r.int_no, s);
	// prints(s);

	/* EOI */
	if(r.int_no > 40) // slave
		port_byte_out(0xa0, 0x20);

	// master
	port_byte_out(0x20, 0x20);

	/* handle */

	// handler has a value of offset in code segment
	// handler itself is in data segment, but the value offsets code segment
	// hence works with non flat gdt model
	if(handlers[r.int_no] == 0) return;
	isr_h handler = handlers[r.int_no];
	handler(r);
}

void new_handler(uint8_t intr, isr_h handler){
	handlers[intr] = handler;
}