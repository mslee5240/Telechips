#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 열거형은 변수에 저장할 수 있는 정수 값을 기호로 정의해서 나열
// 컴파일러는 멤버를 0부터 차례로 하나씩 큰 정수로 바꿈

enum season {   // 열거형 선언
    SPRING, // 0
    SUMMER, // 1
    FALL,   // 2
    WINTER  // 3
};

int main(void) {
    enum season ss;     // 열거형 변수 선언
    char* pc = NULL;

    ss = SPRING;
    //ss = 0;
    switch (ss) {
    case SPRING:
        pc = "inline";
        break;
    case SUMMER:
        pc = "swimming";
        break;
    case FALL:
        pc = "trip";
        break;
    case WINTER:
        pc = "skiing";
        break;
    }
    printf("> 나의 레저 활동: %s\n", pc);

    return 0;
}
