#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "button.h"


void init_timer3(void);
void init_L298N(void);
void pwm_fan_control_main(void);
void L298N_pwm_fan_control_main(void);
