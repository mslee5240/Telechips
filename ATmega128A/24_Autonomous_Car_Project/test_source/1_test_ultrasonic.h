#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define TRIG		1
#define TRIG_PORT	PORTA
#define TRIG_DDR	DDRA

#define ECHO		5
#define ECHO_PIN	PINE	
#define ECHO_DDR	DDRE

void init_ultrasonic(void);
void trigger_ultrasonic(void);
void distance_ultrasonic(void);

