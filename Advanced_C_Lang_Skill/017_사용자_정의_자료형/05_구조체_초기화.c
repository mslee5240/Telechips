#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 구조체 선언을 함수 밖에서 하면 함께 선언되는 변수가 전역 변수가 되므로
// 별도로 초기화하지 않을 경우 모든 멤버가 0으로 자동 초기화됩니다.
struct student_0 {
    int     id;
    char    name[20];
    double  grade;
} s0 = { 315, "홍길동", 2.4 };  // 구조체 선언과 동시에 데이터 넣기

struct student {
    int     id;
    char    name[20];
    double  grade;
};

int main(void) {
    struct student s1 = { 315, "홍길동", 2.4 },     // 구조체 변수 선언과 초기화
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

    printf("> 학번: %d\n", max.id);
    printf("> 이름: %s\n", max.name);
    printf("> 학점: %.1lf\n", max.grade);

    return 0;
}
