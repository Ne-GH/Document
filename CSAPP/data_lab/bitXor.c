/*
 * 仅使用~ 和 & 实现 ^
 */
int bitXor(int x,int y) {
    int num1 = ~(x & y);
    int num2 = ~(~x & ~y);
    return num1 & num2;
}
