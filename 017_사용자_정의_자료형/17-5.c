// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct profile {
    int age;
    double  height;
};

struct student {
    struct profile pf;  // profile 구조체를 멤버로 사용용
    int id;
    double grade;
};

void app(void) {

    struct student ms;

    ms.pf.age = 27;
    ms.pf.height = 176.5;
    ms.id = 202104135;
    ms.grade = 3.5;

    printf("나이: %d\n", ms.pf.age);
    printf("키: %.1lf\n", ms.pf.height);
    printf("학번: %d\n", ms.id);
    printf("학점: %.1lf\n", ms.grade);

}
