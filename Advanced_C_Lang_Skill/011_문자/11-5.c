#include <stdio.h>

int main(void) {
    int res;
    char ch = 0;

    while (1) {
        res = scanf_s("%c", &ch);
        if (res == EOF) break; // EOF
        printf("%c", ch);
    }

    return 0;
}