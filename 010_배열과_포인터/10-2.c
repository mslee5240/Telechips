#include <stdio.h>

int main(void) {
    int arr[3];

    *(arr + 0) = 10;
    *(arr + 1) = *(arr + 0) + 10;

    printf("세 번째 요소에 키보드 입력: ");
    scanf_s("%d", arr + 2);

    for (int i = 0; i < 3; i++) {
        printf("%5d", *(arr + i));
    }

    return 0;
}