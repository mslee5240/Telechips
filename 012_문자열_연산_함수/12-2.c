#include <stdio.h>

int main(void) {
    char str[80];

    printf("1. 문자열 입력: ");
    scanf_s("%s", str, sizeof(str));
    printf("2. 첫 번째 단어: %s\n", str);
    scanf_s("%s", str, sizeof(str));
    printf("3. 버퍼에 남아 있는 두 번째 단어: %s\n", str);

    return 0;
}