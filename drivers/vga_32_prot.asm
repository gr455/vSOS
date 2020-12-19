/*
 *	use:
 *	print_str_32p:
 *		in: ebx, edx
 *		prints character at [ebx] to vga display at [edx]
 */

[bits 32]

print_str_32p:
	pusha
	mov edx, 0xb8000 ; vga starting pointer
	jmp p_lp_32p

p_32p_end:
	popa
	ret

p_lp_32p:
	mov al, [ebx]
	mov ah, 0x0f ; white on black
	cmp al, 0
	je p_32p_end

	mov [edx], eax ; store to vga mem
	add edx, 2 ; vid memory is 2 byte word
	add ebx, 1

	jmp p_lp_32p