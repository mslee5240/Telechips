#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

// 스택 초기화 함수
void init_stack(StackType* s) {
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

// 공백 상태 검사
int is_empty(StackType* s) {
    return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType* s) {
    return (s->top == (s->capacity -1));
}

// 삽입 함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        s->capacity *= 2;
        element* temp = (element*)realloc(s->data, s->capacity * sizeof(element));
        if (temp == NULL) {
            fprintf(stderr, "메모리 재할당 실패\n");
            exit(1);
        }
        s->data = temp;
    }
    s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        // return -1;
        // return (element){ -1, -1 };
        exit(1);
    }
    else {
        return s->data[(s->top)--];
    }
}

// 피크 함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        // return -1;
        return (element){ -1, -1 };
    }
    else {
        return s->data[s->top];
    }
}

// void delete(StackType* s) {
//     free(s);
// }

void delete(StackType* s) {
    free(s->data);  // 동적 할당된 배열 해제
    s->data = NULL; // 포인터 초기화
    s->capacity = 0;
    s->top = -1;
}