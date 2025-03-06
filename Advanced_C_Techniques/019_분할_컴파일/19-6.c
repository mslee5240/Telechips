// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app() {
    int score_1[3][4];
    int score_2[12];
    int total;
    double avg;

    for (int i = 0; i < 3; i++) {
        printf("4과목의 점수 입력: ");
        for (int j = 0; j < 4; j++) {
            scanf("%d", &score_1[i][j]);
        }
    }

    memcpy(score_2, score_1, 12 * sizeof(int));

    for (int i = 0; i < 3; i++) {
        total = 0;
        for (int j = 0; j < 4; j++) {
            total += score_2[i * 4 + j];
        }
        avg = total / 4.0;
        printf("총점: %d, 평균: %.2lf\n", total, avg);
    }
}



// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a, b;

int main(void) {
    app();

    return 0;
}



