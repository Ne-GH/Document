// 实现(int)float
int floatFloat2Int(unsigned uf) {
    unsigned mask = 0xff << 23;
    unsigned sign = uf & (1 << 31);
    // 移码 -127
    int exponential = ((uf & mask) >> 23) - 127;
    unsigned mantissa =  uf & ~mask & ~(1 << 31);
    int ret;
    mantissa = mantissa | 1 << 23;
    ret = mantissa;
    // int无法表示，溢出
    if (exponential > 31) {
        return 0x80000000u;
    }
    else if (exponential < 0) {
        return 0;
    }
    // else 0 <= exponential <= 31
    exponential -= 23;
    if (exponential > 0){
        ret <<= exponential;
    }
    else {
        ret >>= -exponential;
    }
    if (sign == 0)
        return ret;
    else {
        return ~ret + 1;
    }

}
