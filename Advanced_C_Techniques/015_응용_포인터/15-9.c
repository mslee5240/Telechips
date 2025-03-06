// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void app(void) {
    int arr[5] = { 10, 20, 30, 40, 50 };

    void* vp = arr;

    printf("%d", ((int*)vp)[2]);

}



