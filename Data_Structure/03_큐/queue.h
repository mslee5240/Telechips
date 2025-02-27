#pragma once
#ifndef __queue_h__
#define __queue_h__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE  5

typedef int element;
typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message);
void init_queue(QueueType* q);
void queue_print(QueueType* q);
int is_full(QueueType* q);
int is_empty(QueueType* q);
int enqueue(QueueType* q, int item);
element dequeue(QueueType* q);
element peek(QueueType* q);

#endif
