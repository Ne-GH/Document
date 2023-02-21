assume cs:code,ds:data,ss:stack

data segment
    dw 0,0,0,0
    dw 0,0,0,0
    dw 0,0,0,0
    dw 0,0,0,0
data ends

stack segment
    db 10 dup('123','abc')
stack ends


code segment

start:
    ; 初始化栈和数据段
    mov ax,data
    mov ds,ax
    mov ax,stack
    mov ss,ax
    mov sp,32

    ; div 指令
    ; div后跟除数
    ; 被除数 / 除数 = 商 + 余数
    ; 被除数默认在ax,或者ax和dx中
    ; 除数有8位和16位两种,可以是内存或寄存器

    ; 如果除数为8位 
    ; 被除数为16位,默认存在ax中
    ; al存储除法操作的商,ah存储除法操作的余数

    ; 如果除数为16位
    ; 被除数为32位,dx存放高16位,ax存放低16位
    ; ax存储除法的商,dx存储除法操作的余数
    
    mov ax,9
    mov bl,2
    div bl

    mov ax,17
    mov byte ptr ds:[0],4
    div byte ptr ds:[0]

    mov ds:[0],16
    mov ds:[2],0


    mov ax,ds:[0]
    mov dx,ds:[2]
    mov bx,3
    div bx

    mov ax,ds:[0]
    mov dx,ds:[2]
    mov ds:[3],3
    div word ptr ds:[3]















    ; 字型数据
    mov ax,0

    inc ax
    add ax,1000
    sub ax,255

    ; 字节型数据
    mov al,0
    mov al,bl
    mov al,ds:[0]
    mov ds:[1],al
    inc al
    add al,100
    ; add al,256 错误,因为8位寄存器不支持256

    mov ds:[0],0FFFFH
    ; 指定
    ; 字型
    mov word ptr ds:[0],1



    mov word ptr ds:[0],0FFFFH
    ; 字节型
    mov byte ptr ds:[0],2
    ;mov byte ptr ds:[0],256  错误,指定为byte,即8位寄存器,因此不能存储256



code ends

end start