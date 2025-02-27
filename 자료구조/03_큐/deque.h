#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE  5

typedef int element;
typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} DequeType;

void error(char* message);
void init_deque(DequeType* q);
void deque_print(DequeType* q);
int is_full(DequeType* q);
int is_empty(DequeType* q);
int add_rear(DequeType* q, int item);
element delete_front(DequeType* q);
element get_front(DequeType* q);