// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void app(void) {
    double div(int, int);
    void prn(char*);
    int *save(int);

    double (*fpa)(int, int);    // 원형 double div(int, int);
    void (*fpb)(char*);         // 원형 void prn(char*);
    int *(*fpc)(int);           // 원형 int *save(int);

    fpa = div;
    fpb = prn;
    fpc = save;

}



