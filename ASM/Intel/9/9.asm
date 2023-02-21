assume cs:code  

code segment   
start:


    mov ax,0
    mov cx,123

Addnumber:
    add ax,236
    loop Addnumber      ; 该循环实现了236*123


    mov ax,2000H
    mov ds,ax
    mov bx,1000H

    mov dl,0

Set:            ; 标识
    mov ds:[bx],dl
    inc dl
    inc bx

    jmp Set     ; 由于我们不能直接在源文件里跳转到某个特定的地址,所以使用标识来帮助我们跳转


    ;loop指令 按照次数跳转,循环次数保存在cx寄存器中
    ;loop指令的两个步骤
        ;1.cx = cx-1
        ;2.判断cx的值,不为0就jmp跳转,为0就往下继续执行

    mov cx,1
    mov ax,0
SetLoop:
    inc ax
    loop SetLoop


code ends       





end start


