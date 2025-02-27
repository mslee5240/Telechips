#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 구조체 선언 (명시적)
struct student1 {
    int     num;        // int형 멤버
    double  grade;   // double형 멤버
};

// 구조체 선언 (암시적)
typedef struct {
    int     num;
    double  grade;
} student2_t;

int main(void) {
    struct student1 s1;  // 구조체를 사용한 변수 선언, struct student1형의 변수 선언
    student2_t s2;

    s1.num = 2;
    s1.grade = 2.7;
    printf("> S1_학번: %d\n", s1.num);      // 멤버 접근 연산자(.)
    printf("> S1_학점: %.1lf\n", s1.grade);

    s2.num = 3;
    s2.grade = 3.8;
    printf("> S2_학번: %d\n", s2.num);
    printf("> S2_학점: %.1lf\n", s2.grade);

    printf("> S1_구조체 크기: %d\n", sizeof(struct student1));
    printf("> S2_구조체 크기: %d", sizeof(student2_t));
    // 크기가 가장 큰 멤버가 메모리를 할당하는 기준 단위가 됨.
    // 패딩 바이트(padding byte), 바이트 얼라인먼트(byte alignment)
    // 구조체는 큰 데이터 타입을 기준으로 맞춰 size를 span함 => 16바이트가 나옴

    return 0;
}
