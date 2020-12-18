; load at bootsector
[org 0x7c00]

mov bx, HM_MSG
call print
jmp $

%include "boot_sect_print.asm"

HM_MSG: dw "Booting into vSOS...", 0

; bootloader magic number

times 510 - ($ - $$) db 0
dw 0xaa55