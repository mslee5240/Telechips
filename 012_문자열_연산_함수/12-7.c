#include <stdio.h>

int main(void) {
    int age;
    char name[20];

    printf("나이 입력: ");
    scanf_s("%d", &age);

    getchar();      // 해결 방법 1
    // scanf_s("%*c"); // 해결 방법 2
    // fgetc(stdin);   // 해결 방법 3

    printf("이름 입력: ");
    gets(name); 
    printf("나이: %d, 이름: %s\n", age, name);

    return 0;
}