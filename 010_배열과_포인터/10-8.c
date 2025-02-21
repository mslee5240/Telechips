#include <stdio.h>

void input_array(double *pa, int size);
double find_max(double *pa, int size);

int main(void) {
    double arr[5];
    double max = 0;
    int size = sizeof(arr) / sizeof(arr[0]);

    input_array(arr, size);
    max = find_max(arr, size);
    printf("최댓값: %.1lf\n", max);

    return 0;
}

void input_array(double *pa, int size) {
    printf("%d개의 실수값 입력: ", size);
    for (int i = 0; i < size; i++) {
        scanf_s("%lf", pa + i); // &pa[i] == pa + i
    }
}

double find_max(double *pa, int size) {
    double max = pa[0];
    for (int i = 1; i < size; i++) {
        if (pa[i] > max) { // (*(pa + i) == pa[i]
            max = pa[i];
        }
    }

    return max;
}