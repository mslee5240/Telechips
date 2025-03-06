#include <stdio.h>

int main(void) {
	int score[5];
	int total = 0;
	double avg = 0;

	for (int i = 0; i < 5; i++) {
        printf("정수를 입력하시오. 남은 입력 횟수[%d]: ", 5 - i);
		scanf_s("%d", &score[i]);
        printf("\n");
	}

	for (int i = 0; i < 5; i++) {
		total += score[i];
	}

	avg = total / 5.0;

	for (int i = 0; i < 5; i++) {
		printf("%5d", score[i]);
	}

	printf("\n");

	printf("평균: %.1lf\n", avg);

	return 0;
}