#include <avr/io.h>
#include <avr/interrupt.h>

// 타이머 변수
volatile uint32_t debounce_timer;				// 디바운싱 카운터
volatile uint32_t milliseconds;					// 밀리초 카운터 (타이머 ISR에서 증가)
volatile uint32_t fnd_circle_timer;				// FND circle 출력용 카운터
volatile uint32_t wash_mode_timer;				// wash_mode 제어용 카운터
volatile uint32_t beep_timer;					// beep 제어용 카운터
volatile uint32_t displayUpdateCounter;				// 디스플레이 갱신 주기 제어 변수
volatile uint32_t ultrasonic_check_timer;			// 초음파를 주기적으로 측정하기 위한 타이머 변수
volatile uint32_t motor_speed;						// 모터 속도를 왼쪽 FND(Circle)에 출력하기 위한 변수

// 토글 변수
volatile uint8_t timer_active;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t beep_active;                   // 1 : 활성 <-> 0 : 정지			
volatile uint8_t btn_debounce_active;			// 1 : 활성 <-> 0 : 정지

// 함수 프로토타입
void reset_time(void);