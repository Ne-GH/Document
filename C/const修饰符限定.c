#include<stdio.h>

int main() {

	const ch1 = 1;
	//ch1 = 2;//�����������Ǵ����
    
	int ch2 = 1, ch3 = 2;
    // const ��������������Ҳ�����εĶ���
    // �˴������ǵľ��� *�����ָ��ָ�����ݲ����޸�
	const int* p1 = &ch2;
	p1 = &ch3;

    // �˴�����p4,���p4ָ�����ݲ����޸�
	int* const p4=&ch2;
	*p4 = 4;
	printf("%d\n", *p1);
	return 0;
}
