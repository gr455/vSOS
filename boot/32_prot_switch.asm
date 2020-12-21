[bits 16]

use_protected:
	cli ; disable interrupts
	lgdt [gdt_descriptor]
	mov eax, cr0 ; cr0 is 32 bits. it is allowed to use 32 bit registers in 16 bit mode
	or eax, 0x1 ; flip enable protected bit
	mov cr0, eax

	jmp BOOT_GDT_CODE:protected_mode ; far jumping from NOSEGMENT to BOOT_GDT_CODE to flush pipeline and finish tasks before jumping
	; far jump switches code segment(cs) register

[bits 32]

protected_mode:
	; initialize all segment registers to data segment
	mov ax, BOOT_GDT_DATA
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000 ; set stack
	mov esp, ebp

	call BEGIN_PM ; call label where PM is to be started

