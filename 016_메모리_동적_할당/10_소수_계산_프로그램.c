#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 입력
    int n = 0;
    printf("> 양수 입력: ");
    scanf("%d", &n);
    if (n < 2) {
        printf("> 2 이상의 숫자를 입력하세요.\n");
        return 0;
    }

    // 메모리 할당
    int *nArr = (int *)malloc((n -1) * sizeof(int));
    if (nArr == NULL) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    
    // 배열 초기화
    for (int i = 0; i < n - 1; i++) {
        nArr[i] = 2 + i;
    }

    // 논리 구현 - 에라토스테네스의 체
    for (int i = 0; i < n - 1; i++) {
        if (nArr[i] == 0) {
            continue;
        }

        int prime = nArr[i];    // 현재 소수
        for (int j = i + prime; j < n - 1; j += prime) {
            nArr[j] = 0;    // 배수 제거
        }
    }
    
    // 출력
    printf("> 소수 목록: \n");
    for (int i = 0; i < n - 1; i++) {
        printf("%5d", nArr[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }

    return 0;
}