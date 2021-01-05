; load at bootsector in memory
[org 0x7c00]

KERNEL_OFFSET: equ 0x1000

; ** sector 1 : boot **

boot:
mov [BOOT_DRIVE], dl ; BIOS stores boot drive in dl

; move stack pointer away to not accidentally overwrite stack
mov bp, 0x9000
mov sp, bp

call kernel_ld

call use_protected

[bits 32]

BEGIN_PM:
	pusha
	mov edx, 0xb8000
	sub edx, 0x2
	call clr_scr
	popa
	mov ebx, BOOT_MSG
	mov edx, 0xb8000
	call print_str_32p
	call KERNEL_OFFSET
	jmp $

clr_scr:
	mov ebx, NONE
	add edx, 0x2
	call print_str_32p
	cmp edx, 0xb87d0
	jnz clr_scr
	ret

[bits 16]

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "../drivers/vga_32_prot.asm"
%include "boot_gdt_32.asm"
%include "32_prot_switch.asm"
%include "kernel_ld.asm"


BOOT_MSG: dw "Booting into vSOS", 0
KRL_LD_MSG: dw "Loading kernel...", 0
BOOT_DRIVE: db 0x0 ; hard drive
NONE: db " "

; bootloader magic number

times 510 - ($ - $$) db 0
dw 0xaa55

