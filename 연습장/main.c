#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


//int main(void) {
//    app();
//
//    return 0;
//}

int main(void) {
	char str_1[80] = "applejam";
	char str_2[80] = { 'a', 'p', 'p', 'l', 'e', 'j', 'a', 'm' };


	printf("����: %s\n", str_1);
	printf("�Է�: ");
	scanf_s("%s", str_1, sizeof(str_1));
	str_1[5] = '_';
	printf("�Է� �� ���ڿ�: %s", str_1);

	return 0;
}