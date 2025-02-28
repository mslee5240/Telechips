#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 배열을 이용한 리스트의 구현
#define MAX_LIST_SIZE   100

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];   // 배열 정의
    int size;                       // 현재 리스트에 저장된 항목의 개수
} ArrayListType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(ArrayListType* L) {
    L->size = 0;
}

int is_empty(ArrayListType* L) {
    return L->size == 0;
}

int is_full(ArrayListType* L) {
    return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos) {
    if (pos < 0 || pos >= L->size) {
        error("위치 오류");
    }
    return L->array[pos];
}

void print_list(ArrayListType* L) {
    for (int i = 0; i < L->size; i++) {
        printf("%d->", L->array[i]);
    }
    printf("\n");
}

void insert_last(ArrayListType* L, element item) {
    if (L->size >= MAX_LIST_SIZE) {
        error("리스트 오버플로우");
    }
    L->array[L->size++] = item;
}

void insert(ArrayListType* L, int pos, element item) {
    if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
        // 뒤에서 부터 데이터를 하나씩 뒤로 복사한다. (핵심)
        // for (int i = (L->size - 1); i >= pos; i--) {
        //     L->array[i + 1] = L->array[i];  // 한칸씩 뒤로 밀기
        // }

        // 교수님 방법
        element temp[MAX_LIST_SIZE];
        memcpy(temp, L->array, L->size * sizeof(element));
        memcpy(&L->array[pos + 1], &temp[pos], (L->size - pos) * sizeof(element));

        L->array[pos] = item;
        L->size++;
    }
}

element delete(ArrayListType* L, int pos) {
    element item;
    if (pos < 0 || pos >= L->size) {
        error("위치 오류");
    }
    item = L->array[pos];
    // 앞에서 부터 남은 데이터를 하나씩 앞으로 복사한다.
    // for (int i = pos; i < (L->size - 1); i++) {  // 교재 방법
    //     L->array[i] = L->array[i + 1];
    // }

    // 교수님이 사용하시는 방법
    memcpy(&(L->array[pos]), &(L->array[pos + 1]), (L->size - pos) * sizeof(element));
    L->size--;
    return item;
}

// 숙제
void clear(ArrayListType* L) {
    L->size = 0;
}


void replace(ArrayListType* L, int pos, element item) {
    
}

int get_length(ArrayListType* L) {

}


int main(void) {
    ArrayListType list;
    init(&list);

    insert(&list, 0, 10);
    print_list(&list);
    insert(&list, 0, 20);
    print_list(&list);
    insert(&list, 0, 30);
    print_list(&list);

    insert_last(&list, 40);
    print_list(&list);

    delete(&list, 0);
    print_list(&list);
    
    return 0;
}
