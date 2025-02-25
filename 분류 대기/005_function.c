#include <stdio.h>
#include <stdlib.h>

int func(int a, int b); // 함수 프로토타입

int main(void) {
	int sum_1 = func(100, 50);
	printf("Sum_1 = %d\n", sum_1);

	int sum_2 = func(100, 50);
	printf("Sum_1 = %d\n", sum_2);

	return 0;
}

int func(int a, int b) {
	printf("Hello World! %d\n", a + b);
	static int s = 0;
	s += (a + b);
	return s;
}