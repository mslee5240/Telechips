#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// stdin과 stdout을 사용한 문자 출력
int main(void) {
    int ch;

    while (1) {
        ch = fgetc(stdin);
        if (ch == EOF) {
            break;
        }
        fputc(ch, stdout);
    }

    return 0;
}