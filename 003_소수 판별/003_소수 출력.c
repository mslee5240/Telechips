#include <stdio.h>

int main() {
	
	int cnt = 0;
	int inputVal = 0;
	
	printf("2 �̻��� ������ �Է��Ͻÿ�.: ");
	scanf_s("%d", &inputVal);

	int i, j;
	int prime_cnt = 0;

	for (i = 2; i <= inputVal; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0) {
				break;
			}
		}
		if (i == j) {
			prime_cnt++;
			printf("%5d", i);
			
			cnt++;
			if (cnt == 5) {
				printf("\n");
				cnt = 0;
			}
		}
	}

	printf("\n�� �Ҽ��� %d�� �Դϴ�.", prime_cnt);
	return 0;
}
