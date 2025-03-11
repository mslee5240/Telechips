#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// 연산자 스택 구조체 및 함수들
typedef struct {
    char items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, char item) {
    if(isFull(s)) {
        printf("Stack is full\n");
        exit(1);
    }
    s->items[++(s->top)] = item;
}

char pop(Stack *s) {
    if(isEmpty(s)) {
        printf("Stack is empty\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

char peek(Stack *s) {
    if(isEmpty(s)) return '\0';
    return s->items[s->top];
}

int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

// 중위표현식을 후위표현식으로 변환하는 함수
void infixToPostfix(const char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int i = 0, k = 0;
    
    while(infix[i] != '\0') {
        // 공백은 건너뛰기
        if(infix[i] == ' ') {
            i++;
            continue;
        }
        
        // 숫자인 경우 전체 숫자(다중 자리수)를 복사
        if(isdigit(infix[i])) {
            while(isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';  // 숫자 구분을 위한 공백 추가
        }
        // 왼쪽 괄호는 스택에 push
        else if(infix[i] == '(') {
            push(&s, infix[i]);
            i++;
        }
        // 오른쪽 괄호인 경우 왼쪽 괄호가 나올 때까지 pop
        else if(infix[i] == ')') {
            while(!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
                postfix[k++] = ' ';
            }
            if(!isEmpty(&s) && peek(&s) == '(')
                pop(&s);  // '(' 제거
            i++;
        }
        // 연산자인 경우
        else {
            while(!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[k++] = pop(&s);
                postfix[k++] = ' ';
            }
            push(&s, infix[i]);
            i++;
        }
    }
    // 남은 연산자 모두 pop
    while(!isEmpty(&s)) {
        postfix[k++] = pop(&s);
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';
}

// 피연산자(숫자)를 위한 스택 구조체 및 함수들
typedef struct {
    double items[MAX];
    int top;
} StackNum;

void initStackNum(StackNum *s) {
    s->top = -1;
}

int isEmptyNum(StackNum *s) {
    return s->top == -1;
}

int isFullNum(StackNum *s) {
    return s->top == MAX - 1;
}

void pushNum(StackNum *s, double item) {
    if(isFullNum(s)) {
        printf("Number Stack is full\n");
        exit(1);
    }
    s->items[++(s->top)] = item;
}

double popNum(StackNum *s) {
    if(isEmptyNum(s)) {
        printf("Number Stack is empty\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

// 후위표현식을 계산하는 함수
double evaluatePostfix(const char *postfix) {
    StackNum s;
    initStackNum(&s);
    int i = 0;
    
    while(postfix[i] != '\0') {
        if(postfix[i] == ' ') {
            i++;
            continue;
        }
        // 숫자인 경우
        if(isdigit(postfix[i])) {
            double num = 0;
            while(isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushNum(&s, num);
        }
        // 연산자인 경우
        else {
            double val2 = popNum(&s);
            double val1 = popNum(&s);
            switch(postfix[i]) {
                case '+': pushNum(&s, val1 + val2); break;
                case '-': pushNum(&s, val1 - val2); break;
                case '*': pushNum(&s, val1 * val2); break;
                case '/': pushNum(&s, val1 / val2); break;
                default:
                    printf("알 수 없는 연산자: %c\n", postfix[i]);
                    exit(1);
            }
            i++;
        }
    }
    return popNum(&s);
}

int main() {
    // 계산할 중위표현식
    char infixExp[] = "(4 * (220 + 3) + 2) * 10 / 2 + 4 * 3";
    char postfixExp[200];
    
    // 중위 -> 후위 변환
    infixToPostfix(infixExp, postfixExp);
    printf("Postfix Expression: %s\n", postfixExp);
    
    // 후위표현식 계산
    double result = evaluatePostfix(postfixExp);
    printf("Result: %.0f\n", result);  // 결과: 4482
    
    return 0;
}
