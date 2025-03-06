#include <stdio.h>

long long int get_num(void);

int main() {
	int result;

	result = get_num();
	printf("반환값: %d\n", result);

	return 0;
}

long long int get_num(void) {
	long long int num;
	printf("정수 입력: ");
	scanf_s("%lld", &num);
	return num;
}
