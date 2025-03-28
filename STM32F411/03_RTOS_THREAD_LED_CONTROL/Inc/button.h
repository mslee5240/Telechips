/*
 * button.h
 *
 *  Created on: Mar 26, 2025
 *      Author: eec04
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"	// HAL / GPIO config

#define BTN0			0	// PC0
#define BTN1			1	// PC1
#define BTN2			2	// PC2
#define BTN3			3	// PC3
#define BTN4			4	// PC13	Demo Board

#define BUTTON_NUMBER	5

#define BUTTON_PRESS	0	// Active Low
#define BUTTON_RELEASE	1	// Button을 뗀 상태

void button_led_toggle_test(void);
int get_button(GPIO_TypeDef* GPIO, int GPIO_Pin, int button_num);

#endif /* INC_BUTTON_H_ */
