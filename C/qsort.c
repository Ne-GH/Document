#include<stdio.h>
#include<stdlib.h>//qsort�Ŀ�
int main() {
	int cmp_z(const void*, const void*);//�̶����β�
	int cmp_f(const void*, const void*);
	int a[20] = { 1,3,6,8,3,7,3,8,0,8,9,5,2,3,6 };
	(*qsort)(a + 5, 15, sizeof(int), cmp_z);//��ǰ16��Ԫ�ؽ�������\
	                                       ������������ʾ��������
	for (int i = 0; i < 20; i++)
		printf("%d ", a[i]);
	return 0;
}

int cmp_z(const void* a, const void* b) {//��
	return (*(int*)a - *(int*)b);
}

int cmp_f(const void* a, const void* b) {//��
	return  (*(int*)b - *(int*)a);//���������͵���������,\
								  ǿ��ת��Ϊ�������͵�ָ�� 
}