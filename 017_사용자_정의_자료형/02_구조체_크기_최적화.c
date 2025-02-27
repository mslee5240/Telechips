// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 패딩 바이트(padding byte), 바이트 얼라인먼트(byte alignment)

// 구조체 선언 (명시적)
struct student1 {
    char ch1;
    short num;
    char ch2;
    int score;
    double grade;
    char ch3;
};

// 구조체 선언 (암시적)
typedef struct {
    char ch1;
    char ch2;
    short num;
    int score;
    double grade;
    char ch3;
} student2_t;

void app(void) {
    struct student1 s1;  // 구조체를 사용한 변수 선언
    student2_t s2;

    
    printf("1_구조체 크기: %d\n", sizeof(struct student1));
    printf("2_구조체 크기: %d", sizeof(student2_t));
    

}
