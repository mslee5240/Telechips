#include <stdio.h>

void input_nums(int* lotto_nums);
void print_nums(int* lotto_nums);

int main(void) {
    int lotto_nums[6] = { 0 };

    input_nums(lotto_nums);
    print_nums(lotto_nums);

    return 0;
}

void input_nums(int* lotto_nums) {
    for (int i = 0; i < 6; i++) {
        printf("번호 입력: ");
        scanf_s("%d", &lotto_nums[i]);

        // 입력 범위 검사
        if (lotto_nums[i] < 1 || lotto_nums[i] > 45) {
            printf("입력 범위를 초과했습니다!\n");
            i--;
        }

        // 중복 검사
        for (int j = 0; j < i; j++) {
            if (lotto_nums[i] == lotto_nums[j]) {
                printf("같은 번호가 있습니다!\n");
                i--;
            }
        }
        
    }
}

void print_nums(int* lotto_nums) {
    printf("로또 번호: ");
    for (int i = 0; i < 6; i++) {
        printf("%3d ", lotto_nums[i]);
    }
}