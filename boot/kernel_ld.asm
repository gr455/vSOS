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
    pusha
    mov word [sectors_left], 6144       ; total = 3 MiB
    mov dword [current_lba], 1          ; start reading at LBA 1 - 0 is bootsector, skipt it.

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
	; push dx
	; mov dx, [current_lba]
	; call print_hex
	; call print_ln
	; pop dx

    call dsk_ld
	
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
	jmp $
    popa
    ret


; --- temporary storage ---
sectors_left dw 0
