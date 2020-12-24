; /*
;  * use:
;  * kernel_ld:
;  * 		calls disk_ld
;  * 		loads kernel from disk into memory(at [es:bx])
;  */


[bits 16]

kernel_ld:
	pusha
	mov bx, KRL_LD_MSG
	call print
	call print_ln

	; reading base 0x02 from disk
	mov bx, KERNEL_OFFSET ; 
	mov dh, 31 ; number of sectors

	mov dl, [BOOT_DRIVE]
	call dsk_ld
	popa

	ret