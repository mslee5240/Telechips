#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[80];   // 길이가 80인 char 배열을 element라는 새로운 타입으로 정의

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 리스트 항목 인쇄
void print_list(ListNode* head) {
    ListNode* p;
    if (head == NULL) {
        return;
    }
    p = head->link;
    do {
        printf("%s->", p->data);
        p = p->link;
    } while (p != head);
    printf("%s->", p->data);    // 마지막 노드 인쇄
}

// 앞에 노드 추가
ListNode* insert_first(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));   // 노드 생성
    // node->data = data;  // 생성된 노드에 데이터 할당
    strcpy(node->data, data);
    if (head == NULL) { // 기존 노드가 없는 경우
        head = node;       // 헤드를 자신으로
        node->link = head;  // 자신의 링크를 자신으로
    }
    else {  // 기존 노드가 존재하는 경우
        node->link = head->link;    // 헤드가 가진 링크를 자신의 링크로 복사
        head->link = node;          // 헤드의 링크를 자신의 주소로 할당
    }
    return head;
}

// 뒤에 노드 추가
ListNode* insert_last(ListNode* head, element data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));   // 노드 생성
    // node->data = data;  // 생성된 노드에 데이터 할당
    strcpy(node->data, data);
    if (head == NULL) { // 기존 노드가 없는 경우
        head = node;       // 헤드를 자신으로
        node->link = head;  // 자신의 링크를 자신으로
    }
    else {  // 기존 노드가 존재하는 경우
        node->link = head->link;    // 헤드가 가진 링크를 자신의 링크로 복사
        head->link = node;          // 헤드의 링크를 자신의 주소로 할당
        head = node;                // 노드를 헤드로 복사
    }
    return head;
}

int main(void) {
    ListNode* head = NULL;

    // list = 10->20->30->40
    head = insert_last(head, "하나");
    head = insert_last(head, "두울");
    head = insert_last(head, "세엣");
    head = insert_first(head, "네엣");
    print_list(head);

    return 0;
}