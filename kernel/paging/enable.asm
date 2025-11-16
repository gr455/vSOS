global set_paging_enable
global set_pd

; arg 0: kennel page directory physical address
set_paging_enable:
	call set_pd

	mov eax, cr0
	or eax, 0x80000000  ; set PG bit
	mov cr0, eax

	ret

; arg: 0: pd phys addr
set_pd:
	mov eax, [esp + 4]  ; get pd phys 4B from argument.
	mov cr3, eax

	ret