; Second stage
[org 0x7e00]

KERNEL_OFFSET: equ 0x1000
KERNEL_LBA_START: equ 2

; ** second stage boot **
second_stage:
	; Use saved drive from Stage 1
	mov [BOOT_DRIVE], dl

	cli
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov bp, 0x7000 ; this is lower than stage 1. should be fine.
	mov sp, bp
	sti

	mov bx, BOOT_STAGE_2_MSG
	call print
	call print_ln
	; Setup for kernel load
	mov bx, KERNEL_OFFSET
	xor ax, ax
	mov es, ax  ; ES=0
	; mov si, KERNEL_LBA_START    ; IN: si = starting LBA
    ; mov dh, 127                 ; IN: dh = max sectors per read
	mov dl, 0x80        ; IN: dl = drive
	call kernel_ld
	call use_protected

[bits 32]

BEGIN_PM:
	; Save only necessary registers instead of pusha
	; We don't want to use too much space on the temporary stack.
	push edx

	mov edx, 0xb8000
	sub edx, 0x2
	.clear_loop:
		mov ebx, NONE
		add edx, 0x2
		call print_str_32p
		cmp edx, 0xb87d0
		jnz .clear_loop
	
	; Restore saved register
	pop edx
	; Print boot message
	mov ebx, BOOT_MSG
	mov edx, 0xb8000
	call print_str_32p
	; Jump to kernel
	jmp KERNEL_OFFSET

[bits 16]

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"
%include "boot_sect_disk.asm"
%include "../drivers/vga_32_prot.asm"
%include "boot_gdt_32.asm"
%include "32_prot_switch.asm"
%include "kernel_ld.asm"

BOOT_STAGE_2_MSG: db "Bootloader in stage 2", 0
BOOT_MSG: db "Booting into vSOS", 0
KRL_LD_MSG: db "Loading kernel...", 0
BOOT_DRIVE: db 0x80 ; hard drive (overwritten by Stage 1)
NONE: dw " "