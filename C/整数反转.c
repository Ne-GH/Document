#include<stdio.h>
int reverse(int x) {
	long long y = 0;
	while (x != 0) {
		y = y * 10 + x % 10;
		x = x / 10;
	}
	if (y > (int)0x7fffffff || y < (int)0x80000000)
		//int 的最大值                   最小值
		return 0;
	else
		return (int)y;
}
int main() {
	int h = 123;
	printf("%d\n", reverse(h));


	return 0;
}