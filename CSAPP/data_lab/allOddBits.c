// 是否所有的奇数位均为1
// 是：返回1
// 否：返回0
int allOddBits(int x) {
    int num = 0xaa;
    num ^= num << 8;
    num ^= num << 16;
    // num = 0xaaaaaaaa
    return !(x & num ^ num);
}
