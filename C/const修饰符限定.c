#include<stdio.h>

int main() {
	const ch1 = 1;
	//ch1 = 2;//�����������Ǵ����
	int ch2 = 1, ch3 = 2;
	const int* p1 = &ch2;
	//const���η���ǰ��ʱ�����޸�ָ�������
	p1 = &ch3;
	int* const p4=&ch2;
	//const���η��ں���ʱ���ܸı�ָ��ָ��
	*p4 = 4;
	printf("%d\n", *p1);
	return 0;
}