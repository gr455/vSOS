global set_paging_enable
global set_pd

; arg 0: kernel page directory physical address
set_paging_enable:
	mov eax, [esp + 4]
	call set_pd

	mov eax, cr0
	or eax, 0x80000000  ; set PG bit
	mov cr0, eax
	ret

; eax = pd physical
set_pd:
	mov cr3, eax
	ret
