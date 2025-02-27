#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 명령행 인수 command line argument
int main(int argc, char **argv) {       // 명령행 인수를 받을 매개변수
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);        // 인수로 받은 문자열 출력
    }
    
    // 방법_2
    // while (*argv != NULL) {
    //     printf("%s\n", *argv);
    //     argv++;
    // }

    return 0;
}