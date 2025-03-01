#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100  // 최대 스택의 크기

typedef int element;        // int 자료형을 element라는 새로운 이름으로 정의하는 것

element stack[MAX_STACK_SIZE];  // int stack[100];과 동일
int top = -1;

// 공백 상태 검사
int is_empty() {
    return (top == -1);
}

// 포화 상태 검사
int is_full() {
    return (top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(element item) {
    if (is_full()) {
        fprintf(stderr, "스택 포화 오류\n");
        return;
    }
    else {
        stack[++top] = item;
    }
}

// 삭제 함수
element pop() {
    if (is_empty()) {
        fprintf(stderr, "스택 공백 오류\n");
        return;
    }
    else {
        return stack[top--];
    }
}

// 피크 함수
element peek() {
    if (is_empty()) {
        fprintf(stderr, "스택 공백 오류\n");
        return;
    }
    else {
        return stack[top];
    }
}

int main(void) {
    push(1);
    push(2);
    push(3);
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());

    return 0;
}