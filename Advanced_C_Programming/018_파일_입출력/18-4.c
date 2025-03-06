#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 표준 입출력 스트림을 사용한 문자열 입력
int main(void) {
    int ch;

    while (1) {
        ch = getchar();
        if (ch == EOF) {
            break;
        }
        putchar(ch);
    }

    return 0;
}