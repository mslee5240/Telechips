#include <avr/io.h>

#define LED_DDR		    DDRB	// LED 데이터 방향 레지스터
#define LED_PORT	    PORTB   // LED 포트 출력 레지스터

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

void pwm_led_control_sw_manner(void);
void led_on_pwm_sw_manner(int dim);

