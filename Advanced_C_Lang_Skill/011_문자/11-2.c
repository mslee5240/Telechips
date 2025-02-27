#include <stdio.h>

int main(void) {
    char ch = 0;

    for (int i = 0; i < 3; i++) { // 버퍼를 사용하는 입력 함수의 특징 이해
        scanf_s("%c", &ch);
        printf("%c", ch);
    }

    return 0;
}