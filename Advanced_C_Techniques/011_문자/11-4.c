#include <stdio.h>

int main(void) {
    int res;
    char ch = 0;

    while (1) {
        res = scanf_s("%c", &ch);
        if (res == -1) break; // Ctrl + z 누르면 -1 반환됨. / -1 == EOF
        printf("%c", ch);
    }

    return 0;
}