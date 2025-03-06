#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void add_ten(int a) {
    a = a + 10;
    printf("add_ten의 a: %d\n", a);
}

int main(void) {
    int a = 10;

    add_ten(a);
    printf("main의 a: %d\n", a);

    
    return 0;
}
