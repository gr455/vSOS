[bits 32]
[extern k_main]
[extern zero_bss]

section .bss
align 4
kernel_stack:
    resb 8192    ; 8KB stack size

section .text
global _start
_start:
    call zero_bss ; this uses temp stack
    ; Set up the stack
    lea ebp, [kernel_stack + 8192]  ; Point to top of stack
    mov esp, ebp
    
    ; Call kernel main
    call k_main
    jmp $
