#include <avr/io.h>
#include <avr/interrupt.h>

#define ACTIVE		1
#define STOP		0

#define FORWARD		1
#define REVERSE		0

// 타이머 변수
volatile uint32_t debounce_timer;						// 버튼 디바운싱 카운터
volatile uint32_t milliseconds;							// 밀리초 카운터
volatile uint32_t fnd_circle_timer;						// FND circle 출력용 카운터
volatile uint32_t beep_timer;							// beep 제어용 카운터
volatile uint32_t displayUpdateCounter;					// 7-Segment 디스플레이 갱신 주기 제어 변수
volatile uint32_t lcd_displayUpdateCounter;				// lcd 디스플레이 갱신 주기 제어 변수
volatile uint16_t ultrasonic_check_timer;				// 초음파를 주기적으로 측정하기 위한 타이머 변수
volatile uint16_t ultrasonic_print_timer;				// 디버깅을 위해 거리를 출력하기 위한 타이머 변수
volatile uint32_t buzzer_timer;						// 피에조 부조 출력을 제어하기 위한 타이머 변수

volatile uint32_t motor_speed;						// 모터 속도를 가시적으로 나타내기 위한 변수


// 토글 변수
volatile uint8_t timer_active;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t beep_active;						// 1 : 활성 <-> 0 : 정지
volatile uint8_t btn_debounce_active;				// 1 : 활성 <-> 0 : 정지

volatile uint8_t motor_active;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t motor_forward;					// 1 : forward <-> 0: reverse

// 함수 프로토타입
void reset_time(void);