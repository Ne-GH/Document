// 实现2.0 ^ x
unsigned floatPower2(int x) {
    int exponential = x;
    if (exponential > 127)
        return 0xff << 23;
    else if (exponential < 0)
        return 0;
    return ((exponential+127) << 23);
}
