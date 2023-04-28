/*
 * 仅使用~ 和 & 实现 ^
 */
int bitXor(int x,int y) {
    int num1 = ~(x & y);
    int num2 = ~(~x & ~y);
    return num1 & num2;
}

/*
 * 提示超时版本
 * 更新：超时是因为用于debug的printf被多次调用，注释即可
 */
int bitXor_time_out(int x,int y) {
   int num1 = (~x & y);
   int num2 = (x & ~y);

   int num3 = ~(num1 & num2);
   int num4 = (~num1 & ~num2);
   // printf("%d %d %d %d\n",num1,num2,num3,num4);
   return ~(num3 & num4);
}
