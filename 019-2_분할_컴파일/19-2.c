#include <stdio.h>

int main(void) {
    app();

    return 0;
}

// app.c
#include <stdio.h>

int* sum(int a, int b);
void app(void);

void app() {
    int* resp;

    resp = sum(10, 20);
    printf("두 정수의 합: %d\n", *resp);
}

int* sum(int a, int b) {
    static int res;     // 어떤 값을 주소로 반환할 경우 반드시 정적 변수로 선언되어야 한다.

    res = a + b;

    return &res;
}