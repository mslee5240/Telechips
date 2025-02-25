// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 공용체
union student {
    int num1;
    double num2;
    char num3;  // -128 ~ 127
    short num4;
};
// 공용체는 저장 공간을 공유한다.


void app(void) {
    union student s1 = { 0x123456 };
    printf("num1: %x\n", s1.num1);
    // s1.grade = 4.4;
    printf("num2: %x\n", s1.num2);
    printf("num3: %x\n", s1.num3);
    printf("num4: %x\n", s1.num4);
}

