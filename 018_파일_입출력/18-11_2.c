#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct {
    char a;
    char b;
    short c;
    int d;
    char name[20];
} myStruct_t;

int main(void) {
    FILE* bfp;

    myStruct_t num;
    myStruct_t res;

    num.a = 64;
    num.b = 128;
    num.c = 65535;  // 0xffff == -1
    num.d = 0x12345678;
    strcpy(num.name, "Hello World!");

    bfp = fopen("b.txt", "wb");
    fwrite(&num, sizeof(num), 1, bfp);

    fclose(bfp);

    bfp = fopen("b.txt", "rb");
    fread(&res, sizeof(res), 1, bfp);
    printf("a = %d\n", res.a);
    printf("b = %d\n", res.b);
    printf("c = %d\n", res.c);
    printf("d = %8x\n", res.d);
    printf("name = %s\n", res.name);

    fclose(bfp);

    return 0;
}