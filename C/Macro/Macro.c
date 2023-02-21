#include <stdio.h>

// 实参中的空格将被替换为一个空格
// # 用于创建字符串
#define STR(s) # s

// ## 用来拼接字符
#define ST(s) T ## s

// 不被拼接的应当展开定义
// 被拼接的应该直接按照字面值进行拼接
#define SH(x) printf("n" #x "=%d,or %d\n",n##x,x)
#define SUB_Z 26
int main(){

    int nSUB_Z = 10;
    SH(SUB_Z);

    return 0;
}
