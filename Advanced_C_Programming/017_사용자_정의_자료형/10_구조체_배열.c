#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct address {
    char    name[20];
    int     age;
    char    tel[20];
    char    addr[80];
};

int main(void) {
    // 방법_1
    struct address list_1[5] = {  // 요소가 5개인 구조체 배열 선언
        { "1길동", 11, "111-111", "1릉도 독도" },
        { "2길동", 22, "222-222", "2릉도 독도" },
        { "3길동", 33, "333-333", "3릉도 독도" },
        { "4길동", 44, "444-444", "4릉도 독도" },
        { "5길동", 55, "555-555", "5릉도 독도" },
    };
    // 배열의 요소가 구조체이므로 각각의 초깃값은 구조체를 초기화하는 형식을 사용
    // 따라서 중괄호 쌍을 2개 사용

    for (int i = 0; i < 5; i++) {
        printf("> list_1: %10s%5d%15s%20s\n",
            list_1[i].name, list_1[i].age, list_1[i].tel, list_1[i].addr);
    }

    // 방법_2
    struct address* list_2;
    list_2 = (struct address*)malloc(5 * sizeof(struct address));

    strcpy(list_2[0].name, "steve");
    list_2->age = 66;
    strcpy(list_2[0].tel, "666-666");
    strcpy(list_2[0].addr, "6릉도-독도");

    for (int i = 0; i < 5; i++) {
        printf("> list_2: %10s%5d%15s%20s\n",
            list_2[i].name, list_2[i].age, list_2[i].tel, list_2[i].addr);
    }

    free(list_2);

    return 0;
}
