; load at bootsector in memory
[org 0x7c00]

SECOND_STAGE_OFFSET: equ 0xe82E
SECOND_STAGE_SEGMENT: equ 0x0

boot_min:
	mov [BOOT_DRIVE], dl ; BIOS stores boot drive in dl

	; move stack pointer away to not accidentally overwrite stack
	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov bp, 0xfffe
	mov sp, bp
	sti

	; Load second stage (sectors 2-4) into memory at 0x7E00
	mov bx, SECOND_STAGE_OFFSET
    push ax
    mov ax, SECOND_STAGE_SEGMENT
    mov es, ax
    pop ax
	mov dh, 4 ; must fit stage 2 within ~2KiB (4 sectors)
	mov dl, [BOOT_DRIVE]
	call load_second_stage

	; Jump to second stage
	jmp SECOND_STAGE_SEGMENT:SECOND_STAGE_OFFSET

; Simple routine to load sectors (starting sector 2)
load_second_stage:
	pusha
	push dx
	mov ah, 0x02 ; read mode
	mov al, dh ; number of sectors
	mov cl, 0x02 ; first sector to read (0x01 contains MBR)
	mov ch, 0x00 ; cylinder
	mov dh, 0x00 ; head  ; Note: Overwrites DH temporarily

	int 0x13
	jc disk_err_simple

	pop dx  ; Restore original DX (DH=sectors, DL=drive)
	cmp al, dh ; verify read sectors
	jne sec_err_simple

	popa
	ret  ; .done:

disk_err_simple:
	pop dx  ; Balance stack
	popa
	mov bx, DSK_ERR_MSG_SIMPLE
	call print
	jmp hang

sec_err_simple:
	pop dx
	popa
	mov bx, SEC_ERR_MSG_SIMPLE
	call print
	jmp hang

hang:
	mov bx, HANG_MSG_SIMPLE
	call print
	call print_ln
	jmp $

%include "boot_sect_print.asm"

DSK_ERR_MSG_SIMPLE: db "dsk err", 0
SEC_ERR_MSG_SIMPLE: db "sec err", 0
HANG_MSG_SIMPLE: db "hang", 0
BOOT_DRIVE: db 0x0 ; hard drive

; bootloader magic number
times 510 - ($ - $$) db 0
dw 0xaa55