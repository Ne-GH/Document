#include <stdio.h>

#define MA 10

#if !MA == 10
    int Mc = 10;
#endif


// 如果MA宏定义不存在,那么变成 #if 0 || TEMP || 2 < 3
// 如果MA 和 TEMP都不存在,那么变成 #if 0 || 0 || 2 < 3
// 因为 2 < 3 成立,所以 #if 0 || 0 || 1   ,即成立
// 条件编译查找的是宏定义,即便存在同名的变量定义,也不考虑
#if MA || TEMP || 2 < 3
    long long Mc = 100; 
#else 
    double Mc = 10.10;
#endif




// 根据条件判断编译器环境
#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
  // 编译器版本大于等于 4.9，可以使用某些特性
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1900
  // 编译器版本大于等于 MSVC 2015，可以使用某些特性
#endif

#if defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 5))
  // 编译器版本大于等于 Clang 3.5，可以使用某些特性
#endif



int main(){


#define a 1;
#ifdef a//如果使用预处理宏定义a,就编译中间内容
#define a 1;
	printf("ifdef部分");
#endif//选择性编译的结束标志

#define b 0
#if b//如果预处理定义的b的值为0就编译第一部分
    printf("b为真时,#if部分");
#else//否则编译下面
    printf("b不为0时,#else部分");
#endif//结束标志


#ifndef c//如果没有使用预处理宏定义定义c,就编译
#define c 1//这种写法属于没有定义c
    printf("#ifndef,没有编译");
#endif
    return 0;
}
