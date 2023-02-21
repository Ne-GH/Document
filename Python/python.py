#!/usr/bin/python3
# coding=utf-8  # 指定编码,防止乱码
'''
注释1
'''
"""
注释2
"""
# 注释3

# 空语句
pass
# 变量
a = b = c = 1       # 创建变量a,b,c且均赋值为1
t1,t2,t3 = 1,2,"t3" # 创建变量t1,t2,t3,并分别赋值为1,2,"t3"

del a   #删除对象a的引用,py一切皆对象?

# python 假设所有函数内的赋值都是局部变量,如果我们需要给全局变量复制,需要global

# 模块引用
# import cmath              加载cmath,使用时cmath.abs()
# form cmath import abs     仅加载cmath中的abs
# form cmath import *       把cmath中的所有内容加载进来



# python 标准数据类型:
# number        数字
NumberVar = 1
# string        字符串
StrVar = "StrVar"
StrVar
StrVar[0]       # 下标为0的字符
StrVar[1:5]     # StrVar下标1-5即1,2,3,4
StrVar[1:]      # StrVar下标1开始,到结尾
StrVar * 2      # 两次  例如print(str * 2)
StrVar + "Addition"
# list          列表
# 用法同string
ListVar = ['PythonList',123,456.78]
ListVar2 = ['Var2']
ListVar
ListVar[0]
ListVar[1:5]
ListVar[1:]
ListVar * 2
ListVar + ListVar2

# tuple         元组
# 元组类似于list,但是不能二次赋值,即const,onlyread
# 用法同string和list
TupleVar = ("PythonTuple",123,456.789)
TupleVar2 = ("TupleVar2")
TupleVar
TupleVar[0]
TupleVar[1:5]
TupleVar[1:]
TupleVar * 2
# TupleVar + TupleVar2  该语句运行失败,提示不能连接tuple
# print(TupleVar+TupleVar2) ,同上,失败
# TupleVar3 = TupleVar + TupleVar2  ,同上,失败

# dictionary    字典
DictVar = {'name':'Python','ok':1,1:"pos"}
DictVar['name']     # 键为'name'的数据
DictVar[1]          # 键为1的数据
DictVar             # 完整的字典
DictVar.keys()      # 所有的键
DictVar.values()    # 所有的值


# 使用单词作为逻辑运算符
# and   &&
# or    ||
# not   !

# 身份运算符
# is ,is not        如果两个对象引用自一个对象,is返回true,is not 返回false

# I/O
Name = input("input:")
print(Name)   

# 分支
str = "True"
if True==str and True:                       # python不使用{  },而是根据缩进表示模块,缩进空白数量随意,但是,所有代码快必须有相同的缩进数量
    print(str,end="")               # end=""表示不换行
    print(str)
elif str=="True":
    print("str:True",str * 2)
    # print("2-4",str[2:4])
else:
    print(str)

# 循环
whileflag = 0
while whileflag < 10:
    print(whileflag)
    whileflag += 1
else:                   # 可以仅使用while,不使用else语句
    print("EndWhile")

templist = [1,10,100]
for forflag in templist:
    print(forflag)

for forflag in range(10,20):
    print(forflag)
else:
    print("ForEnd")         # 同while,一样可以在末尾加上else

# 函数
# 定义
def fun(var,var2 = 123  ):      # 圆括号中间可以定义参数,可以定义默认参数
    pass
    print("Fun",var2)
    return 0        # 不带return,默认返回None

fun("var")
fun("var",111)

# 可变参
def funchange(par,*varlist):        # 参数前加*表示变参列表
    for par in varlist:
        print(par)
    return 0

funchange(1,2,3,4,'q',"zxc","中文")

# lambda
sum = lambda arg1,arg2 : arg1 + arg2
sum(10,20)      # 调用上述lambda函数


# 异常
# try:
# <语句>        #运行代码
# except <名字>：
# <语句>        #如果在try部份引发了'name'异常
# except <名字>，<数据>:
# <语句>        #如果引发了'name'异常，获得附加的数据
# else:
# <语句>        #如果没有异常发生

# try:
# <语句>        #运行代码
# except：
# <语句>        #如果在try部份引发了异常
# else:
# <语句>        #如果没有异常发生

# try:
# <语句>
# finally:
# <语句>    #退出try时总会执行
# raise
