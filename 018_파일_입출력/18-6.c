#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 13 -> CR(Carriage Return, \r)
// 10 -> LF(Line Feed, \n)
// 26 -> EOF(End Of File, Ctrl + Z)
int main(void) {
    FILE* fp;
    int arr[10] = { 13, 10, 13, 13, 10, 26, 13, 10, 13, 10 };
    int res;

    fp = fopen("a.txt", "wb");
    for (int i = 0; i < 10; i++) {
        fputc(arr[i], fp);
    }
    fclose(fp);


    // 텍스트 파일을 읽기 위해 개방
    fp = fopen("a.txt", "rt");
    while (1) {
        res = fgetc(fp);
        if (res == EOF) {
            break;
        }
        printf("%4d", res);
    }
    printf("\n");
    fclose(fp);
    // Windows에서는 \r\n (CR+LF)을 \n (LF)로 변환해서 읽음.


    // 바이너리 파일을 읽기 위해 개방
    fp = fopen("a.txt", "rb");
    while (1) {
        res = fgetc(fp);
        if (res == EOF) {
            break;
        }
        printf("%4d", res);
    }
    printf("\n");
    fclose(fp);

    return 0;
}