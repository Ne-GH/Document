assume cs:code,ds:data

; 转移指令
; jmp 无条件转移
; jmp 跳转指令编译后的机器码和指令的长度有关
; CPU并不需要跳转的目的地址,只需要偏移地址,并修改IP寄存器即可即可
; 计算过程如下 偏移地址 = 标号地址 - jmp指令后第一个字节的地址
; jmp 指令有跳转范围,即-128 - 127  和  -32768 - 32767
; 8位位移   jmp short pos
; 16位位移  jmp near ptr pos

;loop 条件转移指令,根据cx寄存器中的值进行转移,cx寄存器中的值!=0的时候进行跳转
;jcxz 条件转移指令,根据cx寄存器中的值进行转移,cx寄存器中的值==0的时候进行跳转
;所有的条件转移指令都是短转移,位移范围 -128 - 127
;偏移是在编译的时候计算的


;offset start得到start的偏移地址,start可替换为其他内容

data segment
	db 'Hello Word      '
	db 01110001B
	db 00100100B
	db 00000010B

data ends

code segment 


start:
	; mov ax,offset start
	
	;jmp word ptr ds:[0] ; 修改ip寄存器为ds:[0](字型数据)中的值
	;jmp dword ptr ds:[0]; 修改ip寄存器为ds:[0]中的值,并修改cs寄存器为ds:[2]中的值(均为字型数据)
	
	; 在B800H - BFFFH 共32KB的空间,为80*32 彩色字符模式的显示缓冲区
	; 向这个地址空间写入数据,写入的内容将显示在显示器上
	; 80*25 彩色字符模式下,显示器可以显示25行,每行80个字符,每个字符有256种属性
	; 偶数地址存放字符的ASCII码
	; 奇数地址存放字符的颜色(属性)
	; 字符的属性占1个字节即8个bit,位的标号 7 6 5 4 3 2 1 0
	;                                (背景色)r g b   r g b(前景色)
	; 7: 闪烁   					(只有全屏dos才能看到效果)
	; 3: 高亮
	
	
	mov ax,data
	mov ds,ax
	mov bx,0B800H
	mov es,bx
	
	
	mov si,0
	mov di,160*10+30*2
	mov bx,16
	mov dx,0
	

	
	mov cx,4

F4:
	push si
	push di
	push cx
	
	mov cx,16
	mov dh,ds:[bx]
	
Show:
	mov dl,ds:[si]
	mov es:[di],dx
	add di,2
	inc si
	loop Show

	
	pop cx
	pop di
	pop si
	inc bx
	add di,160	
	
	loop F4
	mov ax,4C00H
	int 21H
	

code ends


end start