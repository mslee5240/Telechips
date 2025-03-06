#include <stdio.h>

int main(void) {
    int arr[3] = { 10, 20, 30 };
    int* pa = arr;

    printf("배열의 값: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", *pa);
        pa++; // 허용되는 연산, 포인터 변수이기 때문
    }

    // printf("배열의 값: ");
    // for (int i = 0; i < 3; i++) {
    //     printf("%d ", arr);
    //     arr++; // 허용되지 않는 연산, 주소 상수이기 때문
    // }

    return 0;
}