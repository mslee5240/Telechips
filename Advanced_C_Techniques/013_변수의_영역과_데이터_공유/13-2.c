#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 레지스터 변수
int main(void) {
    register int i;
    auto int sum = 0;

    for (i = 1; i <= 10000; i++) {
        sum += 1;
    }

    printf("%d\n", sum);

    return 0;
}
