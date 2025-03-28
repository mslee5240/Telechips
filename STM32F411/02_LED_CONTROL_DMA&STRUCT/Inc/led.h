#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"	// HAL_driver GPIO Info

#define GPIOB_ODR 	0x040020414		// ODR : Output Data Register

// 함수 프로토타입 선언
void led_all_on(void);
void led_all_off(void);
void led_main(void);

void shift_left_led_on(void);
void shift_right_led_on(void);
void shift_left_keep_led_on(void);
void shift_right_keep_led_on(void);
void flower_on(void);
void flower_off(void);

#endif /* INC_LED_H_ */
