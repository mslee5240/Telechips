#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 계수: coefficient, 지수: exponential

typedef struct ListNode {
    int coef;   // 계수
    int expon;  // 지수
    struct ListNode* link;
} ListNode;

// 연결 리스트 헤더
typedef struct ListType {
    int size;           // 전체 노드의 개수
    ListNode* head;     // 링크 노드의 첫번째 노드 저장
    ListNode* tail;     // 링크 노드의 마지막 노드 저장
} ListType;

// 오류 메시지를 출력하는 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 리스트 헤더를 생성하는 함수
ListType* create() {
    ListType* plist = (ListType*)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

// 
void insert_last(ListType* plist, int coef, int expon) {
    // 동적 메모리 할당
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
    if (temp == NULL) {
        error("메모리 할당 실패");
    }
    temp->coef = coef;      // 계수 저장
    temp->expon = expon;    // 지수 저장
    temp->link = NULL;      // 다음 노드 링크 없음

    if (plist->tail == NULL) {
        // 기존 노드가 없으면, 
        plist->head = plist->tail = temp;   //헤드와 테일 모두 temp로 설정
    }
    else {
        // 기존 노드가 있으면,
        plist->tail->link = temp; // 테일의 링크를 temp로 설정
        plist->tail = temp;       // tail을 temp로 설정
    }
    plist->size++;  // 전체 카운트 1 증가
}

// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;
    int sum;
    while (a && b) {    // a, b 모두 NULL이 아니면
        if (a->expon == b->expon) { // a, b의 지수가 동일하면
            sum = a->coef + b->coef;    // a, b의 계수를 더하여 sum에 저장
            if (sum != 0) {
                insert_last(plist3, sum, a->expon); // plist3에 결과 노드 추가
            }
            a = a->link;    // a 리스트의 다음 노드 선택
            b = b->link;    // b 리스트의 다음 노드 선택
        }
        else if (a->expon > b->expon) {  // 두개의 지수 중, a > b인 경우
            insert_last(plist3, a->coef, a->expon); // plist3에 a의 값을 추가
            a = a->link;    // a 리스트의 다음 노드 선택
        }
        else {  // 두개의 지수 중, a < b인 경우
            insert_last(plist3, b->coef, b->expon); // plist3에 b의 값을 추가
            b = b->link;    // b 리스트의 다음 노드 선택
        }
    }
    // a, b 중에서 하나가 먼저 끝나면 남아있는 리스트의 나머지 항들을 모두 plist3에 복사
    for (; a != NULL; a = a->link) {
        insert_last(plist3, a->coef, a->expon);
    }
    for (; b != NULL; b = b->link) {
        insert_last(plist3, b->coef, b->expon);
    }
}

// 다항식 인쇄
void poly_print(ListType* plist) {
    ListNode* p = plist->head;
    char str[100];
    sprintf(str, "Polynomial = ");

    // 방법_1
    for (; p; p = p->link) {    // p가 NULL이 될 때까지 
        sprintf(str, "%s%d^%d + ", str, p->coef, p->expon);
    }
    // 방법_2
    // while (p != NULL) {
    //     printf("%d^%d + ", p->coef, p->expon);
    //     p = p->link;
    // }

    // 마지막 '+' 잘라내기
    str[strlen(str) - 2] = 0;
    sprintf(str, "%s\n", str);
    // 저장된 문자열 인쇄
    printf(str);
}

int main(void) {
    ListType* list1, * list2, * list3;

    // 연결 리스트 생성
    list1 = create();
    list2 = create();
    list3 = create();

    // 다항식 1을 생성
    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);

    // 다항식 2을 생성
    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 10, 6);

    poly_print(list1);
    poly_print(list2);

    // 다항식 3 = 다항식1 + 다항식2
    poly_add(list1, list2, list3);
    poly_print(list3);

    // 메모리 해제
    free(list1);
    free(list2);
    free(list3);

    return 0;
}