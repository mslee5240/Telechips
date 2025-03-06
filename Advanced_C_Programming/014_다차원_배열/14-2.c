// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app() {
    char mark[5][5] = { 0 };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == j || i == (4 - j)) {   // 최댓값에서 j 빼는 방법 (축을 뒤집는 방법)
                mark[i][j] = 'X';
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", mark[i][j]);
        }
        printf("\n");
    }
    
        
}