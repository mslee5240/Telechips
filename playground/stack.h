#ifndef __stack_h__
#define __stack_h__

#define MAX_STACK_SIZE 100  // 최대 스택의 크기

//typedef int element;        // int 자료형을 element라는 새로운 이름으로 정의하는 것

typedef struct {    // 미로찾기
    short r;        // x 좌표
    short c;        // y 좌표
} element;

typedef struct {
    element* data;      // 동적 메모리로
    int capacity;
    int top;
} StackType;

void init_stack(StackType* s);
int is_empty(StackType* s);
int is_full(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);
element peek(StackType* s);
void delete(StackType* s);

#endif