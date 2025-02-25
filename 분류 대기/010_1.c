#include <stdio.h>

int main(void) {
	int arr[5];
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = arr[0] + arr[1];

	scanf_s("%d", &arr[3]);

	for (int i = 0; i <= 4; i++) {
		printf("%d\n", arr[i]);
	}
	
	return 0;
}