// arr[y][z] = { 0 };

// arr[y] == &arr[y][0] // (중요!)

// arr == &arr[0][0]


// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app() {
    char animal[5][20];
    int cnt;

    cnt = sizeof(animal) / sizeof(animal[0]);

    for (int i = 0; i < cnt; i++) {
        scanf("%s", animal[i]);
    }
    for (int i = 0; i < cnt; i++) {
        printf("%s ", animal[i]);
    }
}



// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a, b;

int main(void) {
    app();

    return 0;
}



