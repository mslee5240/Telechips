// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct address {
    char name[20];
    int age;
    char tel[20];
    char addr[80];
};

void app(void) {
    // 방법_1
    // struct address list[5] = {
    //     { "1길동", 11, "111-111", "1릉도 독도" },
    //     { "2길동", 22, "222-222", "2릉도 독도" },
    //     { "3길동", 33, "333-333", "3릉도 독도" },
    //     { "4길동", 44, "444-444", "4릉도 독도" },
    //     { "5길동", 55, "555-555", "5릉도 독도" },
    // };

    // 방법_2
    struct address* list;
    list = malloc(5 * sizeof(struct address));
    strcpy(list[0].name, "steve");

    for (int i = 0; i < 5; i++) {
        printf("%10s%5d%15s%20s\n", 
            list[i].name, list[i].age, list[i].tel, list[i].addr);
    }

}

