//app.c
#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>

void app() {
    int score[3][4];    // 만약, 1차원 배열로 구성한다면, score[12];
    int total;
    double avg;

    for (int i = 0; i < 3; i++) {
        printf("4과목의 점수 입력: ");
        for (int j = 0; j < 4; j++) {
            scanf("%d", &score[i][j]); // 만약, 1차원 배열로 구성한다면, &score[i * 4 + j]
        }
    }

    for (int i = 0; i < 3; i++) {
        total = 0;
        for (int j = 0; j < 4; j++) {
            total += score[i][j];   // 만약, 1차원 배열로 구성한다면, &score[i * 4 + j]
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



