// 实现三目运算符
int conditional(int x,int y,int z) {
    x = ~(!!x) + 1;
    // x != 0 时，x = 0xffffffff
    // x == 0 时，x = 0x0
    return (x&y) | (~x&z);
}
