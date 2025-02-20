#include <stdio.h>
#include <stdlib.h>
#define ESC 0x11b

int main(void) {
	int max_x = 10, max_y = 10;
	int cur_x = 5, cur_y = 5;
	while (1) {
		printf("\033[2J\033[H");

		for (int y = 0; y < max_y; y++) {
			for (int x = 0; x < max_x; x++) {
				if (cur_x == x && cur_y == y) {
					putchar('*');
				}
				else {
					putchar('.');
				}
			}
			putchar('\n');
		}

		char ch = getch();
		if (ch == '1') return 0;

		if (ch == 'a') {
			cur_x--;
			if (cur_x < 0) cur_x = 0;
		}
		if (ch == 'd') {
			cur_x++;
			if (cur_x > max_x - 1) cur_x = max_x - 1;
		}
		if (ch == 'w') {
			cur_y--;
			if (cur_y < 0) cur_y = 0;
		}
		if (ch == 's') {
			cur_y++;
			if (cur_y > max_y - 1) cur_y = max_y - 1;
		}
	}
}