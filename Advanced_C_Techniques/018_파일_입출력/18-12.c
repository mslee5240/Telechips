#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE* afp, * bfp, * cfp;

    char a_word[21];
    char b_word[21];
    char c_word[21];
    char* a_res;
    char* b_res;
    char* c_res;
    
    
    afp = fopen("a.txt", "r");
    bfp = fopen("b.txt", "r");
    cfp = fopen("c.txt", "w+");
    if ((afp == NULL) && (bfp == NULL) && (cfp = NULL)) {
        printf("오류 발생.");
        return 1;
    }

    while (1) {
        if (feof(afp)) break;
        a_res = fgets(a_word, 20, bfp);
        printf("%s\n", a_res);

    }
    

    fclose(afp);
    fclose(bfp);
    fclose(cfp);

    return 0;
}