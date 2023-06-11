#include<stdio.h>

int main() {

	const ch1 = 1;
	//ch1 = 2;//毫无疑问这是错误的
    
	int ch2 = 1, ch3 = 2;
    // const 修饰离他最近的右侧可修饰的对象
    // 此处修饰是的就是 *，因此指针指向内容不可修改
	const int* p1 = &ch2;
	p1 = &ch3;

    // 此处修饰p4,因此p4指向内容不可修改
	int* const p4=&ch2;
	*p4 = 4;
	printf("%d\n", *p1);
	return 0;
}
