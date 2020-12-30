; /*
;  * for 32 bit protected mode
;  * Global Descriptor Table
;  * based on Intel's flat model
;  *
;  */

gdt_start:

; segment descriptors begin

; for cpu null catching, if segment register contains 0x0
gdt_null:
	dd 0x0
	dd 0x0

; overlapping code and data descriptors as in Intel flat model
gdt_code:
	dw 0xffff ; limit 0:15
	dw 0x0 ; start(base) 0:15
	db 0x0 ; base 16:23
	db 10011010b; ( present )1 ( privilege )00 ( descriptor type )1 ( code )1 ( conforming )0 ( readable )1 ( accessed )0 
	db 11001111b; ( granularity )1 (32 - bit default )1 (64 - bit seg )0 ( AVL )0, limit 16:19; makes net limit 0xfffff
	db 0x0; base 24:31

gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b ; ( code ) 0
	db 11001111b
	db 0x0

gdt_end:

; segment descriptors end

gdt_descriptor: ; describes the current gdt
	dw gdt_end - gdt_start - 1 ; size, 16bit
	dd gdt_start ; base (32 bit)

BOOT_GDT_CODE: equ gdt_code - gdt_start
BOOT_GDT_DATA: equ gdt_data - gdt_start 
