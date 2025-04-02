/*
 * button.c
 *
 *  Created on: Mar 26, 2025
 *      Author: microsoft
 */

#include "button.h"
#include "led.h"

void init_button_pullup(void)
{
	GPIOC->PUPDR |= 1 << (0 << 1); // 0 * 2
	GPIOC->PUPDR |= 1 << (1 << 1);
	GPIOC->PUPDR |= 1 << (2 << 1);
	GPIOC->PUPDR |= 1 << (3 << 1);
}

void button_toggle_test(void)
{
	init_button_pullup();
	led_all_off();
	while(1)
	{
		if(get_button(GPIOC, GPIO_PIN_0, BTN_0) == BUTTON_PRESS)
		{
			led_n_toggle(0);
		}
		if(get_button(GPIOC, GPIO_PIN_1, BTN_1) == BUTTON_PRESS)
		{
			led_n_toggle(1);
		}
		if(get_button(GPIOC, GPIO_PIN_2, BTN_2) == BUTTON_PRESS)
		{
			led_n_toggle(2);
		}
		if(get_button(GPIOC, GPIO_PIN_3, BTN_3) == BUTTON_PRESS)
		{
			led_n_toggle(3);
		}
		if(get_button(GPIOC, GPIO_PIN_13, BTN_4) == BUTTON_PRESS)
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);	// demo b'd led toggle
		}
	}
}

// 버튼이 연결된 GPIO 포인터를 받아온다
int get_button(GPIO_TypeDef *GPIO, int GPIO_pin, int button_num)
{
	static unsigned char button_status[] = {
		BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE
	};
	// 5개의 버튼

	int currtn_state = !(!(GPIOC->IDR & GPIO_pin));


	if(currtn_state == BUTTON_PRESS && button_status[button_num] == BUTTON_RELEASE)
	{

		HAL_Delay(60);
		button_status[button_num] = BUTTON_PRESS;
		return BUTTON_RELEASE;
	}
	else if(currtn_state == BUTTON_RELEASE && button_status[button_num] == BUTTON_PRESS)
	{

		HAL_Delay(60);
		button_status[button_num] = BUTTON_RELEASE;
		return BUTTON_PRESS;
	}

	return BUTTON_RELEASE;

}
