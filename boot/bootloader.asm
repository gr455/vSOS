; load at bootsector in memory
[org 0x7c00]

KERNEL_OFFSET: equ 0x1000

; ** sector 1 : boot **

mov [BOOT_DRIVE], dl ; BIOS stores boot drive in dl

; move stack pointer away to not accidentally overwrite stack
mov bp, 0x9000
mov sp, bp

mov bx, HM_MSG
call print
call print_ln
call print_ln
; call print_ln

call kernel_ld

call use_protected

[bits 32]

BEGIN_PM:
	mov ebx, BOOT_MSG
	mov edx, 0x720
	add edx, 0xb8000
	call print_str_32p
	call KERNEL_OFFSET
	jmp $

[bits 16]

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "../drivers/vga_32_prot.asm"
%include "boot_gdt_32.asm"
%include "32_prot_switch.asm"
%include "kernel_ld.asm"


HM_MSG: dw "Booting into vSOS...", 0
BOOT_MSG: dw "vSOS v0.0 beta", 0
KRL_LD_MSG: dw "Loading kernel...", 0
BOOT_DRIVE: db 0x0 ; hard drive

; bootloader magic number

times 510 - ($ - $$) db 0
dw 0xaa55

