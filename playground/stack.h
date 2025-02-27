#ifndef __stack_h__
#define __stack_h__

#define MAX_STACK_SIZE 100  // �ִ� ������ ũ��

//typedef int element;        // int �ڷ����� element��� ���ο� �̸����� �����ϴ� ��

typedef struct {    // �̷�ã��
    short r;        // x ��ǥ
    short c;        // y ��ǥ
} element;

typedef struct {
    element* data;      // ���� �޸𸮷�
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