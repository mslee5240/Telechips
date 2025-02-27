#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 함수를 호출할 때 인수로 구조체 변수를 사용하면 멤버들의 값을 한꺼번에 함수에 줄 수 있다.
// 구조체 변수를 반활할 때도 똑같이 적용되므로 함수가 여러 개의 값을 한 번에 반환할 수 있다.

struct vision {
    double left;
    double right;
};

struct vision exchange(struct vision robot);    // 두 시력을 바꾸는 함수

int main(void) {
    struct vision robot;

    printf("> 시력 입력: ");
    scanf("%lf %lf", &(robot.left), &(robot.right));

    robot = exchange(robot);
    printf("> 바뀐 시력: %.1lf %.1lf\n", robot.left, robot.right);

    return 0;
}

// 구조체를 반환하는 함수
struct vision exchange(struct vision robot) {
    double temp;

    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot;
}
