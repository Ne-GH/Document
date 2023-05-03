// 返回浮点数*2的结果，如果阶码为0xff表示NAN,返回原值
unsigned floatScale2(unsigned uf) {

    unsigned mask = 0xff << 23;
    // 阶码
    unsigned char exponential = (uf & mask) >> 23;
    // 尾数
    unsigned mantissa = uf & ~mask & ~(1 << 31);

    // uf 仅保留符号
    uf = (uf & 1 << 31);
    // 阶码为0x0 或 0xff,不处理阶码
    !(!exponential || !(exponential ^ 0xff)) && (exponential += 1);
    // 阶码为0,尾数*2
    !exponential && (mantissa <<= 1);

    mask = exponential << 23;
    uf = uf | mask | mantissa;
    return uf;

}
