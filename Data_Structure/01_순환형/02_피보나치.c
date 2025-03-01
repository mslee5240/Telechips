#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 1 1 2 3 5 8 13

// 재귀호출
int fib_1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    return (fib_1(n - 1) + fib_1(n - 2));
}

// 반복문 - 다시 작성하기
int fib_2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int pp = 1;
    int p = 1;
    int result = 0;

    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
}

int main(void) {
    int result = fib_1(6);
    printf("피보나치 6 = %d", result);

    return 0;
}