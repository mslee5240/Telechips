// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void app(void) {
    int* pi;
    int size = 5;
    int cnt = 0;
    int num;

    // calloc(배열 요소의 개수, 변수 하나의 바이트 크기);
    // calloc 함수는 할당된 저장 공간을 모두 0으로 초기화.
    pi = (int*)calloc(size, sizeof(int)); // 먼저 5개의 저장 공간 할당
    while (1) {
        printf("양수만 입력하세요 => ");
        scanf("%d", &num);
        if (num <= 0) {
            break;
        }
        if (cnt == size) {
            size += 5;
            // realooc(이미 할당한 저장 공간의 포인터, 재할당 후 전체 저장 공간의 크기);
            // 저장 공간을 늘리는 경우 이미 입력한 값은 그대로 유지되며 추가된 공간에는 쓰레기 값이 존재.
            // 저장 공간을 줄이는 경우라면 입력된 데이터는 잘려 나감.
            // 저장 공간의 크기를 조정한 후에는 다시 그 주소를 반환하므로 포인터에 저장해 사용
            pi = (int *)realloc(pi, size * sizeof(int)); 
        }
        pi[cnt++] = num;
    }

    for (int i = 0; i < cnt; i++) {
        printf("%5d", pi[i]);
    }

    free(pi);

}
