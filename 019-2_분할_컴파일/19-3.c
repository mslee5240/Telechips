//app.c
# include <stdio.h>

void app(int *pa, int *pb, int *pr) {
    *pr = *pa + *pb;
}


// main.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    int a = 10, b = 20, res = 0;
    app(&a, &b, &res);
    printf("%d", res);

    return 0;
}



