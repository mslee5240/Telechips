#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"

DListNode* current;

void print_dList2(DListNode* phead) {
    DListNode* p;
    for (p = phead->rLink; p != phead; p = p->rLink) {
        if (p == current) {
            printf("<-| [%s] |->", p->data);
        }
        else {
            printf("<-| %s |->", p->data);
        }
    }
    printf("\n");
}

int main(void) {
    char ch;
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    dInsert(head, "맘마미아");
    dInsert(head, "댄싱퀸");
    dInsert(head, "페르난도");

    current = head->rLink;

    do {
        printf("\n명령어를 입력하시오(<, >, q): ");
        ch = getchar();
        if (ch == '<') {    // 이전 곡
            current = current->lLink;   // 선행 링크로 이동
            if (current == head) {      // 이동한 링크가 헤더인 경우 
                current = current->lLink;   // 헤더의 선행 링크로 이동
            }
        }
        else if (ch == '>') {   // 다음 곡
            current = current->rLink;   // 후행 링크로 이동
            if (current == head) {      // 이동한 링크가 헤더인 경우
                current = current->rLink;   // 헤더의 후행 링크로 이동
            }
        }
        print_dList2(head);
        getchar();
    } while(ch != 'q');

    // 메모리 해제
    current = head;
    while (current->rLink != head) {
        dDelte(head, current->rLink);
        current = current->rLink;
    }
    free(head);

    return 0;
}