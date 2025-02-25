// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap_ptr(char** ppa, char**ppb);

void app(void) {
    char* pa = "success";
    char* pb = "failure";

    printf("pa -> %s, pb -> %s\n", pa, pb);
    
    swap_ptr(&pa, &pb);

    printf("pa -> %s, pb -> %s\n", pa, pb);

}

void swap_ptr(char** ppa, char**ppb) {
    char* pt;
    pt = *ppa;
    *ppa = *ppb;
    *ppb = pt;
}