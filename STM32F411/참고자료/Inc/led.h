/*
 * led.h
 *
 *  Created on: Mar 26, 2025
 *      Author: microsoft
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"		// HAL_driver GPIO 정보

#define LED_DELAY 	30

#define GPIOB_ODR		0x40020414
#define GPIOB_ODR2		*(unsigned int *)0x40020414

void led_main(void);

void led_n_on(int n);
void led_n_off(int n);
void led_n_toggle(int n);
void led_all_on(void);
void led_all_off(void);
void led_all_toggle(void);
void shift_left_ledon(void);
void shift_right_ledon(void);
void shift_left_keep_ledon(void);
void shift_right_keep_ledon(void);
void flower_on(void);
void flower_off(void);

#endif /* INC_LED_H_ */


