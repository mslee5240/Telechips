#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    FILE *fp;
    char str[] = "banana";

    fp = fopen("b.txt", "w");
    if (fp == NULL) {
        printf("파일을 만들지 못했습니다.\n");
        return 1;
    }

    int i = 0;
    while (str[i] != '\0') {
        fputc(str[i], fp);
        i++;
    }
    fputc('\n', fp);
    fclose(fp);

    return 0;
}