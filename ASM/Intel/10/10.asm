assume cs:code,ds:data  

; 在程序中安排自己的数据段
data segment        ;伪指令,实际上cpu并不会按照我们的安排来安排数据,不同的segment的编译方式会影响我们的内存
                    ;各个代码段分配的内存,如果刚好是16字节的倍数,就是该值,否者补齐到16字节的倍数
    ;db 定义字节型数据   1字节
    ;dw 定义字型数据   x86下2字节
    ;dd 定义双字型数据 x86下4字节
    dw 1,2,3,4,5,6,7,8
    dw 11,12,13,14,15,16,17,18


    ; dup指令
    ; 配合dd dw  db指令,重复定义
    ; 定义100个db  都是0
    db 100 dup(0) 
    ; 定义10个'123abc'
    db 10 dup('123','abc')
data ends
code segment

start:
    ; 由于程序不会按照我们给定的数据段进行分配,所以我们需要修改ss,ds等寄存器,使之指向我们安排的数据
    mov ax,data
    mov ds,ax

    mov ax,0
    mov bx,0

    mov cx,8


AddNum:
    add ax,ds:[bx]
    add bx,2
    loop AddNum

code ends

end start