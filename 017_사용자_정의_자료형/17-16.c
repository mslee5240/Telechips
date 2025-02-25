// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct train Train;

struct train {
    int seats;
    struct train *next;
};


void app(void) {
    Train* head = NULL, * tail = NULL;
    for (int i = 0; i < 5; i++) {
        if (head == NULL) {
            head = tail = (Train*)malloc(sizeof(Train));
        }
        else {
            tail->next = (Train*)malloc(sizeof(Train));
            tail = tail->next;
        }
    }
    head->seats = 1;
    head->next->seats = 2;
    head->next->next->seats = 3;
    head->next->next->next->seats = 4;
    head->next->next->next->next->seats = 5;

    Train* current;
    current = head;
    while (current != NULL) {
        printf("%d ", current->seats);
        current = curretn->next;
    }

}

