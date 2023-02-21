#include<stdio.h>
#include<stdlib.h>
int main() {
	char* end;
	char str[20];
	scanf("%s", str);
	printf("%ld\n", strtol(str, &end, 16));//有符号的n进制
	printf("%ld\n", strtoul(str, &end, 16));//无符号的n进制
	printf("%f\n", strtod(str, &end));//转化为浮点数
	return 0;
}
