// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_str(char** pps, int cnt);

void app(void) {
    int arr[5];
    printf("arr의 값: %u\t", arr);
    printf("arr의 주소: %p\n", &arr);
    printf("arr + 1: %u\t" + 1, arr);
    printf("arr 주소 + 1: %p\n", &arr + 1);

}

void print_str(char** pps, int cnt) {
    for (int i = 0; i < cnt; i++) {
        printf("%s\n", pps[i]);
    }
}