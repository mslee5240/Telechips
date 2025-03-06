#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 구조체 배열의 이름은 첫 번째 요소의 주소이므로 구조체 변수를 가리킵니다.
// 따라서 구조체 배열의 이름을 인수로 받는 함수는 구조체 포인터를 매개변수로 선언합니다.

struct address {
    char    name[20];
    int     age;
    char    tel[20];
    char    addr[80];
};

void print_list(struct address *lp);

int main(void) {
    struct address list[5] = {
        { "1길동", 11, "111-111", "1릉도 독도" },
        { "2길동", 22, "222-222", "2릉도 독도" },
        { "3길동", 33, "333-333", "3릉도 독도" },
        { "4길동", 44, "444-444", "4릉도 독도" },
        { "5길동", 55, "555-555", "5릉도 독도" },
    };

    print_list(list);

    return 0;
}

void print_list(struct address *lp) {
    // 방법_1: -> 연산자 사용
    for (int i = 0; i < 5; i++) {
        printf("> 방법_1: %10s%5d%15s%20s\n", 
            (lp + i)->name, (lp + i)->age, (lp + i)->tel, (lp + i)->addr);
    }
    printf("\n");

    // 방법_2: 배열 표현
    for (int i = 0; i < 5; i++) {
        printf("> 방법_2: %10s%5d%15s%20s\n",
            lp[i].name, lp[i].age, lp[i].tel, lp[i].addr);
    }
    printf("\n");

    // 방법_3: 포인터 표현
    for (int i = 0; i < 5; i++) {
        printf("> 방법_3: %10s%5d%15s%20s\n",
            (*(lp + i)).name, (*(lp + i)).age, (*(lp + i)).tel, (*(lp + i)).addr);
    }
    printf("\n");
}