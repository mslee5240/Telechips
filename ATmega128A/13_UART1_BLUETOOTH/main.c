#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "led.h"
#include "button.h"
#include "fnd.h"
#include "uart0.h"

volatile int msec_count = 0;

// stdout에 UART0_transmit을 연결하여
// printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE); // For printf()

// Timer0 오버플로우 인터럽트 벡터
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
	// 타이머0 및 UART 초기화
	init_timer_0();
	init_uart0();
	
	// 표준 출력(stdout)을 UART0의 OUTPUT 스트림에 연결
	stdout = &OUTPUT;
	
	// 전역 인터럽트 허용
	sei();
	
	// 초기화 확인 메시지
	printf("init_uart0\n ");
	
	// 기타 주변장치 초기화 (LED, 버튼 등)
	init_led();
	init_button();
	
	int button_state[4] = { 0 };
	
    while (1) 
    {
		// 수신된 명령이 있으면 처리
		pc_command_processing();
		
		if (fp_num >= 0 && fp_num< 8)
		{
			fp_led[fp_num]();
			// 예: shift_left_led_on() 등은 내부에서 msec_count 등을 확인하며
			//     100ms마다 한 칸씩 LED를 움직이도록 작성되어 있음
		}
    }
	return 0;
}

void init_timer_0(void)
{
	// 초기 카운터값 설정
	TCNT0 = 6;
	
	// 분주비 256 : CS02 = 1, CS01 = 0, CS00 = 0
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	
	// Timer0 오버플로우 인터럽트 허용
	TIMSK |= (1 << TOIE0);
}


