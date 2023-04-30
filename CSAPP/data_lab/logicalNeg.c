// 不使用！实现！
int logicalNeg(int x) {
    unsigned int mod = x;
    // 高16 | 低16
    mod = (mod >> 16) | (mod); // 只看低16
    mod = (mod >> 8)  | (mod); // 低8
    mod = (mod >> 4)  | mod; //4
    mod = (mod >> 2)  | mod; // 2
    mod = (mod >> 1)  | mod; // 1
    return (mod & 1) ^ 1;   // 1->0 ,0 -> 1
}
