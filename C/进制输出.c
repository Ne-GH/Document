#include <stdio.h>

int main() {

    int num = 77;
    printf("%d\n",num);     // 10 进制
    printf("%o\n",num);     // 8  进制
    printf("%#o\n",num);    // 8 进制,带前缀
    printf("%x\n",num);     // 16 进制,小写
    printf("%#x\n",num);    // 16 进制,小写前缀
    printf("%X\n",num);     // 16 进制,大写
    printf("%#X\n",num);    // 16 进制,大写前缀
                            //
    return 0;
}
