#include <stdio.h>

int main(void) {
    // 초기화 방법
	char str_1[80] = "applejam";
	char str_2[80] = { 'a', 'p', 'p', 'l', 'e', 'j', 'a', 'm' };


	printf("최초: %s\n", str_1);
	printf("입력: ");
	scanf_s("%s", str_1, sizeof(str_1));
	str_1[5] = '_';
	printf("입력 후 문자열: %s", str_1);

	return 0;
}