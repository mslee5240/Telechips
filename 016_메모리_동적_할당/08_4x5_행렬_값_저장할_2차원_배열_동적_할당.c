#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int **matrix = (int *)malloc(4 * sizeof(int *)); // 포인터 배열로 사용할 공간의 동적 할당

    for (int i = 0; i < 4; i++) {
        matrix[i] = (int *)malloc(5 * sizeof(int)); // 각 행을 동적 할당해 포인터 배열에 연결
    }

    for (int i = 0; i < 4; i++) { // 각 행의 동적 할당 영역 반환
        free(matrix[i]);
    }

    free(matrix); // 포인터 배열로 사용한 동적 할당 영역 반환

    return 0;
}