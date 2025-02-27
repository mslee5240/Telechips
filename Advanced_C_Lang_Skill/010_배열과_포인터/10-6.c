#include <stdio.h>

void print_arr(int* pa) {
    for (int i = 0; i < 5; i++) {
        printf("%d ", pa[i]);
    }
}

int main(void) {
    int arr[5] = { 10, 20, 30, 40, 50 };

    print_arr(arr);

    return 0;
}