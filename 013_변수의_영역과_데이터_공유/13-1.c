#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 전역변수에 언더바 붙이는 습관 int _a = 0;

void auto_func(void);
void static_func(void);

int main(void) {
    int i;

    printf("일반 지역 변수: \n");
    for (int i = 0; i < 3; i++) {
        auto_func();
    }

    printf("정적 지역 변수: \n");
    for (int i = 0; i < 3; i++) {
        static_func();
    }

    return 0;
}

void auto_func(void) {
    auto int a = 0;
    a++;
    printf("%d\n", a);
}

void static_func(void) {
    static int a;
    a++;
    printf("%d\n", a);
}