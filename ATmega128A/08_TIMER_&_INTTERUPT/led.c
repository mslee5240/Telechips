#include "led.h"

extern volatile int msec_count;

volatile int state = 0;

#define FUNC_NUM	8;
void state_transition(void);
void state_transition(void) {
	state++;
	state %= FUNC_NUM;
}

void (*fp[])() =
{
	shift_left_led_on,
	shift_right_led_on,
	shift_left_keep_led_on,
	shift_left_keep_led_off,
	shift_right_keep_led_on,
	shift_right_keep_led_off,
	flower_on,
	flower_off
};

void led_main(void)
{
	DDRA = 0xff;    // PORTA의 모든 핀을 출력(OUTPUT)으로 설정
	
	while (1)
	{
		
		if (state > 7) {
			state = 0;
		}
		fp[state]();

	}
}


void led_all_on(void)
{
	PORTA = 0xff;
}

void led_all_off(void)
{
	PORTA = 0x00;
}

void shift_left_led_on(void)
{
	// (1) for문 제거, (2) _delay_ms(30) 제거
	static int i = 0;
	
	if (msec_count >= 100) 
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			PORTA = 0;
			state++;
		}
		else {
			PORTA = 0x01 << i++;	// 후위 연산자
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
			state++;
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
			state++;
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
			state++;
		}
		else {
			PORTA |= (0x80 >> i);
			i++;
		}
	}
}


void shift_left_keep_led_off()
{
	static int i = 0;
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i >= 8) {
			i = 0;
			state++;
		}
		else {
			PORTA &= ~(1 << i);  // PORTA -= 1 << i;
			i++;
		}
	}
}

void shift_right_keep_led_off()
{
	static int i = 7;
	if (msec_count >= 100)
	{
		msec_count = 0;
		if (i < 0) {
			i = 7;
			state++;
			PORTA = 0;
		}
		else {
			PORTA &= ~(1 << i);
			i--;
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
			state++;
			PORTA = 0xff;
		}
		else {
			PORTA |= ((1 << (4 + i)) | (1 << (3 - i)));
			i++;
		}
	}
}


void flower_off(void) {
	static int i = 3;
	if (msec_count >= 200)
	{
		msec_count = 0;
		if (i <= 0) {
			i = 3;
			PORTA = 0x00;
			state++;
		}
		else {
			PORTA &= ~((1 << (4 + i)) | (1 << (3 - i)));
			i--;
		}
	}
}

void flower_off_2(void) {
	static int i = 0;
	if (msec_count >= 50)
	{
		msec_count = 0;
		if (i >= 4) {
			i = 0;
			PORTA = 0xFF;
		}
		else {
			PORTA &= ~((1 << (4 + i)) | (1 << (3 - i)));
			i++;
		}
	}
}
