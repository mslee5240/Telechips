#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


// 스택 초기화 함수
void init_stack(StackType* s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검사
int is_empty(StackType* s) {
    return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType* s) {
    return (s->top == (s->capacity - 1));
}

// 삽입 함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

// 삽입 함수 2


// 삭제 함수
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        //return -1;
        return (element) { -1, -1 };
    }
    else {
        return s->data[(s->top)--];
    }
}

// 피크 함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        //return -1;
        return (element) { -1, -1 };
    }
    else {
        return s->data[s->top];
    }
}

// 스택 삭제 함수
void delete(StackType* s) {
    free(s);

}
