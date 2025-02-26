#include <stdio.h>

int main(void) {
	char ch;
	int in;
	double db;

	char* pch = &ch;
	int* pin = &in;
	double* pdb = &db;

	printf("char�� ������ �ּ� ũ��: %d\n", sizeof(&ch));
	printf("int�� ������ �ּ� ũ��: %d\n", sizeof(&ch));
	printf("double�� ������ �ּ� ũ��: %d\n\n", sizeof(&ch));

	printf("char ������ ������ ũ��: %d\n", sizeof(pch));
	printf("int ������ ������ ũ��: %d\n", sizeof(pin));
	printf("double ������ ������ ũ��: %d\n\n", sizeof(pdb));

	printf("char �����Ͱ� ����Ű�� ������ ũ��: %d\n", sizeof(*pch));
	printf("int �����Ͱ� ����Ű�� ������ ������ ũ��: %d\n", sizeof(*pin));
	printf("double �����Ͱ� ����Ű�� ������ ������ ũ��: %d\n\n", sizeof(*pdb));

	return 0;
}