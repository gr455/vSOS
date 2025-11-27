; /*
;  * use:
;  * dsk_ld:
;  *       in: dh (total sectors to read), dl (drive), es:bx (destination)
;  *      loads data from disk (starting at LBA 1) into memory at [es:bx]
;  *      Assumes bios (which seabios does) supports reading beyond segment boundary
;  */

[bits 16]

dsk_ld:
	; push dx
	; mov dx, bx
	; call print_hex
	; call print_ln
	; pop dx
    pusha
    push ds
    push si
    mov ax, cs
    mov ds, ax

    mov [dap+0], byte 0x10       ; size
    mov [dap+1], byte 0x00       ; reserved
    mov [dap+2], dh              ; sectors to read
    mov [dap+4], bx              ; buffer offset
    mov [dap+6], es              ; buffer segment

    mov ax, [current_lba]
	mov [dap+8], ax
	mov ax, [current_lba+2]
	mov [dap+10], ax
	mov dword [dap+12], 0

    ; === Perform INT 13h AH=42h read ===
    mov si, dap
    mov ah, 0x42

	; push dx
	; mov dx, es
	; call print_hex
	; call print_ln
    ; mov dx, bx
	; call print_hex
	; call print_ln
	; pop dx

	int 0x13
	; push dx
	; mov dx, bx
	; call print_hex
	; call print_ln
	; pop dx
	; push bx
	; mov bx, SEC_ERR_MSG
	; call print
	; pop bx

    jc dsk_err                   ; CF=1 → error

    ; === Success check ===
    cmp ah, 0
    jne sec_err                  ; just in case
    

    pop si
    pop ds
    ; push dx
    ; mov dx, sp
    ; call print_hex
    ; call print_ln
    ; mov dx, bp
    ; call print_hex
    ; call print_ln
    ; pop dx

    ; jmp $
    popa

    ; push bx
	; mov bx, bruh_msg
	; call print
	; call print_ln
	; pop bx

    ret

dsk_err:
    pusha
    mov bx, DSK_ERR_MSG
    call print
    mov dh, ah                   ; error code
    call print_hex
    popa
    jmp dsk_loop

sec_err:
    pusha
    mov bx, SEC_ERR_MSG
    call print
    mov dh, ah
    call print_hex
    popa
    jmp dsk_loop

dsk_loop:
    jmp $   ; hang

; === DAP ===

dap:
    db 0x10        ; size
    db 0x00        ; reserved
    dw 0           ; number of sectors
    dw 0           ; offset
    dw 0           ; segment
    dq 0           ; starting LBA (little endian)

current_lba dd 0


DSK_ERR_MSG: db "fatal: disk could not be read. code:", 0
SEC_ERR_MSG: db "fatal: some sectors could not be read. code:", 0
