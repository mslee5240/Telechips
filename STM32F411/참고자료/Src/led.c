/*
 * led.c
 *
 *  Created on: Mar 26, 2025
 *      Author: microsoft
 */


#include "led.h"
#include "extern.h"

char *func_names[] = {
	"led_all_on",
	"led_all_off",
	"shift_left_ledon",
	"shift_right_ledon",
	"shift_left_keep_ledon",
	"shift_right_keep_ledon",
	"flower_on",
	"flower_off"
};

void (*funcs[])(void) =
{
	led_all_on,
	led_all_off,
	shift_left_ledon,
	shift_right_ledon,
	shift_left_keep_ledon,
	shift_right_keep_ledon,
	flower_on,
	flower_off
};

void led_main(void)
{
	while(1)
	{

		for(int i = 0; i<50; i++)
		{
			delay_us(1000);
		}

		led_all_on();

		for(int i = 0; i<50; i++)
		{
			delay_us(1000);
		}

		led_all_off();

	}
}

void led_all_on(void)
{
	GPIOB->ODR |= 0xff;
}

void led_all_off(void)
{
	GPIOB->ODR &= ~(0xff);
}

void led_n_on(int n)
{
	GPIOB->ODR |= 1 << n;
}

void led_n_off(int n)
{
	GPIOB->ODR &= ~(1 << n);
}

void led_all_toggle(void)
{
	GPIOB->ODR ^= 0xff;
}

void led_n_toggle(int n)
{
	GPIOB->ODR ^= 1 << n;
}

void shift_left_ledon(void)
{
	int i;

	led_all_off();
	for(i = 0; i < 8; i++)
	{
		led_all_off();
		GPIOB->ODR |= 1 << i;
		HAL_Delay(LED_DELAY);
	}
}

void shift_right_ledon(void)
{
	int i;

	led_all_off();
	for(i = 0; i < 8; i++)
	{
		led_all_off();
		GPIOB->ODR |= 0x80 >> i;
		HAL_Delay(LED_DELAY);
	}
}

void shift_left_keep_ledon(void)
{
	int i;

	led_all_off();
	for(i = 0; i < 8; i++)
	{
		GPIOB->ODR |= 1 << i;
		HAL_Delay(LED_DELAY);
	}
}

void shift_right_keep_ledon(void)
{
	int i;

	led_all_off();
	for(i = 0; i < 8; i++)
	{
		GPIOB->ODR |= 0x80 >> i;
		HAL_Delay(LED_DELAY);
	}
}

void flower_on(void)
{
	int i;

	led_all_off();
	for(i = 0; i < 4; i++)
	{
		HAL_Delay(LED_DELAY);
		GPIOB->ODR |= 0x08 >> i | 0x10 << i;
	}
}

void flower_off(void)
{
	int i;

	led_all_on();
	for(i = 0; i < 4; i++)
	{
		HAL_Delay(LED_DELAY);
		*(unsigned int *)GPIOB_ODR &= ~(0x80 >> i | 0x01 << i);
	}
}
