#include<stdio.h>
int main() {
	int a = 010;
	int b = 0x11;
	printf("%x\n", a);
	printf("%#o\n", a);
	printf("%x\n", b);
	printf("%#x\n", b);

	return 0;
}