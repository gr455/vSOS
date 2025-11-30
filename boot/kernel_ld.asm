; /*
;  * use:
;  * kernel_ld:
;  *       calls dsk_ld
;  *       loads ~3MiB (6144 sectors) from disk (starting LBA=1)
;  *       into memory at [es:bx]
;  * in: es:bx (destination), dl (drive)
;  */

[bits 16]

kernel_ld:
	; push dx
	; mov dx, [current_lba]
	; call print_hex
	; call print_ln
	; pop dx
    pusha
    mov word [sectors_left], 77
    mov dword [current_lba], 3 ; start reading at LBA 1 - 0 is bootsector, skipt it and 1&2 are stage 2 BL skip that as well.

.load_loop:

    mov ax, [sectors_left]
    cmp ax, 0
    je .done

    ; --- decide how many sectors to read this call ---
    mov cx, ax
    cmp cx, 31
    jbe .use_cx
    mov cx, 31
.use_cx:

    ; dh = number of sectors
    mov dh, cl

    ; call dsk_ld (uses dl, es:bx, dh)
    push cx

	; push bx
	; mov bx, wow_msg
	; call print
	; call print_ln
	; pop bx

    call dsk_ld

	; push bx
	; mov bx, bruh_msg
	; call print
	; call print_ln
	; pop bx

	
    pop cx ; 31 sectors read

    ; --- advance memory pointer ---
    mov ax, cx
	push dx
    mov si, 512	; 512 bytes read per sector
    mul si      ; DX:AX = CX * 512 total bytes read
	pop dx ; this is safe since high(dx:ax) is always zero since it'sj ust 31*512.
    add bx, ax	; advance offset
    jnc .no_carry
    mov ax, es
    add ax, 0x1000 ; overstepped the segment. So increment.
    mov es, ax
.no_carry:

    ; --- advance LBA ---
    mov ax, word [current_lba]
    add ax, cx
    mov [current_lba], ax
    jc .carry_lba
    jmp .no_carry_lba
.carry_lba:
    inc word [current_lba+2]
.no_carry_lba:

    ; --- reduce remaining ---
    mov ax, [sectors_left]
    sub ax, cx
    mov [sectors_left], ax

    jmp .load_loop

.done:
    popa
    ret


; --- temporary storage ---
sectors_left dw 0
bruh_msg db "bruh", 0
wow_msg db "wow", 0
