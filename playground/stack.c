#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

// ���� ���� �˻�
int is_empty(StackType* s) {
    return (s->top == -1);
}

// ��ȭ ���� �˻�
int is_full(StackType* s) {
    return (s->top == (s->capacity - 1));
}

// ���� �Լ�
void push(StackType* s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

// ���� �Լ� 2


// ���� �Լ�
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        //return -1;
        return (element) { -1, -1 };
    }
    else {
        return s->data[(s->top)--];
    }
}

// ��ũ �Լ�
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        //return -1;
        return (element) { -1, -1 };
    }
    else {
        return s->data[s->top];
    }
}

// ���� ���� �Լ�
void delete(StackType* s) {
    free(s);

}
