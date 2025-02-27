#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct train Train;

struct train {
    int seats;
    struct train* next;
};

int main(void) {
    Train* head = NULL, * tail = NULL;
    for (int i = 0; i < 5; i++) {
        if (head == NULL) {
            head = tail = (Train*)malloc(sizeof(Train));
            tail->next = NULL;  // next 포인터를 NULL로 초기화
        }
        else {
            tail->next = (Train*)malloc(sizeof(Train));
            tail = tail->next;
            tail->next = NULL;  // 새로운 노드의 next 포인터를 NULL로 초기화
        }
    }

    // 각 노드에 대한 seats 값 설정
    head->seats = 1;
    head->next->seats = 2;
    head->next->next->seats = 3;
    head->next->next->next->seats = 4;
    head->next->next->next->next->seats = 5;

    // 리스트 출력
    Train* current = head;
    while (current != NULL) {
        printf("%d ", current->seats);
        current = current->next;
    }
    printf("\n");

    // 메모리 해제
    current = head;
    while (current != NULL) {
        Train* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
