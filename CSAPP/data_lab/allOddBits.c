int allOddBits(int x) {
    return ~(x & 0xaaaaaaaa ^ 0xaaaaaaaa);
}
