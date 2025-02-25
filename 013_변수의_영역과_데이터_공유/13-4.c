#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void add_ten(int* pa) {
    *pa += 10;
    printf("add_ten의 a: %d\n", *pa);
}

int main(void) {
    int a = 10;
    int* pt;
    pt = &a;

    add_ten(pt);
    printf("main의 a: %d\n", a);

    return 0;
}
