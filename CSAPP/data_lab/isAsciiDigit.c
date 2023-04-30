// 0x30 <= x <= 0x39 时返回1,否则返回0
int isAsciiDIgit(int x) {
    int mod = ~0 ^ 0x3f;    // mod = 0xffffffc0
    // 0xff ff ff c0(1100 0000)

    int flag = !(x & mod);
    int bit4 = x & 0xf;
    int one = !(x & 0x30 ^ 0x30);
    int two = !(bit4 & 0x8);
    int three = !(bit4 & 0x6);
    // cout << flag << " " << one << " " << two << " " << three << endl;
    return flag & one & (two | three);
}
