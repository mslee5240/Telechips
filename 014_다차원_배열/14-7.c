// pArr[2][2] == *(pArr[2] + 2)

// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app(void) {
    char a[4][20] = { "horse", "fox", "hippo", "tiger" };
    char* pa[] = { a[0], a[1], a[2], a[3] };
    int cnt;

    cnt = sizeof(pa) / sizeof(pa[0]);


    for (int i = 0; i < cnt; i++) {
        printf("%c ", pa[i][i]);
    }

}