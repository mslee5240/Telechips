// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// struct student {
//     int id;
//     char name[20];
//     double  grade;
// } s1 = { 315, "홍길동", 2.4 };  // 구조체 선언과 동시에 데이터 넣기

struct student {
    int id;
    char name[20];
    double  grade;
};

void app(void) {
    
    struct student s1 = { 315, "홍길동", 2.4 },
                    s2 = { 316, "박길동", 3.4 },
                    s3 = { 317, "이길동", 4.4 };

    struct student max;

    max = s1;
    if (s2.grade > max.grade) {
        max = s2;
    }
    if (s3.grade > max.grade) {
        max = s3;
    }

    printf("학번: %d\n", max.id);
    printf("이름: %s\n", max.name);
    printf("학점: %.1lf\n", max.grade);

}
