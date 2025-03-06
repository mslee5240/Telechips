#include <stdio.h>

int main(void) {
    int age;
    char name[20];

    printf("나이 입력: ");
    scanf_s("%d", &age);

    printf("이름 입력: ");
    gets(name); // 버퍼에 개행문자가 남아서 오류 발생생
    printf("나이: %d, 이름: %s\n", age, name);

    return 0;
}