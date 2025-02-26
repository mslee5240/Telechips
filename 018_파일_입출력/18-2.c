#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    FILE *fp;
    int ch;

    fp = fopen("C:\\Users\\eec04\\source\\repos\\Telechips\\Telechips\\playground\\a.txt", "r");
    if (fp == NULL) {
        printf("파일이 열리지 않았습니다.\n");
        return 1;
    }

    while (1) {
        ch = fgetc(fp);     // 개방한 파일에서 문자 입력
        if (ch == EOF) {
            break;
        }
        putchar(ch);
    }
    fclose(fp);

    return 0;
}
