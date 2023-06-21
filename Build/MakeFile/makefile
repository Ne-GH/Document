# 目标 : 所需文件
# <tab>将所需文件生成为目标所需要的代码
# main:main.o fun.o
	# gcc main.o fun.o -o main

# 定义CXX变量，值为 g++
CXX = g++
TARGET = Main
# 当前文件夹下的.c文件都放在SRC变量中
SRC = $(wildcard *.c)
# 将SRC中的.c结尾的文件都换成.o
OBJ = $(patsubst %.c,%.o,$(SRC))
# OBJ = main.o fun.o

CXXFLAGS = -c -Wall

# $(OBJ) 读取变量的内容 
# $(TARGET) : $(OBJ)
	# $(CXX) -o $(TARGET) $(OBJ)
# $@ 是生成目标 , $^ 是依赖
$(TARGET) : $(OBJ)
	$(CXX) -o $@ $^

# main.o:main.c
	# gcc -c main.c
# fun.o:fun.c
	# gcc -c fun.c

# $< 是第一个依赖，$^是所有依赖
%.o : %.c
	$(CXX) $(CXXFLAGS) -o $@ $<

install:
	@echo "install"

# .PHONT : clean
# 如果当前文件夹下有个文件叫做clean，make clean会提示clean文件已经最新了
# 这时候需要添加.PHONT : clean,.PHONT 目标永远不会存在，因此可以避免这一问题
clean:
	rm *.o $(TARGET)
	# @echo "如果加了@,表示只显示结果,而不显示命令本身"
	echo "删除文件"
	# -tttttt
	# echo "如果前面加了-,表示即使遇到错误也不停止,否则遇到错误会停止"

