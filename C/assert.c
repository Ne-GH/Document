#include<stdio.h>
#include<assert.h>
int main() {
	int n = 1;
	// 如果assert参数为true,则继续执行
	assert(n);
	printf("true\n");

	int num = 0;
	// 如果assert参数为false,则停止执行,并显示位置等信息
	assert(num);
	printf("false\n");
	return 0;
}