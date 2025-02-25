// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void app(void) {
    int* pi;
    int size = 5;
    int cnt = 0;
    int num;

    pi = (int*)calloc(size, sizeof(int)); // 먼저 5개의 저장 공간 할당
    while (1) {
        printf("양수만 입력하세요 => ");
        scanf("%d", &num);
        if (num <= 0) {
            break;
        }
        if (cnt == size) {
            size += 5;
            pi = (int *)realloc(pi, size * sizeof(int));
        }
        pi[cnt++] = num;
    }

    for (int i = 0; i < cnt; i++) {
        printf("%5d", pi[i]);
    }

    free(pi);

}
