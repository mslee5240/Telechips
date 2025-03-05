// 조건부 컴파일
#ifndef LED_H_
#define LED_H_

#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>

void led_main(void);
void led_all_on(void);
void led_all_off(void);
void shift_left_led_on(void);
void shift_right_led_on(void);
void shift_left_keep_led_on();
void shift_right_keep_led_on();
void shift_left_keep_led_off();
void shift_right_keep_led_off();
void flower_on(void);
void flower_off(void);

#endif /* LED_H_ */