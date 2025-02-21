#include <stdio.h>

int rec_func(int n) {
	if (n == 1) return 1;
	return n * rec_func(n - 1);
}

int main(void) {
	int result = rec_func(5);
	printf("%d", result);
	return 0;
}