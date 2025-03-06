#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 공용체의 경우 모든 멤버가 하나의 저장 공간을 같이 사용
// 공용체 변수의 크기는 멤버 중에서 크기가 가장 큰 멤버로 결정

union student {     // 공용체 선언
    int     num1;
    double  num2;
    char    num3;  // -128 ~ 127
    short   num4;
};

int main(void) {
    union student s1 = { 0x12345678 };    // 공용체 변수의 선언과 초기화
    // 공용체 변수의 초기화는 중괄호를 사용해 첫 번째 멤버만 초기화합니다.

    printf("> 공용체 초기화 값(0x12345678)\n");
    printf("> int형, num1: %x\n", s1.num1);
    printf("> double형, num2: %x\n", s1.num2);
    printf("> char형, num3: %x\n", s1.num3);
    printf("> short형, num4: %x\n\n", s1.num4);

    printf("> 멤버 num2에 값(7.7) 대입 후: \n");
    s1.num2 = 7.7;

    printf("> int형, num1: %d\n", s1.num1);
    printf("> double형, num2: %.1lf\n", s1.num2);
    printf("> char형, num3: %d\n", s1.num3);
    printf("> short형, num4: %d\n", s1.num4);

    return 0;
}

