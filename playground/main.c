// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>


//int main(void) {
//    app();
//
//    return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    FILE* fp;   // ���� ������

    fp = fopen("C:\\Users\\eec04\\source\\repos\\Telechips\\Telechips\\playground\\a.txt", "r");   // a.txt ������ �б� �������� ����
    if (fp == NULL) {
        printf("������ ������ �ʾҽ��ϴ�.\n");
        return 1;
    }
    printf("������ ���Ƚ��ϴ�.\n");
    fclose(fp); // ���� �ݱ�

    return 0;
}