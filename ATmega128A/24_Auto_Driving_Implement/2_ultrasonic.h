#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define LEFT		0
#define MID			1
#define RIGHT		2

#define TRIG_LEFT	0
#define TRIG_MID	1
#define TRIG_RIGHT	2
#define TRIG_PORT	PORTA
#define TRIG_DDR	DDRA

#define ECHO_LEFT	4
#define ECHO_MID	5
#define ECHO_RIGHT	6
#define ECHO_PIN	PINE
#define ECHO_DDR	DDRE

void init_ultrasonic(void);

void trigger_left(void);
void trigger_mid(void);
void trigger_right(void);

void trigger_ultrasonic(void); // 사용 X

void distance_check(void);

void distance_print(void);