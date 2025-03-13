#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "led.h"
#include "button.h"
#include "fnd.h"
#include "uart0.h"
#include "uart1.h"
#include "ultrasonic.h"
#include "pwm.h"

volatile int msec_count = 0;
volatile int ultrasonic_check_timer = 0;

// stdout에 UART0_transmit을 연결하여
// printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE); // For printf()

// Timer0 오버플로우 인터럽트 벡터
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	msec_count++;
	ultrasonic_check_timer++;
}

void init_timer_0(void);

extern volatile int fp_num;
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
volatile int fp_num = -1;

int main(void)
{
	// 타이머0 및 UART 초기화
	init_timer_0();
	init_uart0();
	init_uart1();
	init_ultrasonic();
	
	// 표준 출력(stdout)을 UART0의 OUTPUT 스트림에 연결
	stdout = &OUTPUT;
	
	// 전역 인터럽트 허용
	sei();
	
	// 초기화 확인 메시지
	//printf("init_uart0\n ");
	
	// 기타 주변장치 초기화 (LED, 버튼 등)
	init_led();
	init_button();
	
	//pwm_led_control_sw_manner();
	//pwm_fan_control_main();
	L298N_pwm_fan_control_main();
	
	int button_state[4] = { 0 };
	
	while (1)
	{
		distance_ultrasonic();
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


