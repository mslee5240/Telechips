#define F_CPU 16000000UL
#include <avr/io.h>      
#include <util/delay.h>     
#include <avr/interrupt.h>

#include "led.h"
#include "button.h"
#include "fnd.h"
#include "interrupt.h"

volatile int msec_count = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	msec_count++;
}

void init_timer_0(void);

int main(void)
{
	init_timer_0();
	
	init_led();
	init_button();
	int button_state[4] = { 0 };
	
	void (*fp_0[])() =
	{
		led_auto,
		led_manual,
	};

	while (1)
	{
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			button_state[0]++;
			button_state[0] %= 2;
			init_led();
		}
		fp_0[button_state[0]]();

		if (get_button(BUTTON_1, BUTTON_1_PIN))
		{
			button_state[1]++;
			button_state[1] %= 1;
			init_led();
			manual_transition();
		}
	}

	return 0;
}

void init_timer_0(void)
{
	TCNT0 = 6;
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;
	TIMSK |= 1 << TOIE0;
	sei();
}