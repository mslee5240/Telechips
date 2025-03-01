#pragma once
#ifndef __double_linked_list_h__
#define __double_linked_list_h__

// #define USE_NUMBER
// #define USE_STRING      // 정수로 사용할 경우 주석 처리
#define USE_STRUCT

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_NUMBER
typedef int element;
#endif
#ifdef USE_STRING
typedef char element[80];
#endif
#ifdef USE_STRUCT
typedef struct {
    char    bookname[80];   // 책 이름
    int     id;             // 책 관리 번호
    int     is_borrowed;    // 대여 상태 (0: 보유, 1: 대여)
} element;
#endif

typedef struct DListNode {
    element data;
    struct DListNode* lLink;    // 선행 노드 링크
    struct DListNode* rLink;    // 후행 노드 링크
} DListNode;

void init(DListNode* phead);
void print_dList(DListNode* phead);
void dInsert(DListNode* before, element data);
void dDelte(DListNode* head, DListNode* removed);
DListNode* dSearch_id(DListNode* head, int id);
DListNode* dSearch_name(DListNode* head, char* name);

// 도서 대출 시스템
void borrow_book(DListNode* head, int id);
void return_book(DListNode* head, int id);
void display_books(DListNode* head);

#endif