#include <stdio.h>

long long int get_num(void);

int main() {
	int result;

	result = get_num();
	printf("��ȯ��: %d\n", result);

	return 0;
}

long long int get_num(void) {
	long long int num;
	printf("���� �Է�: ");
	scanf_s("%lld", &num);
	return num;
}
