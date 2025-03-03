#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int     id;
    char    name[20];
    int     kor;
    int     eng;
    int     math;
    int     total;
    double  average;
    char    grade;
} Student;

void input_data(Student* pary);
void calc_data(Student* pary);
void sort_data(Student* pary);
void print_data(Student* pary);

int main(void) {
    Student ary[5];     // 5명 학생의 성적

    input_data(ary);
    calc_data(ary);

    printf("# 정렬 전 데이터...\n");
    print_data(ary);    // 정렬 전 출력
    sort_data(ary);     // 총점 순으로 내림차순 정렬
    printf("\n# 정렬 후 데이터...\n");
    print_data(ary);    // 정렬 후 출력
    
    return 0;
}

void input_data(Student* pary) {
    for (int i = 0; i < 5; i++) {
        printf("> 학번 :  ");
        scanf("%d", &pary->id);     // == pary[0].num
        printf("> 이름 :  ");
        scnaf("%s", &pary->name);
        printf("> 국어 영어 수학 점수 :  ");
        scanf("%d %d %d", &pary->kor, &pary->eng, &pary->math);
        pary++;
    }
}

void calc_data(Student* pary) {
    for (int i = 0; i < 5; i++) {
        pary->total = pary->kor + pary->eng + pary->math;
        pary->average = pary->total / 3.0;

        if (pary->average >= 90.0) {
            pary->grade = 'A';
        }
        else if (pary->average >= 80) {
            pary->grade = 'B';
        }
        else if (pary->average >= 70) {
            pary->average = 'C';
        }
        else if (pary->average >= 60) {
            pary->average = 'D';
        }
        else {
            pary->average = 'F';
        }
    }
    pary++;
}

void print_data(Student* pary) {
    for (int i = 0; i < 5; i++) {
        printf("%5d %7s %5d %5d %5d %5d %7.1lf %5c\n",
            pary->id, pary->name, pary->kor, pary->eng, pary->math, 
            pary->total, pary->average, pary->grade);
        pary++;
    }
}

void sort_data(Student* pary) {
    Student temp;
    int max_index;

    for (int i = 0; i < 4; i++) {
        max_index = i;
        for (int j = i + 1; j < 5; j++) {
            if (pary[max_index].total < pary[j].total) {
                max_index = j;
            }
        }
        if (max_index != i) {
            temp = pary[max_index];
            pary[max_index] = pary[i];
            pary[i] = temp;
        }
    }
}