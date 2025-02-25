#include <stdio.h>

void print(char inText[]) {
	// for (int i = 0; i < strlen(inText); i++) {
	// 	putchar(inText[i]);
	// }

	int i = 0;
	while (1) {
        if (inText[i] == 0) { // '0' == '\0' == NULL 값 만나면 중지
            break;
        }
		putchar(inText[i]);
		i++;
	}
    putchar('\n');
    putchar('\n');
}

int main(void) {
	char str[80] = "AppleJam";

	print(str);

	printf("최초 문자열: %s\n", str);
	printf("문자열 입력: ");
	scanf("%s", str);
    // 기존 값이 사라지고, 새 입력값이 덮어쓰기되며, 마지막에 '\0'	
	printf("입력 후 문자열: %s\n", str);

    printf("문자열 메모리 상태 확인: ");
    for (int i = 0; i < 20; i++) {
        if (str[i] == '\0') {
            printf("\\0");
        }
        else {
            printf("%c ", str[i]);
    
        }
    }
    

	return 0;
}