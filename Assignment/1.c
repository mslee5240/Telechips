#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {

    int num_1 = 0, num_2 = 0;
    scanf("%d %d", &num_1, &num_2);

    int sum = 0, carry = 0;

    for (int i = 0; i < 32; i++) {
        // 정수형 2진수로 변환
        int binary_1 = (num_1 >> i) & 1;
        int binary_2 = (num_2 >> i) & 1;
    
        int sum_bit = binary_1 ^ binary_2 ^ carry;
        carry = (binary_1 & binary_2) | (carry & (binary_1 ^ binary_2));
    
        sum |= (sum_bit << i);
    }
    return 0;
}