// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 열거형
enum season { 
    SPRING, // 0
    SUMMER, // 1
    FALL,   // 2
    WINTER  // 3
}; // 열거형 선언

// typedef struct {
//     char a;
// } s_name;

// typedef unsigned char BYTE;

void app(void) {
    enum season ss;
    char* pc = NULL;

    ss = SPRING;
    switch (ss) {
        case SPRING:
            pc = "inline";
            break;
        case SUMMER:
            pc = "swimming";
            break;
        case FALL:
            pc = "trip";
            break;
        case WINTER:
            pc = "skiing";
            break;
    }
    printf("나의 레저 활동: %s\n", pc);

}

