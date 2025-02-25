// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct cracker {
    int price;
    int calories;
};

void app(void) {
    struct cracker c1;

    printf("바사삭의 가격과 열량을 입력하세요.: ");
    scanf("%d %d", &(c1.price), &(c1.calories));
    
    printf("바사삭의 가격: %d원\n", c1.price);
    printf("바사삭의 열량: %dkcal\n", c1.calories);

}

