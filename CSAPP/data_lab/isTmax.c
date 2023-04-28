/*
 * 判断x是否是INT_MAX的补码
 * 是：返回1
 * 否：返回0
 */
int isTmax(int x) {
    return !(x ^0x7fffffff);
}
