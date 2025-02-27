#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
    QueueType queue;
    int element;

    init_queue(&queue);
    srand(time(NULL));  // 랜덤 함수 초기화
    for (int i = 0; i < 100; i++) {
        if (rand() % 5 == 0) {
            enqueue(&queue, rand() % 100);
        }
        queue_print(&queue);
        if (rand() % 10 == 0) {
            int data = dequeue(&queue);
        }
        queue_print(&queue);
    }
    
    return 0;
}