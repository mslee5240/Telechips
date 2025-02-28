#include "double_linked_list.h"

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

#ifdef USE_STRING
        printf("<-| |%s| |->", p->data);
#endif
#ifdef USE_NUMBER
        printf("<-| |%d| |->", p->data);
#endif
    }
    printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입
void dInsert(DListNode* before, element data) {
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
#ifdef USE_STRING
    strcpy(newNode->data, data);
#endif
#if defined(USE_NUMBER) || defined(USE_STRUCT)
    newNode->data = data;               // 새로운 노드에 값 저장
#endif
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

// 검색 함수 (id로 검색)
DListNode* dSearch_id(DListNode* head, int id) {
    DListNode* p = head->rLink; // 시작 위치
    while (p != head) {
        if (p->data.id == id) {
            return p;
        }
        p = p->rLink;   // 다음 노드로 이동
    }
    return NULL;
}

// 검색 함수 (name으로 검색)
DListNode* dSearch_name(DListNode* head, char* name) {
    DListNode* p = head->rLink; // 시작 위치
    while (p != head) {
        if (strcmp(p->data.bookname, name) == 0) {
            return p;
        }
        p = p->rLink;   // 다음 노드로 이동
    }
    return NULL;
}

// 도서 대출 함수
void borrow_book(DListNode* head, int id) {
    DListNode* node = dSearch_id(head, id);
    if (node == NULL) {
        printf("책 ID %d를 찾을 수 없습니다.\n", id);
    }
    else if (node->data.is_borrowed) {
        printf("책 \'%s\' (ID: %d)은 이미 대출 중입니다.\n", node->data.bookname, node->data.id);
    }
    else {
        node->data.is_borrowed = 1;
        printf("책 \'%s\' (ID: %d)을 대출했습니다.\n", node->data.bookname, node->data.id);
    }
}