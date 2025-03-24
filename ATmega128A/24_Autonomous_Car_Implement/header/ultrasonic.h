#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "def.h"

// 방향 정의
#define LEFT		0
#define MID			1
#define RIGHT		2

// TRIG 핀 정의 (PA0, PA1, PA2)
#define TRIG_LEFT	0
#define TRIG_MID	1
#define TRIG_RIGHT	2
#define TRIG_PORT	PORTA
#define TRIG_DDR	DDRA

// ECHO 핀 정의 (PE4, PE5, PE6)
#define ECHO_LEFT	4
#define ECHO_MID	5
#define ECHO_RIGHT	6
#define ECHO_PIN	PINE
#define ECHO_DDR	DDRE

// 함수 선언
void init_ultrasonic(void);
void trigger_left(void);
void trigger_mid(void);
void trigger_right(void);
void distance_check(void);
void distance_print(void);	// 디버깅용 출력 함수

// 거리 저장 배열
volatile uint32_t ultrasonic_dis[3];

// ISR에서 사용할 버퍼
volatile uint32_t start_tcnt[3];
volatile uint32_t start_ovf[3];

// Timer2 오버플로우 횟수
volatile uint32_t timer2_ovf;