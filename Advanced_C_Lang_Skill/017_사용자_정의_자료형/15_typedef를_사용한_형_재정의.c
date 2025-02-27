#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// typedef를 사용하면 자료형 이름에서 struct와 같은 예약어를 생략 가능
// 사용법: typedef 구조체_이름 새_자료형_이름;

// 방법_1: 재정의 후에도 자료형을 써야할 때
struct student {
    int     num;
    double  grade;
};
typedef struct student student_t;   // student_t형으로 재정의

// 방법_2: 형 선언과 동시에 재정의
typedef struct {
    int     num;
    double  grade;
} Student_t;

void print_data(student_t* ps);     // 매개변수는 student_t형의 포인터

int main(void) {
    student_t s1 = { 777, 4.5 };    // student_t형의 변수 선언과 초기화

    student_t* ps1 = &s1;

    print_data(ps1);                // student_t형 변수의 주소 전달

    return 0;
}

void print_data(student_t* ps) {
    printf("학번: %d\n", ps->num);      // student_t 포인터로 멤버 접근
    printf("학점: %.1lf\n", ps->grade);
}

// typedef문으로 기본 자료형 재정의
typedef unsigned int nbyte;