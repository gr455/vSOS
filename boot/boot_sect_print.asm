; /*
;  *  use:
;  *  print:
;  *      in: bx
;  *      prints the value at location pointed by bx followed by newline char
;  *  
;  *  print_ln:
;  *      prints nextline and carriage return
;  *
;  */

print:
    pusha

start:
    mov al, [bx] ;
    cmp al, 0 
    je done

    mov ah, 0x0e
    int 0x10 ;

    add bx, 1
    jmp start

done:
    popa
    ret



print_ln:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret