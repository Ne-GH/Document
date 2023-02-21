assume cs:code,ds:data,ss:stack

data segment       
    ;单引号可以直接表示字符及字符串
    db 'char!           '
    db 'char!           '
    db 'char!           '
    db 'char!           '
data ends

stack segment
    dw 0,0,0,0
stack ends

code segment

start:
    ; 初始化数据段
    mov ax,data
    mov ds,ax

    mov bx,0
    mov cx,0

Up1:   
    mov dx,cx
    mov cx,4
    mov si,0

Up2:
    mov al,ds:[bx+si]
    and al,11011111B
    mov ds:[bx+si],al
    inc si
    loop Up2
    











    mov bx,0
    mov cx,4

UpChar:
    mov al,ds:[bx]
    and al,11011111B
    mov ds:[bx],al
    inc bx
    loop UpChar

    mov bx,0
    mov cx,4
DownChar:
    mov al,ds:[bx]
    or al,00100000B
    mov ds:[bx],al
    inc bx
    loop DownChar



    ; mov ax,'T'





    ; and 和 or均为二进制逻辑运算
    mov al,00001111B
    and al,11110000B

    mov al,00001111B
    or  al,11110000B

code ends

end start