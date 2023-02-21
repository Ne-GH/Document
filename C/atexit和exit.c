#include<stdio.h>
void print1(void) {

	printf("1\n");
	return;
}
void print2() {
	printf("2\n");

	return;
}


int main() {
	atexit(print1);
	atexit(print2);

	return 0;
}