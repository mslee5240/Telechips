#define F_CPU 16000000UL
#include <avr/io.h>         // AVR 입출력 관련 라이브러리
#include <util/delay.h>     // 딜레이 함수 사용을 위한 라이브러리
#include <avr/interrupt.h>

#include "led.h"
#include "button.h"
#include "fnd.h"

volatile int msec_count = 0;	// 변수 type 앞에 volatile을 선언하는 이유: compiler에게 최적화 방지 지시
// cc -0

// TIMER0_OVF_vect : 교재 p.278 (표 12-3)
// ISR(Interrupt Service Routine) : H/W가 S/W에게 event(상황 변화)가 발생했다고 알려주는 공간
// 250개의 pulse를 count(1ms)하면 이곳으로 자동적으로 들어온다.
// ISR은 가능한 짧게 작성할 것

ISR(TIMER0_OVF_vect)
{
	// 6~256 : 250개(= 1ms), TCNT0를 6으로 설정하는 것.
	TCNT0 = 6;
	msec_count++;		// 1ms마다 1 증가
}

void init_timer_0(void);

int main(void)
{
	init_timer_0();
	led_main();
	
	// 간단한 Timer 예제
	int led_toggle = 0;
	while (1)
	{
		if (msec_count >= 1000)
		{
			msec_count = 0;
			led_toggle = !led_toggle;
		}
		
		if (led_toggle) { PORTA = 0xFF; }
		else { PORTA = 0x00; }
	}

	return 0;
}

// # timer0를 초기화 시키는 부분
// - 8bit timer 0번, 2번 중 0번 초기화
// - 임베디드 / FPGA 등에서 제일 중요한 것은 초기화를 정확히 해주는 것
// - 특별히 신경 써서 작성할 것!
void init_timer_0(void)
{
	// # [16MHz / 64] 분주(down); 분주: divider; prescaler
	// --- 분주비 계산 ----
	// (1) 16000000Hz / 64 = 250,000Hz
	// (2) T(주기): 1 clock의 소요 시간; T = 1 / f
	//		즉, T = 1 / 250,000 -> 0.0000004sec(= 4us; 0.004ms)
	// (3) 8bit Timer OV(OVflow) : 0.004ms * 256 = 0.001024sec(= 1.024ms)
	//		1m마다 정확하게 INTERRUPT를 띄우고 싶으면 0.004ms * 250개를 count = 0.001sec(= 1ms)
	TCNT0 = 6;	// TCNT : 0~256 1마다 TIMER0_OVF_Vector로 진입한다.
				// TCNT0 = 6으로 설정한 이유 : 6 -> 256 : 250개의 펄스를 count하기 때문에 정확히 1ms

	// (4) 분주비 설정, 64 분주 (250,000Hz -> 250KHz) 교재 p.296 (표 13-1)
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;		// TCCR0 |= 0xF4; 보다 좌측의 code 권장
	
	// (5) Timer0 Overflow INTERRUPT를 허용(Enable)
	TIMSK |= 1 << TOIE0;	// TIMSK |= 0x01;
	sei();	// 전역(대문)으로 interrupt 허용; set_enable_interrupt
}