/*
 * 判断x是否是INT_MAX的补码
 * 是：返回1
 * 否：返回0
 */
int isTmax(int x) {
    int mask = x + 1;
    mask = ~mask;

    // 如果x 是0xffffffff,~!x 就是1,0x7fffffff就是0
    return !((x + !(~x)) ^ mask);
}
