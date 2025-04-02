/*
 * button.h
 *
 *  Created on: Mar 26, 2025
 *      Author: microsoft
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define GPIOC_IDR	0x40020810

#define BTN_0	0	// PC0
#define BTN_1	1	// PC1
#define BTN_2	2	// PC2
#define BTN_3	3	// PC3
#define BTN_4	4	// PC13 데모보드에 연결된 버튼

#define BUTTON_PRESS	0	// active low
#define BUTTON_RELEASE	1

void button_toggle_test(void);
int get_button(GPIO_TypeDef *GPIO, int GPIO_pin, int button_num);
void init_button_pullup(void);

#endif /* INC_BUTTON_H_ */
