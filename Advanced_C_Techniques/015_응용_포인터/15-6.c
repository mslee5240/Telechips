// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void func(int (*fp)(int, int));     // 함수 포인터를 매개변수로 갖는 함수
int sum(int a, int b);
int mul(int a, int b);
int maX(int a, int b);

typedef int (*operation_t)(int, int);

typedef struct {
    char name[10];
    operation_t func;
} Command;

void app(void) {
    Command commands[] = {
        {"sum", sum},
        {"mul", mul},
        {"maX", maX}
    };

    char command[20];
    int a, b;
    printf("원하는 명령을 입력하세요.: ");
    scanf("%s %d %d", command, &a, &b);
    for (int i = 0; commands[i].func != NULL; i++) {
        if (strcmp(command, commands[i].name) == 0) {
            int result = commands[i].func(a, b);
            printf("결과: %d", result);
            break;
        }
    }
}

void func(int (*fp)(int, int)) {
    int a, b;
    int res;

    printf("두 정수의 값을 입력하세요.: ");
    scanf("%d%d", &a, &b);
    res = fp(a, b);
    printf("결괏값은: %d\n", res);
}

int sum(int a, int b) {
    return (a + b);
}

int mul(int a, int b) {
    return (a * b);
}

int maX(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

