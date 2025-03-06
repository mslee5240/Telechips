#include <stdio.h>

// array vs pointer
int main(void) {
    int arr[4] = { 0 };

    for (int i = 0; i < 4; i++) {
        printf("arr[%d]의 주소: %p\n", i, &arr[i]);
    }


    return 0;
}