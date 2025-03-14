#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "button.h"
#include "fnd.h"
#include "pwm.h"

// 전역 변수: 시간 측정 및 디스플레이 제어에 사용 
// (volatile로 선언하여 ISR과 공유)
volatile uint8_t timer_active = 1;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t motor_active = 1;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t motor_forward = 1;					// 1 : forward <-> 0: reverse

volatile uint32_t milliseconds = 0;					// 밀리초 카운터 (타이머 ISR에서 증가)
volatile uint32_t milliseconds_1 = 0;	
volatile uint32_t displayUpdateCounter = 0;			// 디스플레이 갱신 주기 제어 변수

volatile uint32_t seconds = 0;						// 초 단위 카운터 (milliseconds에서 1초마다 증가)
volatile uint32_t half_seconds = 0;					// 0.5초 단위 카운터 (milliseconds_1에서 0.5초마다 증가)
volatile uint32_t speed = 5;						// 모터 속도를 왼쪽 FND(Circle)에 출력하기 위한 변수

// 포인터를 사용해 디스플레이 함수에 시간 데이터를 전달
volatile uint32_t* f_sec = &seconds;
volatile uint32_t* f_hsec = &half_seconds;

// 함수 프로토타입 선언: 타이머 및 전체 초기화 함수
void init_timer_0(void);
void init_all(void);
void reset_time(void);

// Timer0 오버플로우 인터럽트 벡터
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;							// 타이머 카운터 재설정
	if (timer_active == 1)
	{
		milliseconds++;					// 밀리초 카운터 증가
		milliseconds_1 += (speed % 6);	// motor speed에 따라 증가량 변화
	}
	displayUpdateCounter++;				// 디스플레이 갱신 신호
}

int main(void)
{
	// 모든 주변장치 초기화
	init_all();
		
	while (1)
	{
		// 1초 Count
		if (milliseconds > 999) {
			milliseconds = 0;
			seconds++;
		}
		
		// 0.5초 Count
		if (milliseconds_1 > 499) {
			milliseconds_1 = 0;
			half_seconds++;
		}
		
		// 7-Segment Display 갱신
		if (displayUpdateCounter > 1) {
			displayUpdateCounter = 0;
			
			// 출력 함수 호출
			fnd_display_0(f_sec, f_hsec);
		}

		// 0번 버튼 입력
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			timer_active = !timer_active;		// Timer Toggle
			motor_active = !motor_active;		// Motor Toggle
			OCR3C = (motor_active) ? 250 : 0; 
			speed = 5;
		}
		
		// 1번 버튼 입력 - Up Speed
		else if (get_button(BUTTON_1, BUTTON_1_PIN))
		{
			OCR3C = (OCR3C + 20 > 250) ? 250 : (OCR3C + 20);	
			//OCR3C = (OCR3C >= 250) ? 250 : (OCR3C + 20);		// 교수님 코드: 250을 초과할 가능성 있음
			speed = (speed + 1 > 5) ? 5 : (speed + 1);			// 왼쪽 fnd에 속도를 출력하기 위한 변수 제어
		}
		
		// 2번 버튼 입력 - Down Speed 
		else if (get_button(BUTTON_2, BUTTON_2_PIN))
		{
			OCR3C = (OCR3C <= 70) ? 60 : (OCR3C - 20);
			speed = (speed - 1 < 1) ? 1 : (speed - 1);		// 왼쪽 fnd에 속도를 출력하기 위한 변수 제어
		}
		
		// 3번 버튼 입력 - Motor Direction Decision
		else if (get_button(BUTTON_3, BUTTON_3_PIN))
		{
			motor_forward = !motor_forward;				// Direction Toggle
			PORTF &= ~(1 << 6 | 1 << 7);				// IN1, IN2 reset
			PORTF = (motor_forward) ? (PORTF | 1 << 6) : (PORTF | 1 << 7);
			//		                          forward			  reverse
		}
	}
	
	return 0;
}

void init_timer_0(void)
{
	// 초기 카운터값 설정
	TCNT0 = 6;
	
	// 분주비: 256 [ CS02 = 1, CS01 = 0, CS00 = 0 ]
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	
	// Timer0 오버플로우 인터럽트 허용
	TIMSK |= (1 << TOIE0);
}

// 모든 주변장치 초기화
void init_all(void)
{
	init_button();
	init_fnd();
	init_timer0();
	init_timer3();
	init_L298N();
	
	// 전역 인터럽트 허용
	sei();
}

void reset_time() {
	milliseconds = 0;
	seconds = 0;
}
