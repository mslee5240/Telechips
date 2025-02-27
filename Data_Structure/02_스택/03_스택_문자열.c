#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE  100  // 최대 스택의 크기
#define MAX_STRING      100

typedef struct {
    int student_no;
    char name[MAX_STRING];
    char address[MAX_STRING];
} element;

element stack[MAX_STACK_SIZE];
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
    element input_item = {
        20250226,
        "Steve Kim",
        "Korea",
    };
    element output_item;
    
    push(input_item);
    output_item = pop();

    printf("학번 : %d\n", output_item.student_no);
    printf("이름 : %s\n", output_item.name);
    printf("주소 : %s\n", output_item.address);

    return 0;
}