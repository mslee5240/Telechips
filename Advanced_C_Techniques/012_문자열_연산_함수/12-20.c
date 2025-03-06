#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {
    char str[80];

    gets(str);

    int len = strlen(str);

    if (len > 5) {
        for (int i = 5; i < len; i++) {
            str[i] = '*';
        }
    }

    printf("%s", str);

    return 0;
}