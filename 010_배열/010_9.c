//#include <stdio.h>
//
//int main(void) {
//	char str_1[80], str_2[80], temp[80];
//
//	printf("두 문자열 입력: ");
//	scanf_s("%s %s", str_1, sizeof(str_1), str_2, sizeof(str_2));
//
//	printf("변경 전: %s %s\n", str_1, str_2);
//
//	strcpy_s(temp, sizeof(temp), str_1);
//	strcpy_s(str_1, sizeof(str_1), str_2);
//	strcpy_s(str_2, sizeof(str_2), temp);
//
//	printf("변경 후: %s %s\n", str_1, str_2);
//
//	return 0;
//}