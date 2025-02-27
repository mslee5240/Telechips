// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int a, int b) {
    return (a + b);
}

void app(void) {
    int (*fp)(int, int);
    int res;

    fp = sum;
    res = fp(10, 20);
    printf("result: %d\n", res);
}

