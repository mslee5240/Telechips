#include "isr.h"

// 타이머 변수
volatile uint32_t debounce_timer = 0;					// 버튼 디바운싱 카운터
volatile uint32_t milliseconds = 0;						// 밀리초 카운터
volatile uint32_t fnd_circle_timer = 0;					// FND circle 출력용 카운터
volatile uint32_t beep_timer = 0;						// beep 제어용 카운터
volatile uint32_t displayUpdateCounter = 0;				// 7-Segment 디스플레이 갱신 주기 제어 변수
volatile uint32_t lcd_displayUpdateCounter = 0;			// lcd 디스플레이 갱신 주기 제어 변수
// 초음파를 주기적으로 측정하기 위한 타이머 변수 
volatile uint16_t ultrasonic_check_timer = 0;			
volatile uint16_t ultrasonic_print_timer = 0;			// 디버깅을 위해 거리를 출력하기 위한 타이머 변수
volatile uint32_t buzzer_timer = 0;						// 피에조 부조 출력을 제어하기 위한 타이머 변수

volatile uint32_t motor_speed = 5;						// 모터 속도를 가시적으로 나타내기 위한 변수

// 토글 변수
volatile uint8_t timer_active = ACTIVE;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t beep_active = STOP;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t btn_debounce_active = STOP;				// 1 : 활성 <-> 0 : 정지

volatile uint8_t motor_active = ACTIVE;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t motor_forward = FORWARD;					// 1 : forward <-> 0: reverse

// Timer0 오버플로우가 발생할 때마다 호출되는 인터럽트 서비스 루틴(ISR).
// - 분주비 설정에 따라 일정 시간마다 오버플로우가 일어남
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	
	displayUpdateCounter++;				// 디스플레이 갱신 신호
	lcd_displayUpdateCounter++;
	ultrasonic_check_timer++;			// 초음파 센서 측정을 일정 주기로 실행하기 위해 증가
	ultrasonic_print_timer++;			// 디버깅용 거리를 출력하기 위해 증가
	
	if (timer_active == ACTIVE)
	{
		milliseconds++;					// 밀리초 카운터 증가
		fnd_circle_timer += (motor_speed % 6);	// motor speed에 따라 증가량 변동
	}
	
	buzzer_timer++;
	
	if (beep_active == ACTIVE)
	{
		beep_timer++;
		if (beep_timer > 100) {
			mute();
		}
	}
	
	if (btn_debounce_active)
	{
		debounce_timer++;
	}
}

void reset_time() {
	milliseconds = 0;
}