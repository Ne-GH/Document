// 是否所有的奇数位均为1
// 是：返回1
// 否：返回0
int allOddBits(int x) {
    return ~(x & 0xaaaaaaaa ^ 0xaaaaaaaa);
}
