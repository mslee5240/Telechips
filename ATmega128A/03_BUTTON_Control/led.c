#include "led.h"

void led_main(void)
{
	DDRA = 0xff;    // PORTA의 모든 핀을 출력(OUTPUT)으로 설정
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
	PORTA = 0x01;
	for (int i = 0; i < 8; i++)
	{
		_delay_ms(30);
		PORTA <<= 1;
	}
}

void shift_right_led_on(void)
{
	PORTA = 0x80;
	for (int i = 0; i < 8; i++)
	{
		_delay_ms(30);
		PORTA >>= 1;
	}
}

void shift_left_keep_led_on()
{
	PORTA &= 0x00;  // PORTA를 0으로 초기화하는 의미를 명확히 하기 위함
	for (int i = 0; i < 8; i++)
	{
		PORTA |= 1 << i;	// PORTA += 1 << i;
		_delay_ms(30);
	}
}

void shift_right_keep_led_on()
{
	PORTA &= 0x00;
	for (int i = 0; i < 8; i++)
	{
		PORTA |= 0x80 >> i;	// PORTA += 1 >> i;
		_delay_ms(30);
	}
}

void shift_left_keep_led_off()
{
	PORTA |= 0xff;
	for (int i = 0; i < 8; i++)
	{
		PORTA &= ~(1 << i);  // PORTA -= 1 << i;
		_delay_ms(30);
	}
}

void shift_right_keep_led_off()
{
	PORTA = 0xff;
	for (int i = 7; i >= 0; i--)
	{
		PORTA &= ~(1 << i);     // PORTA -= 0b10000000 >> i;
		_delay_ms(30);
	}
}

void flower_on(void) {
	PORTA = 0x00;
	_delay_ms(30);

	for (int i = 0; i < 4; i++)
	{
		PORTA |= (1 << (4 + i)) | (1 << (3 - i));   // PORTA |= 0x10 << i | 0x08 >> i;
		_delay_ms(30);
	}
}

void flower_off(void) {
	PORTA = 0xFF;
	_delay_ms(30);

	for (int i = 3; i >= 0; i--)
	{
		PORTA &= ~((1 << (4 + i)) | (1 << (3 - i)));    // PORTA &= PORTA >> 1 & PORTA << 1;
		_delay_ms(30);
	}
}

void flower_off_2(void) {
	PORTA = 0xFF;
	_delay_ms(30);

	for (int i = 0; i < 4; i++)
	{
		PORTA &= ~((1 << (4 + i)) | (1 << (3 - i)));    // PORTA &= PORTA >> 1 & PORTA << 1;
		_delay_ms(30);
	}
}