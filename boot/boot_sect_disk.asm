; /*
;  * use:
;  * dsk_ld:
;  * 		in: dh, dl, es, bx
;  *		loads data from disk(sector 0x02 in drive dl) into memory at [es:bx]
;  *		reads number of sectors specified in dh  
;  */

dsk_ld:
; dl -> 0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2
	pusha
	push dx
	mov ah, 0x02 ; read mode
	mov al, dh ; number of sectors
	mov cl, 0x02 ; first sector to read (0x01 contains MBR); for some reason indexing starts at 1 for chs
	; 0x02 will contain kernel
	mov ch, 0x00 ; cylinder
	mov dh, 0x00 ; head

	int 0x13

	jc dsk_err

	pop dx
	cmp al, dh ; verify read sectors
	jne sec_err
	popa
	ret

dsk_err:

	pusha
	mov bx, DSK_ERR_MSG
	call print ; included
	mov dh, ah ; status code
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
	jmp $ ; hang

; data

DSK_ERR_MSG: db "fatal: disk could not be read. code:", 0
SEC_ERR_MSG: db "fatal: some sectors could not be read. code:", 0
