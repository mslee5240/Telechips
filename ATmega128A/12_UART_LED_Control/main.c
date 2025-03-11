#include <avr/io.h>          
#include <avr/interrupt.h>
#include <stdio.h>	// printf, scanf, fgets, puts, gets 등

#include "led.h"
#include "button.h"
#include "fnd.h"
#include "uart0.h"

volatile int msec_count = 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE); // For printf()

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	msec_count++;
}

void init_timer_0(void);

extern int fp_num;
void (*fp_led[])(void) =
{
	led_all_on,
	led_all_off,
	shift_left_led_on,
	shift_right_led_on,
	shift_left_keep_led_on,
	shift_right_keep_led_on,
	flower_on,
	flower_off
};

int main(void)
{
	init_timer_0();
	init_uart0();
	stdout = &OUTPUT;	// printf가 동작될 수 있도록 stdout에 OUTPUT 파일포인터 assign
	sei();	// 전역으로 interrupt 허용
	
	printf("init_uart0\n ");
	
	init_led();
	init_button();
	int button_state[4] = { 0 };
	
	while (1)
	{
		
		pc_command_processing();
		
		// 만약 현재 명령(fp_num)이 있으면 그 함수를 계속 호출
		if (fp_num >= 0 && fp_num< 8)
		{
			fp_led[fp_num]();
			// 예: shift_left_led_on() 등은 내부에서 msec_count 등을 확인하며
			//     100ms마다 한 칸씩 LED를 움직이도록 작성되어 있음
		}
		
		//if (rx_msg_received)
		//{
			////printf("%s\n", (char *) rx_buff);
			//
			//rx_msg_received = 0;
		//}
	}
	return 0;
}

void init_timer_0(void)
{
	TCNT0 = 6;
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;
	TIMSK |= 1 << TOIE0;
}


