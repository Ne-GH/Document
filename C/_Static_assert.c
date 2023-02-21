#include <stdio.h>
#include <limits.h>
#include <assert.h>


int main() {
	// 如果第一个参数表达式为true,则无反应
	static_assert(sizeof(char) == 1, "true");

	// 如果第一个参数表达式为false,则编译出错,原因为第二个参数
	static_assert(sizeof(int) == 1, "false");

	puts("qwe");
	return 0;
}