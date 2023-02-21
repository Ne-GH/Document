/*
 * 0 关闭所有属性
 * 1 高亮度,类似于加粗
 * 4 下划线
 * 5 闪烁
 * 7 反显(背景色和前景色反过来)
 * 8 消隐(隐藏,不显示)
 * 30 - 37 前景色(黑 红 绿 黄 蓝 紫 深绿 白)
 * 40 - 47 背景色(黑 深红 绿 黄 蓝 紫 深绿 白)
 * nA 光标上移n行
 * nB 光标下移n行
 * nC 光标右移n行
 * nD 光标左移n行
 * y;xH 设置光标位置
 * 2J 清屏
 * K 清除光标到行尾的内容
 * s 保存光标位置
 * u 恢复光标位置
 * ?25l 隐藏光标
 * ?25h 显示光标
 */
#include <stdio.h>

#define NONE "\033[0m"
#define RED "\033[31m"
#define T "\033[?25hm"
#define CP(msg,...) printf(msg, ##__VA_ARGS__)

int main(){

    printf(RED"printf"NONE);
    printf("123");
    printf(RED);
    printf("456\n");
    printf(NONE);
    printf(T);
    printf(NONE);

    printf("123456");
    printf(NONE);
    CP(RED "123%d",10);
    /* printf("\033[5;31mChange Shell Color\n\033[0m"); */
    /* \033[31mThis is RED.\n\033[0m */

    return 0;
}
