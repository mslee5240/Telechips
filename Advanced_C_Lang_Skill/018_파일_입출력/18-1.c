#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
    FILE *fp;   // 파일 포인터

    fp = fopen("C:\\Users\\eec04\\source\\repos\\Telechips\\Telechips\\playground\\a.txt", "r");   // a.txt 파일을 읽기 전용으로 개방
    if (fp == NULL) {
        printf("파일이 열리지 않았습니다.\n");
        return 1;
    }
    printf("파일이 열렸습니다.\n");
    fclose(fp); // 파일 닫기

    return 0;
}

// 개방 모드    / 파일이 있을 때                         / 파일이 없을 때
//      r       / 읽기 위해 개방                        / NULL(널 포인터) 반환
//      w       / 파일의 내용을 지우고 쓰기 위해 개방    / 새로운 파일 생성
//      a       / 파일의 끝에 추가하기 위해 개방         / 새로운 파일 생성

// EOF (End Of File): 오류가 발생했는지 또는 파일의 데이터를 모두 읽었는지 확인할 때 사용
// #define EOF (-1)