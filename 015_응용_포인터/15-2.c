// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_str(char** pps, int cnt);

void app(void) {
    char* ptr_arr[] = { "eagel", "tiger", "lion", "squirrel" };
    int cnt;

    cnt = sizeof(ptr_arr) / sizeof(ptr_arr[0]);
    print_str(ptr_arr, cnt);

}

void print_str(char** pps, int cnt) {
    for (int i = 0; i < cnt; i++) {
        printf("%s\n", pps[i]);
    }
}