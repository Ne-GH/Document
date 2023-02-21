#include <stdio.h>

int main(){
    
    // C 內联汇编
    // __asm__("assembly code");Assembly code 表示需要执行的汇编

    //nop 表示让CPU空转一个指令执行周期
    __asm__("nop");

    // 如果需要执行多条汇编应该使用\n\t将各个指令分隔
    __asm__("movl $1,%eax\n\t"
            "movl $4,%ebx\n\t");
            /* "int $0x80"); */         // 为了不终止,注释掉
    
    // 一般使用內联汇编需要和C的变量建立关联,完整的內联汇编格式如下:    \
    __asm__(assembly template                                           \
            :output operands                /* 可选的 */                \
            :input  operands                /* 可选的 */                \
            :list of clobbered registers    /* 可选的 */                \
            );
    int a = 10,b;
    __asm__("movl %1,%%eax\n\t"    // 将a的值传给寄存器eax,为了和%1这种占位符区分,前面要用两个%
            "incl %%eax\n\t"
            "movl %%eax,%0\n\t"
            :"=r"(b)        // "=r"(b) 表示把%0 表示的寄存器中的值传递给b
                            
            :"r"(a)         // "r"(a) 表示指示编译器分配一个寄存器保存变量a的值作为汇编指令的输入,即指令中的%1
                            // 按照约束条件的顺序%0表示b,%1表示a,但具体是哪个寄存器则有编译器决定
            :"%eax"         // 把寄存器eax写出来告诉编译器,在执行__asm__的时候寄存器eax被改变,在此期间不要用eax存储别的值
            );

    printf("%d %d",a,b);

    return 0;
}
