assume cs:code ,ds:data ,ss:stack

; 将data段中的数据 按照以下格式写入table段中,并计算10年中的人均收入
; 并将结果按以下格式存入table段中
; (本质为结构化数据)

data segment
	; 年份
	db '1975','1976','1977','1978','1979','1980','1981','1982','1983','1984'
	; 该年份工资
	dd 16,22,382,1356,2390,8000,16000,24486,50056,97479
	; 员工数量
	dw 3,7,9,13,28,38,130,220,476,778
data ends


stack segment
	db 128 dup (0)
stack ends


table segment
	; 凑16字节
	db 10 dup('year summ ne ?? ')

table ends



code segment


start:
	; 初始化data数据段和stack数据段
	mov ax,stack
	mov ss,ax
	mov sp,128		;pop 的时候sp-2
	
	mov ax,data
	mov ds,ax
	
	mov ax,table
	mov es,ax
	
	
	; 年份的偏移地址
	mov si,0
	; 工资的偏移地址
	mov di,40
	; 人数的偏移地址
	mov bx,80
	; table 段中的第一个字母的偏移量
	mov bp,0
	
	mov cx,10

Get:
	; 把年份放入table段中
	push ds:[si]
	push ds:[si+2]
	pop es:[bp+2]
	pop es:[bp]
	add si,4
	
	; 人数
	mov ax,ds:[bx]
	mov es:[bp+10],ax
	add bx,2
	
	; 把ds中的工资放入table段中
	; 这里使用32位除法,商在ax中,余数在dx中
	; ax存放第16位,dx存放高16位
	mov ax,ds:[di]
	mov dx,ds:[di+2]
	mov es:[bp+5],ax
	mov es:[bp+7],dx
	add di,4
	
	; 得平均值
	div word ptr es:[bp+10]
	mov es:[bp+13],ax
	add bp,16
	loop Get
	
	
	; 程序结束
	mov ax,4C00H
	int 21H
	
	
code ends

end start