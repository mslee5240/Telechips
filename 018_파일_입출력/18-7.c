#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// + 개방 모드, fseek, rewind, feof 함수
// a+ 모드로 파일의 내용을 확인하며 출력
int main(void) {
    FILE* fp;
    char str[20];

    fp = fopen("a.txt", "a+");
    if (fp == NULL) {
        printf("파일을 만들지 못했습니다.\n");
        return 1;
    }

    while (1) {
        printf("과일 이름: ");
        scanf("%s", str);
        if (strcmp(str, "end") == 0) {
            break;
        }
        else if (strcmp(str, "list") == 0) {
            fseek(fp, 0, SEEK_SET);     // 버퍼의 위치 지시자를 맨 처음으로 이동
            // rewind(fp);              // rewind(fp); == fseek(fp, 0, SEEK_SET);
            while (1) {
                fgets(str, sizeof(str), fp);
                if (feof(fp)) {         // 파일의 내용을 모두 읽으면 종료
                    break;
                }
                printf("%s", str);
            }
        }
        else {
            fprintf(fp, "%s\n", str);
        }
    }
    fclose(fp);

    return 0;
}