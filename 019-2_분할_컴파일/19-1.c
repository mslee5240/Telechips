#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "main.h"

#define ABC

extern int motor_a; // 

int main(void) {
#if defined(ABC)    // 전처리기, ABC라는 정의가 있을 때만 동작
    motor_b = 10;
    stopMotor();
    initMotor();
#endif

#ifdef(ABC)        // if defined == ifdef 
    motor_b = 10;
    stopMotor();
    initMotor();
#endif    

#ifndef(ABC)        // ~(ifdef) = ifndef
    motor_b = 10;
    stopMotor();
    initMotor();
#endif    

    return 0;
}


// lcd.c
#include "lcd.h"

int lcd_a;

int lcd(void) {

}


// motor.c
#include "motor.h"

void motor();
void runMotor();

int motor_a;

void motor(void) {
    motor_a = motor_b;

}

void initMotor(void) {
    motor_b = 10;
}


// main.h
#include "motor.h"
#include "lcd.h"


// lcd.h
#include "main.h"
#include "lcd.h"


// motor.h
#ifndef __MOTOR_H   // 언더바 두개 붙여서 숨김, 매크로명이 정의되어 있지 않으면 매크로명 정의의
#define __MOTOR_H   // ifndef - endif 사용해서 중복 선언을 해결 

#include "main.h"   // 서로 충돌하는 경우가 생김 => 헤더 파일의 중복 문제 해결 방법법
#include "lcd.h"

int motor_b; // 헤더 파일에서는 변수 선언을 하지 않는게 좋다.
// int motor_b = 10; 초기화 해버리면 오류 발생 가능성
static motor_c; // 다른 파일에서 접근 제한하기


void motor();
void runMotor();
void stopMotor();
void initMotor();

#endif