#include <stdio.h>
#include <stdarg.h>
#define NUL '\0'

#define debug_int(...) printf(__VA_ARGS__)
#define debug_char(format,args...) printf(format,args)
// 可变参数__VA_ARGS__必须传入一个参数
// 不过可以通过以下形式定义,宏连接符##将会使预处理器处理掉可变参数前的','
#define debug_none(format,args...) printf(format,##args)


struct map{
    int   key;
    char  val;
};

int Argfun(char *format,...){
    int num = 0;
    char ch = 'A';
    // 定义一个可变参数列表,存有va_start,va_arg,va_end以及va_cpy所需要的信息
    va_list args ;
    // 用format初始化args,令函数的以访问可变参数
    // 第二个参数是最后传入参数列表的那个固定参数
    va_start(args,format);

    va_list dest;
    // 创建可变参数的副本
    va_copy(dest, args);

    while(*format != NUL){
        if(*format == '%'){
            if(*(format + 1) == 'n'){
                struct map temp = va_arg(args, struct map);
                printf("%d:%c",temp.key,temp.val);
                format ++;
            }
        }
        else{
            putchar(*format);
        }
        format ++;
    }

    // 结束可变参数的获取,将指针置为无效
    va_end(args);
    return num;
}

int main(){


    struct map no = {1,'A'};

    /* Argfun("%n%n%n%n",no,no,no,no); */

    debug_int("\n%d:",no.key);
    debug_char("%c\n", no.val);

    return 0;
}
