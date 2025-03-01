#include "deque.h"

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_deque(DequeType* q) {
    q->rear = 0;
    q->front = 0;
}

void deque_print(DequeType* q) {
    printf("DEQUE(front = %d, rear = %d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", q->data[i]);
            if (i == q->rear) {
                break;
            }
        } while (i != q->front);
    }
    printf("\n");
}

int is_full(DequeType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(DequeType* q) {
    return (q->rear == q->front);
}

int add_rear(DequeType* q, int item) {
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
        return -1;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;   // 최대값을 넘어가면 다시 1로
    q->data[q->rear] = item;
}

element delete_front(DequeType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element get_front(DequeType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val) {
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
    }
    q->data[q->front] = val;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q) {
    int prev = q->rear;
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
    }
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

element get_rear(DequeType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
    }
    return q->data[q->rear];
}