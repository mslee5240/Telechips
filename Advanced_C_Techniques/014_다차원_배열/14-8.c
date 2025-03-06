// pArr[2][2] == *(pArr[2] + 2)

// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app(void) {
    int a[5][6] = { 0 };
    int cnt = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            a[i][j] = cnt;
            a[i][5] += cnt;
            a[4][j] += cnt;
            a[4][5] += cnt;
            cnt++;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == 5) {
                printf("|");
            }
            printf("%5d", a[i][j]);
        }
        printf("\n");
    }

}