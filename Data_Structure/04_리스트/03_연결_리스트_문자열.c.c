#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 문자열 저장용 형식 정의
typedef struct {
    char name[100];     // 문자열의 길이 최대 99
} element;


typedef struct ListNode {
    element data;
    struct ListNode *link;
} ListNode;

// 오류 메시지를 출력하는 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 단일 연결 리스트의 첫 번째 위치에 새 노드를 삽입하는 함수
ListNode* insert_first(ListNode* head, element value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));     // 새 노드 공간의 동적 할당
    p->data = value;    // 데이터를 저장
    p->link = head;     // 기존 리스트의 첫 노드를 새 노드의 link로 설정
    head = p;           // head를 새 노드로 변경
    return head;
}

// 특정 위치(이전 노드 pre 다음)에 새 노드를 삽입하는 함수
ListNode* insert(ListNode *head, ListNode *pre, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));  // 새 노드 공간의 동적 할당
    p->data = value;        // 데이터를 저장
    p->link = pre->link;    // 새 노드가 이전 노드의 다음 노드를 가리키도록 설정
    pre->link = p;          // 이전 노드의 link를 새 노드로 변경
    return head;
}

// 리스트의 첫 번째 노드를 삭제하는 함수
ListNode* delete_first(ListNode* head) {
    ListNode* removed;      // 삭제될 노드
    if (head == NULL) {     // 리스트가 비어있으면 NULL 반환
        return NULL;        
    }
    removed = head;         // 삭제할 노드 저장
    head = removed->link;   // head를 다음 노드로 변경
    free(removed);          // 삭제된 노드 메모리 해제
    return head;
}

// 특정 위치(이전 노드 pre 다음)의 노드를 삭제하는 함수
ListNode* delete(ListNode* head, ListNode* pre) {
    ListNode* removed;          // 삭제될 노드
    removed = pre->link;        // 삭제할 노드 지정
    pre->link = removed->link;  // 이전 노드의 link를 삭제할 노드의 다음 노드로 변경
    free(removed);              // 삭제된 노드 메모리 해제
    return head;
}

// 리스트를 출력하는 함수
void print_list(ListNode* head) {
    // 헤드부터 link에 NULL이 보관된 노드까지 반복
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf("%s->", p->data.name);    // 노드 데이터 출력 (문자열)
    }
    printf("NULL\n");   // 노드 리스트의 끝을 표시
}

// 노드값 탐색 함수
ListNode* search_list(ListNode* head, element x) {
    ListNode* p = head;
    while (p != NULL) { // 노드의 끝까지 반복
        if (strcmp(p->data.name, x.name) == 0) { // x와 일치되는 노드 발견
            return p;                            // 발견된 노드 반환
        }
        p = p->link;    // 다음 노드로 이동
    }
    return NULL;        // 탐색 실패
}

// 2개의 노드를 하나로 결합하는 함수 head1 -> head2
ListNode* concat_list(ListNode* head1, ListNode* head2) {
    if (head1 == NULL) {    // head1이 없으면 head2를 반환
        return head2;
    }
    else if (head2 == NULL) { // head1이 있고, head2가 없으면 head1을 반환
        return head1;
    }
    else {                  // head1과 head2가 모두 존재하는 경우
        ListNode* p;
        p = head1;
        while (p->link != NULL) { // head1을 복사한 p를 끝까지 이동(마지막 노드 찾기)
            p = p->link;
        }
        p->link = head2;
        return head1;
    }
}

int main(void) {
    ListNode* head = NULL;
    ListNode* p = NULL;

    element data;
    element data2;

    strcpy(data.name, "apple");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "kiwi");
    head = insert_first(head, data);
    print_list(head);

    strcpy(data.name, "banana");
    head = insert_first(head, data);
    print_list(head);

    // kiwi가 존재하는 노드 찾기
    strcpy(data.name, "kiwi");
    p = search_list(head, data);
    if (p != NULL) {
        strcpy(data2.name, "melon");
        insert(head, p, data2);
        print_list(head);
    }
    
    return 0;
}