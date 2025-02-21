#include <stdio.h>

int main(void) {
    char str[80];

    printf("1. 공백이 포함된 문자열 입력: ");
    fgets(str, sizeof(str), stdin); // fgets 함수는 최대 배열의 크기까지만 문자열을 입력합니다.
    str[strlen(str) - 1] = '\0';    // 개행 문자 제거 과정
    printf("2. 입력한 문자열은 %s입니다.", str);

    return 0;
}