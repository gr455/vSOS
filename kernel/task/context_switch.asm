[bits 32]

global context_switch_asm
global jump_to_task

; void context_switch_asm(cpu_state_t* old_state, cpu_state_t* new_state)
; arg0 (esp+4): old_state pointer
; arg1 (esp+8): new_state pointer
;
; cpu_state_t layout (from task.h):
; offset 0:  eax
; offset 4:  ebx
; offset 8:  ecx
; offset 12: edx
; offset 16: esi
; offset 20: edi
; offset 24: ebp
; offset 28: esp
; offset 32: eip
; offset 36: eflags
; offset 40: cs
; offset 44: ss
; offset 48: ds
; offset 52: es
; offset 56: fs
; offset 60: gs

context_switch_asm:
	push ebp
	mov ebp, esp
	
	mov eax, [ebp + 8]  ; old_state pointer
	mov edx, [ebp + 12] ; new_state pointer
	
	; Save old state
	mov [eax + 0], eax   ; eax (already in eax)
	mov [eax + 4], ebx
	mov [eax + 8], ecx
	mov [eax + 12], edx  ; edx (need to save before we clobber)
	mov [eax + 16], esi
	mov [eax + 20], edi
	mov [eax + 24], ebp
	mov [eax + 28], esp
	; eip is handled separately (return address on stack)
	mov ecx, [ebp]      ; old ebp from stack
	mov [eax + 32], ecx ; save as eip (next instruction)
	pushfd
	pop ecx
	mov [eax + 36], ecx ; eflags
	mov ecx, cs
	mov [eax + 40], ecx ; cs
	mov ecx, ss
	mov [eax + 44], ecx ; ss
	mov ecx, ds
	mov [eax + 48], ecx ; ds
	mov ecx, es
	mov [eax + 52], ecx ; es
	mov ecx, fs
	mov [eax + 56], ecx ; fs
	mov ecx, gs
	mov [eax + 60], ecx ; gs
	
	; Load new state
	mov eax, [ebp + 12] ; new_state pointer
	
	mov ebx, [eax + 4]
	mov ecx, [eax + 8]
	mov edx, [eax + 12]
	mov esi, [eax + 16]
	mov edi, [eax + 20]
	mov ebp, [eax + 24]
	mov esp, [eax + 28]
	
	; Load eflags (must use popfd)
	mov ecx, [eax + 36]
	push ecx
	popfd
	
	; Set segment registers
	mov ecx, [eax + 48]
	mov ds, ecx
	mov ecx, [eax + 52]
	mov es, ecx
	mov ecx, [eax + 56]
	mov fs, ecx
	mov ecx, [eax + 60]
	mov gs, ecx
	
	; Load eax last
	mov eax, [eax + 0]
	
	ret

; void jump_to_task(cpu_state_t* state)
; arg0 (esp+4): state pointer
;
; This function jumps to a task without saving state
; Used to start a new task for the first time

jump_to_task:
	mov eax, [esp + 4]  ; state pointer
	
	; Load all registers except eip
	mov ebx, [eax + 4]
	mov ecx, [eax + 8]
	mov edx, [eax + 12]
	mov esi, [eax + 16]
	mov edi, [eax + 20]
	mov ebp, [eax + 24]
	mov esp, [eax + 28]
	
	; Load eflags
	mov ecx, [eax + 36]
	push ecx
	popfd
	
	; Load segment registers
	mov ecx, [eax + 48]
	mov ds, ecx
	mov ecx, [eax + 52]
	mov es, ecx
	mov ecx, [eax + 56]
	mov fs, ecx
	mov ecx, [eax + 60]
	mov gs, ecx
	
	; Get eip and jump to it
	mov ecx, [eax + 32]
	
	; Load eax last
	mov eax, [eax + 0]
	
	jmp ecx
