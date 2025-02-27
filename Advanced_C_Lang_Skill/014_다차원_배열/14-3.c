// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app(void) {
    char* pArr_1[5];
    pArr_1[0] = "dog";
    pArr_1[1] = "elephant";
    pArr_1[2] = "horse";
    pArr_1[3] = "tiger";
    pArr_1[4] = "lion";

    char* pArr_2[5] = { "dog", "elephant", "horse", "tiger", "lion" };
    char Arr[5][10] = { "dog", "elephant", "horse", "tiger", "lion" };

    printf("char* pArr_1[5]: \n");
    for (int i = 0; i < 5; i++) {
        
        printf("%s\n", pArr_1[i]);
    }
    printf("\n");

    printf("char* pArr_2[5]: \n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", pArr_2[i]);
    }
    printf("\n");

    printf("char Arr[5][10]: \n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", Arr[i]);
    }

}