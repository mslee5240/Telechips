#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void app(void) {
    int* pi;
    int sum = 0;

    // 배열처럼 사용할 전체 공간을 동적 할당해 int형을 가리키는 포인터에 그 주소를 저장
    // 그러면 포인터의 주소 값을 int형의 크기만큼 증가시켜 전체 저장 공간을 배열처럼 사용할 수 있다.
    pi = (int*)malloc(5 * sizeof(int));
    if (pi == NULL) {
        printf("메모리가 부족합니다!\n");
        exit(1);
    }

    printf("다섯 명의 나이를 입력하세요.: ");
    for (int i = 0; i < 5; i++) {
        // scanf("%d", &pi[i]);     // 배열 요소 표현식식
        scanf("%d", pi + i);        // 포인터 계산식
        //sum += pi[i];
        sum += *(pi + i);
    }
    printf("다섯 명의 평균 나이: %.1lf\n", (sum / 5.0));
    free(pi);

}
