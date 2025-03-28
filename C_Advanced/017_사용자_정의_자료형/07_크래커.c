#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct book {
    char    title[80];
    char    author[80];
    int     page;
    double  price;
};

struct cracker {
    int price;
    int calories;
};

int main(void) {
    struct cracker c;
    
    printf("> 크래커의 가격과 열량을 입력하세요. : ");
    scanf("%d %d", &(c.price), &(c.calories));

    printf("> 크래커의 가격: %d원\n", c.price);
    printf("> 크래커의 열량: %dkcal\n", c.calories);

    return 0;
}