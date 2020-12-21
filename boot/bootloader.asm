; load at bootsector in memory
[org 0x7c00]

; ** sector 1 : boot **

; move stack pointer away to not accidentally overwrite stack
mov bp, 0x9000
mov sp, bp

mov bx, REAL_MSG
call print
call print_ln

mov bx, HM_MSG
call print

call use_protected

[bits 32]

BEGIN_PM:
	
	mov ebx, PROT_MSG
	call print_str_32p

jmp $

[bits 16]

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "../drivers/vga_32_prot.asm"
%include "boot_gdt_32.asm"
%include "32_prot_switch.asm"

HM_MSG: dw "Booting into vSOS...", 0
REAL_MSG: dw "in 16bit real mode ", 0
PROT_MSG: dw "switched to 32bit protected mode ", 0

; bootloader magic number

times 510 - ($ - $$) db 0
dw 0xaa55

