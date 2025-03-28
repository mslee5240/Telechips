#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "def.h"

#include "button.h"
#include "buzzer.h"
#include "fnd.h"
#include "isr.h"
#include "led.h"
#include "pwm.h"
#include "timer0.h"
#include "uart.h"
#include "uart0.h"
#include "uart1.h"
#include "ultrasonic.h"
#include "I2C.h"
#include "I2C_LCD.h"

// 함수 프로토타입 선언: 타이머 및 주변 장치 전체 초기화 함수
void init_all(void);

void seconds_count(void);		// 1초 Count
void half_seconds_count(void);	// 0.5초 Count
void displayUpdate(void);		// 7-Segment Display 갱신
void lcdDisplayUpdate(void);

void manual_mode(void);
void auto_mode(void);