#include<stdio.h>
#include<stdlib.h>
int main() {
	char* end;
	char str[20];
	scanf("%s", str);
	printf("%ld\n", strtol(str, &end, 16));//�з��ŵ�n����
	printf("%ld\n", strtoul(str, &end, 16));//�޷��ŵ�n����
	printf("%f\n", strtod(str, &end));//ת��Ϊ������
	return 0;
}
