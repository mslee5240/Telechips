#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void app() {
    char animal_1[2][10] = {
        {'d','o', 'g', '\0'},
        {'t','i', 'g', 'e', 'r', '\0'}
    };

    char animal_2[][10] = { "dog", "tiger" };

    for (int i = 0; i < 2; i++) {
        printf("%s", animal_1[i]);
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        printf("%s", animal_2[i]);
    }
    
}
