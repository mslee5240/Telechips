#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// . 연산자: 구조체 변수를 다룰 때 사용
// -> 연산자: 구조체 포인터를 다룰 때 사용

// 구조체 변수의 주소는 구조체 포인터에 저장되며, 구조체 변수 전체를 가리킨다.
struct score {
    int kor;
    int eng;
    int math;
};

int main(void) {
    // 방법 1
    struct score minsoo = { 90, 80, 70 };   // 구조체 변수 선언과 초기화
    struct score* ps_0 = &minsoo;           // 구조체 포인터에 주소 저장

    // 방법 2
    struct score* ps;
    ps = (struct score*)malloc(sizeof(struct score));
    ps->kor = 90;   // -> 연산자 사용
    ps->eng = 80;
    ps->math = 70;

    // 주의) 멤버에 접근하는 .가 *보다 우선순위가 높음
    printf("> 국어: %d\n", (*ps).kor);    // 구조체 포인터로 멤버 접근
    printf("> 영어: %d\n", ps->eng);
    printf("> 수학: %d\n", ps->math);

    return 0;
}
