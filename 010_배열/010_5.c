//#include <stdio.h>
//
//void print(char inText[]) {
//	/*for (int i = 0; i < strlen(inText); i++) {
//		putchar(inText[i]);
//	}*/
//
//	int i = 0;
//	while (1) {
//		if (inText[i] == 0) return;	// 0, \0 , NULL 값 만나면 중지
//		putchar(inText[i]);
//		i++;
//	}
//}
//
//int main(void) {
//	char str[80] = "AppleJam";
//
//	print(str);
//
//	//printf("최초 문자열: %s\n", str);
//	//printf("문자열 입력: ");
//	//scanf_s("%s", str, sizeof(str));	// 기존 값이 사라지고 새 입력값이 덮어쓰기됨.
//	//printf("입력 후 문자열: %s\n", str);
//
//	return 0;
//}