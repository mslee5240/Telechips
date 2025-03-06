// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app() {
    int score[2][3][4] = {
        { { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 } }, 
        { { 1, 2, 3, 4 }, { 1, 2, 3, 4 }, { 1, 2, 3, 4 } }
    };

    for (int i = 0; i < 2; i++) {
        printf("%d반 점수...\n", i + 1);
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                printf("%5d", score[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
        
}



// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    app();

    return 0;
}



