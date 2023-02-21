assume cs:code
;data segment    ;告诉编译器,data段从这里开始,段的名字可以自定义,但是要用assume起别名并对应
;    dw 1H,2H,3H,4H,5H,6H,7H,8H
;data ends       ;告诉编译器,data段在这里结束


code segment

start:      ; 告诉编译器程序入口
    ; mov ax,stack
    ; mov ss,ax
    ; mov sp,32
    ; mov ax,data
    ; mov ds,ax

    ; es 附加段寄存器
    ; si 地址偏移寄存器
    ; di 地址偏移寄存器

    mov bx,0
    mov cx,0
    ;inc bx  自增bx
    ;Debug
    ;-u 查看汇编指令
    ;-a 写指令
    ;-t 运行一条表达式
    ;-r 显示堆栈及下一条将要执行的命令
    ;-d 查看数据,后面可以跟地址
    ;-p 运行一条表达式,跳过循环
    ;-q 退出



    mov ax,4c00H
    int 21H
code ends

end start

; vim:ft=nasm
