assume cs:code  ; 告诉编译器cs的别名为code

code segment    ;code段开始的地方
start:
    mov ax,2000H
    mov ss,ax
    mov sp,0    ; 修改栈指针
    add sp,10H
    pop ax      ; pop sp+2
    pop bx
    push ax     ;push sp-2
    push bx
    pop ax
    pop bx


    mov ax,4c00H
    int 21H

code ends       ;code段结束的地方



end start

;
