#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 재귀호출
int fib_1(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    return (fib(n - 1) + fib(n - 2));
}

// 반복문 - 다시 작성하기
int fib_2(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int pp = 0;
    int p = 0;
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
}


int main(void) {
    int result = fib(6);
    printf("피보나치 6 = %d", result);
    return 0;
}