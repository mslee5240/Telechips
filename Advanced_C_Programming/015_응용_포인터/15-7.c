// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void 포인터: 가리키는 자료형이 정해지지 않은 포인터다.
// 가르키는 자료형이 일치하는 포인터에만 주소를 대입할 수 있습니다.
// 따라서 가리키는 자료형이 다른 주소를 저장하는 경우라면 void 포인터를 사용해야 합니다.

void app(void) {
    int a = 10;
    double b = 3.5;
    void *vp;

    vp = &a;
    printf("a : %d\n", *(int *)vp);
    
    vp = &b;
    printf("b : %.1lf\n", *(double *)vp);

}



