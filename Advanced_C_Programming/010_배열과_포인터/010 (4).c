#include <stdio.h>

void swap(int* pa, int* pb) {
	int temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

int main(void) {
	int a = 10, b = 20;

	printf("���� ��, a = %d, b = %d\n", a, b);

	swap(&a, &b);

	printf("���� ��, a = %d, b = %d\n", a, b);

	return 0;
}