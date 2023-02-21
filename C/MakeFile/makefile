main:main.o fun.o
	gcc main.o fun.o -o main

main.o:main.c
	gcc -c main.c
fun.o:fun.c
	gcc -c fun.c

install:
	@echo "install"

clean:
	@echo "如果加了@,表示只显示结果,而不显示命令本身"
	echo "删除文件"
	-tttttt
	echo "如果前面加了-,表示即使遇到错误也不停止,否则遇到错误会停止"

