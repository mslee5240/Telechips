#include <stdio.h>

int main(void) {
	char str[12] = { "Hello World" };

	str[5] = 65;    // 65 == 'a'

	printf("%s", str);

	return 0;
}