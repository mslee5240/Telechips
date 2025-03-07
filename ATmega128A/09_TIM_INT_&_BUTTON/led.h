// 조건부 컴파일
#ifndef LED_H_
#define LED_H_

#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>

void init_led(void);
void led_main(void);
void led_all_on(void);
void led_all_off(void);
void shift_left_led_on(void);
void shift_right_led_on(void);
void shift_left_keep_led_on();
void shift_right_keep_led_on();
void flower_on(void);
void flower_off(void);

#define FUNC_NUM	6;
void state_transition(void);
void manual_transition(void);

void led_auto(void);
void led_manual(void);

#endif /* LED_H_ */