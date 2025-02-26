#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"

// mouse maze

#define MAZE_SIZE 6
char maze[MAZE_SIZE][MAZE_SIZE] = {
    { '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '1'},
    { '1', '0', '0', '0', '1', '1' },
    { '1', '0', '1', '0', '1', '1' },
    { '1', '0', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' }
};

// 위치 삽입
void push_loc(StackType * s, int r, int c) {
    if (r < 0 || c < 0) {
        return;
    }
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

// 미로 화면 인쇄
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

element here = {1, 0}, entry = {1, 0};

int main(void) {
    int r, c;
    StackType s;

    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;

        maze[r][c] = '.';   // 현재 이동한 경로
        maze_print(maze);
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        if (is_empty(&s)) {
            printf("실패\n");
            return -1;
        }
        else {
            here = pop(&s);
        }
        printf("성공\n");
    }


    return 0;
}
