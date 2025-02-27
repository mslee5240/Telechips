#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 구조체 선언 (명시적)
struct student1 {
    int num;        // int형 멤버
    double grade;   // double형 멤버
};

// 구조체 선언 (암시적)
typedef struct {
    int num;
    double grade;
} student2_t;

void app(void) {
    struct student1 s1;  // 구조체를 사용한 변수 선언, struct student1형의 변수 선언
    student2_t s2;

    s1.num = 2;
    s1.grade = 2.7;
    printf("1_학번: %d\n", s1.num);
    printf("1_학점: %.1lf\n", s1.grade);

    s2.num = 3;
    s2.grade = 3.8;
    printf("2_학번: %d\n", s2.num);
    printf("2_학점: %.1lf\n", s2.grade);
    printf("1_구조체 크기: %d\n", sizeof(struct student1));
    printf("2_구조체 크기: %d", sizeof(student2_t));
    // 구조체는 큰 데이터 타입을 기준으로 맞춰서 size를 span해서 16바이트가 나옴
    

}
