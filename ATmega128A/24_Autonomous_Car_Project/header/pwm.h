#include <avr/io.h>
#include <avr/interrupt.h>

#include "def.h"
#include "ultrasonic.h"

#define MOTOR_PWM_DDR			DDRB
#define MOTOR_LEFT_PORT_DDR		5		// OC1A
#define MOTOR_RIGHT_PORT_DDR	6		// OC1B

#define MOTOR_DRIVER_DIRECTION_PORT		PORTF
#define MOTOR_DRIVER_DIRECTION_DDR		DDRF

// 임계값 및 속도 상수 (원시값 기준)
// 중앙 센서 값이 225 미만이면 turning mode
#define THRESH_CLOSE    250 

// 중앙 센서 값이 225 이상 500 이하면 80% 속도, 500 이상이면 최대 속도  
#define THRESH_SAFE     600 

#define MAX_SPEED       750  // 최대 PWM 값
#define SPEED_80        550  // MAX_SPEED의 80%
#define KP              10	 // 회전 보정 상수 (필요에 따라 조정)

// 함수 프로토타입
void init_timer1(void);
void init_L298N(void);   
void stop(void);
void forward(int speed);
void backward(int speed);
void turn_left(int speed);
void turn_right(int speed);

void auto_drive_mode(void);