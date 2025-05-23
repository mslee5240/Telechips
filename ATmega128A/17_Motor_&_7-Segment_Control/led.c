﻿#include "led.h"

extern volatile int msec_count;

volatile int state = 0;
volatile int state_manual = 0;

void state_transition(void) {
	state++;
	state %= FUNC_NUM;
}

void manual_transition(void) {
	state_manual++;
	state_manual %= FUNC_NUM;
}

void (*fp[])() =
{
	shift_left_led_on,
	shift_right_led_on,
	shift_left_keep_led_on,
	shift_right_keep_led_on,
	flower_on,
	flower_off
};

void init_led(void) {
	DDRB = 0x0f;
	PORTB = 0x00;
}


void led_auto(void)
{
	if (state > 7) {
		state = 0;
	}
	fp[state]();
}

void led_manual(void)
{
	fp[state_manual]();
}


void led_all_on(void)
{
	PORTB = 0x0f;
}

void led_all_off(void)
{
	PORTB = 0x00;
}

void shift_left_led_on(void)
{
	static int i = 0;
	
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			PORTA = 0;
			state_transition();
		}
		else {
			PORTA = 0x01 << i++;
		}
	}
}

void shift_right_led_on(void)
{
	static int i = 0;
	
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			PORTA = 0;
			state_transition();
		}
		else {
			PORTA = 0x80 >> i++;
		}
	}
}

void shift_left_keep_led_on()
{
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			PORTA = 0;
			state_transition();
		}
		else {
			PORTA |= (0x01 << i);
			i++;
		}
	}
}

void shift_right_keep_led_on()
{
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			PORTA = 0;
			state_transition();
		}
		else {
			PORTA |= (0x80 >> i);
			i++;
		}
	}
}

void flower_on(void) {
	static int i = 0;
	if (msec_count >= 200)
	{
		msec_count = 0;
		if (i > 4) {
			i = 0;
			PORTA = 0;
			state_transition();
		}
		else {
			PORTA |= 0x10 << i | 0x08 >> i;
			i++;
		}
	}
}

void flower_off(void) {
	static int i = 0;
	unsigned char h = 0xf0;
	unsigned char l = 0x0f;
	if (msec_count >= 200)
	{
		msec_count = 0;
		if (i > 4) {
			i = 0;
			PORTA = 0x00;
			state_transition();
		}
		else {
			PORTA = (h >> i) & 0xf0 | (l << i) & 0x0f;
			i++;
		}
	}
}

void pwm_led_control_sw_manner(void)
{
	int dim = 0;		// LED 밝기 조정 변수
	int direction = 1;	// 1 : 밝기 증가 모드 / -1 : 감소 모드
	
	DDRA = 0xFF;
	PORTA = 0xFF;		// LED All On
	// Dark => Bright; Bright => Dart
	
	while (1)
	{
		led_on_pwm_sw_manner(dim);
		dim += direction;
		if (dim == 255) {
			direction = -1;
		}
		if (dim == 0) {
			direction = 1;
		}
	}
}

void led_on_pwm_sw_manner(int dim)
{
	PORTA = 0xFF;
	
	for (int i = 0; i < 256; i++) {
		if (i > dim) {
			PORTA = 0x00;	// Duty Cycle이 max를 넘어가면 led all off
		}
		_delay_us(20);
	}
}
