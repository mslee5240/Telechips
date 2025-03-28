#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct profile {
    int     age;
    double  height;
};

struct student {
    struct  profile pf;  // profile 구조체를 멤버로 사용
    int     id;
    double  grade;
};

int main(void) {
    struct student ms;

    ms.pf.age = 27;         // pf 멤버의 age 멤버에 나이 저장
    ms.pf.height = 176.5;   // pf 멤버의 height 멤버에 나이 저장
    ms.id = 202104135;
    ms.grade = 3.5;

    printf("> 나이: %d\n", ms.pf.age);
    printf("> 키: %.1lf\n", ms.pf.height);
    printf("> 학번: %d\n", ms.id);
    printf("> 학점: %.1lf\n", ms.grade);

    return 0;
}
