#include <avr/io.h>
#include <avrinterrupt.h>
#include <stdio.h>

#include "led.h"
#include "button.h"
#include "fnd.h"
#include "uart0.h"

volatile int msec_count = 0;

// stdout에 UART0_transmit을 연결하여 
// printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect)
{
    // 오버플로우가 발생할 때마다 TCNT0를 6으로 재설정
    TCNT = 6;
    msec_count++;
}

void init_timer_0(void);

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