#include<stdio.h>
#include<stdlib.h>//qsort的库
int main() {
	int cmp_z(const void*, const void*);//固定的形参
	int cmp_f(const void*, const void*);
	int a[20] = { 1,3,6,8,3,7,3,8,0,8,9,5,2,3,6 };
	(*qsort)(a + 5, 15, sizeof(int), cmp_z);//对前16各元素进行排序\
	                                       第三个参数表示数组类型
	for (int i = 0; i < 20; i++)
		printf("%d ", a[i]);
	return 0;
}

int cmp_z(const void* a, const void* b) {//正
	return (*(int*)a - *(int*)b);
}

int cmp_f(const void* a, const void* b) {//反
	return  (*(int*)b - *(int*)a);//对其它类型的数据排序,\
								  强制转化为其他类型的指针 
}