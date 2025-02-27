#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// memset, memcpy 함수 사용

void app(void) {
    int* pa;
    int* pb;
    pa = (int*)malloc(5 * sizeof(int));
    pb = (int*)malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        pa[i] = (i + 1) * 100;
    }

    for (int i = 0; i < 5; i++) {
        printf("%5d", pa[i]);
    }
 
    // memset(pa, 0, 5 * sizeof(int)); // 메모리를 0으로 초기화
    // memset(pa, 0xff, 5 * sizeof(int));
    // memset(pa, 1, 5 * sizeof(int));

    // memset(pa, 0, 5 * sizeof(int));
    // for (int i = 0; i < 5; i++) {
    //     printf("%5d", pa[i]);
    // }

    memcpy(pb, pa, 5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        printf("%5d", pb[i]);
    }

}
