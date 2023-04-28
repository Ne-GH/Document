int isAsciiDIgit(int x) {

    int flag = !(x & 0xffffffc0);
    int bit4 = x & 0xf;
    int one = !(x & 0x30 ^ 0x30);
    int two = !(bit4 & 0x8);
    int three = !(bit4 & 0x6);
    // cout << flag << " " << one << " " << two << " " << three << endl;
    return flag & one & (two | three);
}
