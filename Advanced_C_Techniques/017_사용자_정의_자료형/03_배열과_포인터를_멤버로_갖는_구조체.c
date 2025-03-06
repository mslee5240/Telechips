#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct profile {
    char    name[20];
    int     age;
    double  height;
    char*   intro;       // 포인터이므로 문자열 자체를 저장할 공간은 없음
};                       // 동적 할당을 통해 적당 한 크기의 저장 공간을 먼저 확보해야 함

int main(void) {
    struct profile ms;  // 구조체를 사용한 변수 선언

    strcpy(ms.name, "이민수");
    ms.age = 27;
    ms.height = 176.5;

    ms.intro = (char*)malloc(80);
    printf("> 자기소개: ");
    gets(ms.intro);

    printf("> 이름: %s\n", ms.name);
    printf("> 나이: %d\n", ms.age);
    printf("> 키: %.1lf\n", ms.height);
    printf("> 자기소개: %s\n", ms.intro);

    free(ms.intro);

    return 0;
}
