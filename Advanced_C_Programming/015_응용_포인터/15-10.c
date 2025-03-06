// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int add(int a, int b) { return (a + b); }
int sub(int a, int b) { return (a - b); }
int mul(int a, int b) { return (a * b); }


void app(void) {
    int (*parr[3])(int, int) = { add, sub, mul };
    int res = 0;

    for (int i = 0; i < 3; i++) {
        res += parr[i](2, 1);
    }

    printf("%d", res);
}



