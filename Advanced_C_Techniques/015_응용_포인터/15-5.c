// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void func(int (*fp)(int, int));     // 함수 포인터를 매개변수로 갖는 함수
int sum(int a, int b);
int mul(int a, int b);
int maX(int a, int b);

void app(void) {
    int sel;
    

    printf("01 두 정수의 합\n");
    printf("02 두 정수의 곱\n");
    printf("03 두 정수 중에서 큰 값 계산\n");
    printf("원하는 연산을 선택하세요.: ");
    scanf("%d", &sel);

    switch (sel) {
    case 1: func(sum); break;
    case 2: func(mul); break;
    case 3: func(maX); break;
    }
}

void func(int (*fp)(int, int)) {
    int a, b;
    int res;

    printf("두 정수의 값을 입력하세요.: ");
    scanf("%d%d", &a, &b);
    res = fp(a, b);
    printf("결괏값은: %d\n", res);
}

int sum(int a, int b) {
    return (a + b);
}

int mul(int a, int b) {
    return (a * b);
}

int maX(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

