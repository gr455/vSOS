; load at bootsector in memory
[org 0x7c00]

; ** sector 1 : boot **

; move stack pointer away to not accidentally overwrite stack
mov bp, 0x6000
mov sp, bp

mov bx, 0x9000 ; pointer in mem to store disk data
mov dh, 2 ; set sector count

call dsk_ld

mov bx, HM_MSG
call print

mov dx, [0x9000] ; segmentation at 0
call print_ln
call print_hex
call print_ln

mov dx, [0x9000 + 512]
call print_hex
call print_ln

jmp $

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "../drivers/vga_32_prot.asm"

HM_MSG: dw "Booting into vSOS...", 0

; bootloader magic number

times 510 - ($ - $$) db 0
dw 0xaa55

; ** sector 2 **

times 256 dw 0xdada ; sector 2 = 512 bytes
times 256 dw 0xface ; sector 3 = 512 bytes
