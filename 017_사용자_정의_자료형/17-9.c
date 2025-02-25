// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct score {
    int kor;
    int eng;
    int math;
};

void app(void) {
    // 방법 1
    // struct score yuni = { 90, 80, 70 };
    // struct score *ps = &yuni;

    // 방법 2
    struct score* ps;
    ps = malloc(sizeof(struct score));
    ps->kor = 90;
    ps->eng = 80;
    ps->math = 70;

    printf("국어: %d\n", (*ps).kor);
    printf("영어: %d\n", ps->eng);
    printf("수학: %d\n", ps->math);


}

