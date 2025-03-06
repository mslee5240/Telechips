#include <stdio.h>

void print_arr(int* pa, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", pa[i]);
    }
}

int main(void) {
    int arr_1[5] = { 10, 20, 30, 40, 50 };
    int arr_2[7] = { 10, 20, 30, 40, 50, 60, 70 };

    print_arr(arr_1, sizeof(arr_1) / sizeof(arr_1[0]));
    printf("\n");
    print_arr(arr_2, sizeof(arr_2) / sizeof(arr_2[0]));

    return 0;
}