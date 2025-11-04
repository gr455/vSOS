; /*
;  * use:
;  * kernel_ld:
;  * 		calls disk_ld
;  * 		loads kernel from disk into memory(at [es:bx])
;  */

[bits 16]

kernel_ld:
	pusha
	; reading from LBA 1 (sector 2) for 3000 sectors
	mov bx, KERNEL_OFFSET
	mov dh, 127 ; max sectors per read
	mov cx, 3000 ; total sectors
	
	mov dl, 0x80
	call dsk_ld
	popa

	ret