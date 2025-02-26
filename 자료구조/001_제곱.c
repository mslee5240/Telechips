#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


double power(double x, int n) {
    if (n == 0) {
        return 1;
    }
    else if ((n % 2) == 0) {
        return power(x * x, n / 2);
    }
    else {
        return x * power(x * x, (n - 1) / 2);
    }
}
int main(void) {
    int result = (int)power(2, 10);
    printf("2의 10승은 %d", result);
    return 0;
}