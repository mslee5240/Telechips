#include <stdio.h>

int main(void) {
	char inStr[80] = { 0 };
	char outStr[80] = { 0 };
	int cnt = 0;

	printf("���� �Է�: ");
	gets_s(inStr, sizeof(inStr));
	for (int i = 0; i < strlen(inStr); i++) {
		if (inStr[i] >= 'A' && inStr[i] <= 'Z') {
			cnt++;
			outStr[i] = inStr[i] + 32;
		}
		else {
			outStr[i] = inStr[i];
		}
	}

	printf("���� �� ����: %s\n����� ���� ��: %d", outStr, cnt);

	return 0;
}