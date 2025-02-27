#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 패딩 바이트(padding byte), 바이트 얼라인먼트(byte alignment)
// 멤버의 순서에 따라 구조체의 크기가 달라질 수 있으므로
// 패딩 바이트가 가장 작도록 구조체를 선언하면 메모리를 아낄 수 있다.

struct student1 {
    char    ch1;
    short   num;
    char    ch2;
    int     score;
    double  grade;
    char    ch3;
};

typedef struct {
    char    ch1;
    char    ch2;
    short   num;
    int     score;
    double  grade;
    char    ch3;
} student2_t;

int main(void) {
    struct student1 s1;  // 구조체를 사용한 변수 선언
    student2_t s2;

    printf("> 1_구조체 크기: %d\n", sizeof(struct student1)); // 32바이트
    printf("> 2_구조체 크기: %d", sizeof(student2_t));        // 24바이트

    return 0;
}
