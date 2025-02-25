// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app(void) {
    int arr_1[4] = { 1, 2, 3, 4 };
    int arr_2[4] = { 5, 6, 7, 8 };
    int arr_3[5] = { 9, 10, 11, 12, 13 };
    int* pArr[3] = { arr_1, arr_2, arr_3 };
    int* pa = arr_3;

    for (int i = 0; i < 4; i++) {
        printf("%5d", *(pa++));
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%5d", pArr[i][j]);
        }
        printf("\n");
    }

}