#include <stdio.h>

int main(void) {
    int num, grade;

    printf("학번 입력: ");
    scanf_s("%d", &num);
    getchar();  // 버퍼에 남아 있는 개행 문자 제거!
    printf("학점 입력: ");
    scanf_s("%d", &num);
    grade = getchar();
    printf("학번: %d, 학점: %c", num, grade);

    return 0;
}
