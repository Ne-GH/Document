#include<stdio.h>

#pragma c11 on
#if __STDC_VERSION__!=201112L
#error 不是C11
#endif



// line 1000
#line 4 "预定义.c"
int func() {


	printf("%d \n", __LINE__);
	printf("%s \n", __func__);
	return 0;
}

int main() {
	printf("%s \n", __DATE__);
	printf("%s \n", __FILE__);
	printf("%d \n", __LINE__);
	printf("%s \n", __TIME__);
	printf("%s \n", __func__);
	func();


	return 0;
}
