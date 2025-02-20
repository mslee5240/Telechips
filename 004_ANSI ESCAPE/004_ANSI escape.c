#include <stdio.h>
#include <stdlib.h>

#define ESC 0x1b // \033

int main() {
	while (1) {
		char ch = getch();
		putchar(ch);

		if (ch == '1') {
			return 0;
		}

		if (ch == '2') {
			// ANSI escape code, CSI code
			// "\033"�� Escape ���ڷ�, ���� ���� ���ڵ��� Ư���� ���� ���ڷ� �ؼ��ǵ��� �մϴ�.
			// [2J : ȭ���� ����� ���, [H : Ŀ���� ȭ���� ���� ������� �̵�
			printf("\033[2J\033[H");
			/*putchar(ESC);
			putchar('[');
			putchar('0');
			putchar('J');*/
		}
		
	}
	return 0;
}