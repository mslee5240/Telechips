#include "isr.h"

extern volatile uint32_t seconds;		

// 타이머 변수
volatile uint32_t debounce_timer = 0;					// 디바운싱 카운터
volatile uint32_t milliseconds = 0;						// 밀리초 카운터
volatile uint32_t fnd_circle_timer = 0;					// FND circle 출력용 카운터
volatile uint32_t wash_mode_timer = 0;					// wash_mode 제어용 카운터
volatile uint32_t beep_timer = 0;						// beep 제어용 카운터
volatile uint32_t displayUpdateCounter = 0;				// 디스플레이 갱신 주기 제어 변수
volatile uint32_t ultrasonic_check_timer = 0;			// 초음파를 주기적으로 측정하기 위한 타이머 변수
volatile uint32_t motor_speed = 5;						// 모터 속도를 왼쪽 FND(Circle)에 출력하기 위한 변수

// 토글 변수
volatile uint8_t timer_active = 0;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t beep_active = 0;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t btn_debounce_active = 0;				// 1 : 활성 <-> 0 : 정지

// Timer0 오버플로우가 발생할 때마다 호출되는 인터럽트 서비스 루틴(ISR).
// - 분주비 설정에 따라 일정 시간마다 오버플로우가 일어남
ISR(TIMER0_OVF_vect)
{
	// Timer0의 오버플로우 시점마다 TCNT0를 재설정해서 1ms 간격을 유지
	TCNT0 = 6;
	
	if (timer_active)
	{
		milliseconds++;					// 밀리초 카운터 증가
		fnd_circle_timer += (motor_speed % 6);	// motor speed에 따라 증가량 변동
		wash_mode_timer++;				// wash_mode
	}
	
	if (beep_active)
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
	
	displayUpdateCounter++;				// 디스플레이 갱신 신호
	
	ultrasonic_check_timer++;			// 초음파 센서 측정을 일정 주기로 실행하기 위해 증가
}

void reset_time() {
	milliseconds = 0;
	seconds = 0;
}