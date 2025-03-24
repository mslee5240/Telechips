#include <avr/io.h>
#include <avr/interrupt.h>

#include "def.h"

#define MOTOR_PWM_DDR			DDRB
#define MOTOR_LEFT_PORT_DDR		5		// OC1A
#define MOTOR_RIGHT_PORT_DDR	6		// OC1B

#define MOTOR_DRIVER_DIRECTION_PORT		PORTF
#define MOTOR_DRIVER_DIRECTION_DDR		DDRF

// 함수 프로토타입
void init_timer1(void);
void init_L298N(void);   
void stop(void);
void forward(int speed);
void backward(int speed);
void turn_left(int speed);
void turn_right(int speed);