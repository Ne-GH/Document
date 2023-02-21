#include<stdio.h>
#include<stdbool.h>
#include<math.h>
//_Bool c[10000];//无stdbool.h头文件
bool d[20000];//有stdbool.h头文件
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 2; i < sqrt(n); i++)
		if (d[i] == 0)
			for (int j = i * 2; j <= n; j += i)
				d[j] = 1;

	for (int i = 2; i <= n; i++)
		if (d[i] == 0)
			printf("%d ", i);

	return 0;
}
