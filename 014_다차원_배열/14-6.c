// pArr[2][2] == *(pArr[2] + 2)

// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app(void) {
    char *pArr[5] = { "apple", "pear", "peach", "banana", "melon" };


    for (int i = 0; i < 5; i++) {
        printf("%s ", pArr[i]);
    }

}