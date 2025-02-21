#include <stdio.h>

int main(void) {

    int res;
    char ch;
    int cnt = 0, max = 0;

    while (1) {
        res = scanf_s("%c", &ch);
        if (res == -1) {
            break;
        }
        if (ch == '\n') {
            cnt--;
            if (cnt > max) {
                max = cnt;
                cnt = 0;
            }
        }
        cnt++;
    }

    printf("가장 긴 단어의 길이: %d", max);

    return 0;
}