assume cs:code,ss:stack

; ret
; retf
; 均为字型数据
; 当执行ret指令时, 相当于执行了pop ip
; 当执行retf指令时,相当于执行了pop ip   pop cs


;call													
; 执行如下:												
;	push ip												
;	jmp near ptr 标号									
;1. cpu 从cs ip所组合的地址  读取指令  读到指令缓存器中	
;2. ip = ip + 所读取的指令的字节数						
;3. 执行指令缓存器中的内容,回到第一步					


; 16位位移
; 位移 = 标号处的偏移地址 - call 指令后第一个字节的地址
; -32768 - 32767

; jmp near prt 标号    是段内转移
; jmp far  ptr 标号    是段间转移

; call far ptr 标号
; ->push cs   push ip
; cs = 标号所在的段地址
; ip = 标号所在的段的偏移地址


; call word prt 
; push ip
; jmp word ptr


; call dword ptr
; push cs
; push ip
; jmp dword ptr

stack segment

	db 128 dup(0)
stack ends

code segment

start:

	;=============
	; 将ip寄存器修改为2233
	mov ax,2233H
	mov ax,2233H
	mov ax,3344H
	mov ax,1234H
	mov bx,2233H
	push ax
	
	
	ret 
	;========

	mov ax,stack
	mov ss,ax
	mov sp,128
	
	;====
	
	
	
	
	
	;====
	mov ax,0
	call far ptr s
	inc ax
	
	s:
	pop ax
	add ax,ax
	pop bx
	add ax,bx

	
	

code ends

end start



