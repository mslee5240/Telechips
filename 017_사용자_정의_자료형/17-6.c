// app.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct vision {
    double left;
    double right;
};

struct vision exchange(struct vision robot);    // 두 시력을 바꾸는 함수

void app(void) {
    
    struct vision robot;

    printf("시력 입력: ");
    scanf("%lf %lf", &(robot.left), &(robot.right));
    robot = exchange(robot);
    printf("바뀐 시력: %.1lf %.1lf\n", robot.left, robot.right);

}

struct vision exchange(struct vision robot) {
    double temp;

    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot;
}
