#include <stdio.h>

int main(void) {
    char ch = 0;

    printf("문자 입력: ");
    ch = getchar();
    //scanf_s("%c", &ch);

    printf("아스키 코드 값: %d", ch);

    return 0;
}