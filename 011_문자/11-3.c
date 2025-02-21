#include <stdio.h>

int main(void) {
    char ch = 0;

    while (1) {
        scanf_s("%c", &ch);
        if (ch == '\n') {
            break;
        }
        printf("%c", ch);
    }

    return 0;
}