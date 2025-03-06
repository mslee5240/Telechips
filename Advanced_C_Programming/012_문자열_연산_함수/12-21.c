#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void str_swap(char* str_1, char* str_2) {
    char tmp[80] = { 0 };
    strcpy(tmp, str_1);
    strcpy(str_1, str_2);
    strcpy(str_2, tmp);
}

int main(void) {
    char str_1[80];
    char str_2[80];
    char str_3[80];
    
    printf("세 단어 입력: ");
    scanf("%s %s %s", str_1, str_2, str_3);

    if (strcmp(str_1, str_2) == 1) {
        str_swap(str_1, str_2);
       
    }
    if (strcmp(str_1, str_3) == 1) {
        str_swap(str_1, str_3);
    }
    if (strcmp(str_2, str_3) == 1) {
        str_swap(str_2, str_3);
    }

    printf("%s %s %s", str_1, str_2, str_3);

    return 0;
}