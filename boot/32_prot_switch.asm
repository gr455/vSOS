[bits 16]

use_protected:
	cli ; disable interrupts
	lgdt [gdt_descriptor]
	mov eax, cr0 ; cr0 is 32 bits. it is allowed to use 32 bit registers in 16 bit mode
	or eax, 0x1 ; flip enable protected bit
	mov cr0, eax
