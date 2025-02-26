#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100  // 최대 스택의 크기
typedef int element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s) {
    s-> top = -1;
}

// 공백 상태 검사
int is_empty(StackType* s) {
    return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType* s) {
    return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 오류\n");
        return;
    }
    else {
        s->data[++s->top] = item;
    }
}

// 삭제 함수
element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        return;
    }
    else {
        return s->data[s->top--];
    }
}

// 피크 함수
element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 오류\n");
        return;
    }
    else {
        return s->data[s->top];
    }
}

int main(void) {
    StackType s;

	init_stack(&s);

	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));

    // 동적 메모리 할당
    // StackType *s;
    // s = (StackType*)malloc(sizeof(StackType));

    // init_stack(s);

    // push(s, 1);
    // push(s, 2);
    // push(s, 3);
    // printf("%d\n", pop(s));
    // printf("%d\n", pop(s));
    // printf("%d\n", pop(s));

    return 0;
}