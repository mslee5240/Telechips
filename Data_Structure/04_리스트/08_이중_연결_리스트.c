#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct DListNode {
    element data;
    struct DListNode* lLink;    // 선행 노드 링크
    struct DListNode* rLink;    // 후행 노드 링크
} DListNode;

// 이중 연결 리스트 초기화
void init(DListNode* phead) {
    phead->lLink = phead;
    phead->rLink = phead;
}

// 이중 연결 리스트의 노드를 인쇄
void print_dList(DListNode* phead) {
    DListNode* p;

    // p가 최초 위치인 phead에 도달할 때까지 반복
    for (p = phead->rLink; p != phead; p = p->rLink) {
        printf("<-| |%d| |->", p->data);
    }
    printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입
void dInsert(DListNode* before, element data) {
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    newNode->data = data;               // 새로운 노드에 값 저장
    newNode->lLink = before;            // 새로운 노드의 선행 링크를 before의 주소로 할당
    newNode->rLink = before->rLink;     // 새로운 노드의 후행 링크를 before가 가진 후행 링크에서 복사
    before->rLink->lLink = newNode;     // before의 후행 링크에서 보유한 선행 링크의 주소를 새로운 노드의 주소로 할당
    before->rLink = newNode;            // before의 후행 링크를 새로운 노드의 주소로 할당
}

// removed로 입력된 노드를 삭제
void dDelte(DListNode* head, DListNode* removed) {
    if (removed == head) {  // 헤드는 삭제 불가
        return;
    }
    // 삭제될 노드가 가진 선행 링크의 후행 링크값을 삭제될 노드의 후행 링크값에서 복사
    removed->lLink->rLink = removed->rLink;
    // 삭제될 노드가 가진 후행 링크의 선행 링크값을 삭제될 노드의 선행 링크값에서 복사
    removed->rLink->lLink = removed->lLink;
    free(removed);
}

// 이중 연결 리스트 테스트
int main(void) {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    printf("노드 추가\n");
    for (int i = 0; i < 5; i++) {
        dInsert(head, i);
        print_dList(head);
    }
    
    printf("노드 삭제\n");
    for (int i = 0; i < 5; i++) {
        print_dList(head);
        dDelte(head, head->rLink);
    }
    free(head);

    return 0;
}