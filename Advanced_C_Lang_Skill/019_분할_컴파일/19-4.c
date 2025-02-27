//app.c
#define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>

extern int a, b;

void input_data(int* pa, int* pb) {
    printf("두 정수 입력: ");
    scanf("%d %d", pa, pb);
}

void swap_data() {
    int tmp;

    tmp = a;
    a = b;
    b = tmp;
}

void print_data(int a, int b) {
    printf("두 정수 출력: %d %d", a, b);
}


// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a, b;

int main(void) {
    input_data(&a, &b);
    swap_data();
    print_data(a, b);

    return 0;
}



