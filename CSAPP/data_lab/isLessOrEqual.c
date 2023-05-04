// x <= y ,return 1
// x >  y ,return 0
int isLessOrEqual(int x,int y) {
    
    int num = x + (~y+1) + (~1+1);
    int flag = num & (1 << 31);
    return !!flag;

}

// x64 汇编版本
int isLessOrEqual_x64_asm(int x,int y) {
    unsigned long long flags;
    int flag;
    char of;
    char zf;
    char sf;
    int num = x + (~y+1);
    asm (
            "pushfq \n"
            "popq %0 \n"
            : "=r" (flags)
            );
    flag = num & (1 << 31);
    of = (flags >> 11 & 1);
    zf = (flags >> 6 & 1);
    sf = (flags >> 7 & 1);
    // return ~((!!flag) | (of >> 11 & 1));
    return (sf ^ of) | zf;

}
