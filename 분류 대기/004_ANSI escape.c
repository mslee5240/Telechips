#include <stdio.h>
#include <stdlib.h>

#define ESC 0x1b // \033

// ANSI escape code, CSI code

int main() {
	while (1) {
		char ch = getch();
		putchar(ch);

		if (ch == '1') {
			return 0;
		}

		if (ch == '2') {
			printf("\033[2J\033[H");
			// "\033"은 escape 문자로, 이후 오는 문자들이 
			// 특별한 제어 문자로 해석되도록 합니다.
			// [2J : 화면을 지우는 명령
			// [H : 커서를 화면의 왼쪽 상단으로 이동
			
			/*
			putchar(ESC);
			putchar('[');
			putchar('0');
			putchar('J');
			*/
		}
		
	}
	return 0;
}