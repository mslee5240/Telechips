#include <stdio.h>
#include <string.h>

int main() {
    // Please write your code here.
    char chArr_1[20] = { 0 };
    char chArr_2[20] = { 0 };
    char chArr_3[20] = { 0 };

    scanf_s("%s", chArr_1, sizeof(chArr_1));
    scanf_s("%s", chArr_2, sizeof(chArr_2));
    scanf_s("%s", chArr_3, sizeof(chArr_3));

    int nArr[3] = { 0 };
    nArr[0] = strlen(chArr_1), nArr[1] = strlen(chArr_2), nArr[2] = strlen(chArr_3);

    int max = 0;
    int min = 20;
    for (int i = 0; i < 3; i++) {
        if (nArr[i] > max) {
            max = nArr[i];
        }
        if (nArr[i] < min) {
            min = nArr[i];
        }
    }

    printf("%d", max - min);

    return 0;
}