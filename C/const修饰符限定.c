#include<stdio.h>

int main() {
	const ch1 = 1;
	//ch1 = 2;//毫无疑问这是错误的
	int ch2 = 1, ch3 = 2;
	const int* p1 = &ch2;
	//const修饰符在前面时不能修改指向的数据
	p1 = &ch3;
	int* const p4=&ch2;
	//const修饰符在后面时不能改变指针指向
	*p4 = 4;
	printf("%d\n", *p1);
	return 0;
}