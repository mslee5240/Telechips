#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct profile {
    int     num;
    char    name[20];
    char* skill;
};

struct sports {
    char* event;
    struct  profile player;
};

int main(void) {
    struct sports a;

    a.event = (char*)malloc(sizeof("figure skating") + 1);
    strcpy(a.event, "figure skating");
    strcpy(a.player.name, "Minsoo Lee");
    a.player.num = 99;

    a.player.skill = (char*)malloc(80);
    printf("> skill을 입력하세요.: ");
    fgets(a.player.skill, 80, stdin);
    // scanf("%s", a.player.skill);

    printf("> 종목: %s\n", a.event);
    printf("> 이름: %s\n", a.player.name);
    printf("> 번호: %d\n", a.player.num);
    printf("> 기술: %s\n", a.player.skill);

    free(a.event);
    free(a.player.skill);

    return 0;
}