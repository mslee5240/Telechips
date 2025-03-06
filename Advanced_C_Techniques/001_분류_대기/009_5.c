#include <stdio.h>

int recursive_func(int n) {
	if (n == 1) {
		return 1;
	}

	return n * recursive_func(n - 1);
}

int main(void) {
	int result = recursive_func(5);
	printf("%d", result);
	
	return 0;
}