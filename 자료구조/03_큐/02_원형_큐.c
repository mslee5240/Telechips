#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE      5

typedef int element;
typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType* q) {
    q->rear = 0;
    q->front = 0;
}

void queue_print(QueueType* q) {
    printf("QUEUE(front = %d, rear = %d) = ", q->front, q->rear);
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

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType* q) {
    return (q->rear == q->front);
}

int enqueue(QueueType* q, int item) {
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
        return -1;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;   // 최대값을 넘어가면 다시 1로
    // 위 한줄을 if문으로 바꾸면
    // (q->rear)++;
    // if (q->rear == MAX_QUEUE_SIZE) {
    //     q->rear = 0;
    // }
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(QueueType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
        return -1;
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


int main(void) {
    QueueType queue;
    int item;

    init_queue(&queue);

    printf("--데이터 추가 단계--\n");
    while (!is_full(&queue)) {
        printf("정수를 입력하세요.: ");
        scanf("%d", &item);
        enqueue(&queue, item);
        queue_print(&queue);
    }
    printf("큐는 포화상태입니다.\n\n");

    printf("--데이터 꺼냄 단계--\n");
    while (!is_empty(&queue)) {
        item = dequeue(&queue);
        printf("꺼내온 정수: %d\n", item);
        queue_print(&queue);
    }
    printf("큐는 공백상태입니다.\n");

    return 0;
}