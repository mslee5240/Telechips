#include "main.h"

// 토글 변수
volatile uint8_t motor_active = 0;					// 1 : 활성 <-> 0 : 정지
volatile uint8_t motor_forward = 1;					// 1 : forward <-> 0: reverse

// 모터 상태: STOP=0, RUN=1, PAUSE=2
volatile uint8_t motor_state = 0;

volatile uint32_t seconds = 0;						// 남은 시간(초)
volatile uint32_t half_seconds = 0;					// 0.5초 단위 카운터 (fnd_circle_timer에서 0.5초마다 증가)

// 포인터를 사용해 디스플레이 함수에 시간 데이터를 전달
volatile uint32_t* f_sec = &seconds;
volatile uint32_t* f_hsec = &half_seconds;

// 함수 프로토타입 선언: 타이머 및 전체 초기화 함수
void init_all(void);
void wash_mode(void);
void motor_direction_change(void);
void toggle_motor_state(void);

void seconds_count(void);		// 1초 Count
void half_seconds_count(void);	// 0.5초 Count
void displayUpdate(void);		// 7-Segment Display 갱신

void motor_start(void);
void motor_stop(void);
void control_led_by_time(void);

// 버튼 시간 선택 관련
int button_state[4] = { 0 };	// 버튼 상태 배열
int select_time_0 = 0;
int select_time_1 = 0;
int select_time_2 = 0;
int select_time[] = { 5, 10, 20, 30 };

// 표시 제어를 위한 변수
int timeORselect = 1;
int circleORselect = 1;
int washORrinseORdry = 0;

extern int samsung[];
extern int samsung_beats[];

void toggle_motor_state(void)
{
	// STOP 상태 -> RUN 시작
	if (motor_state == 0) {
		// 버튼 0, 1, 2에서 지정한 시간 합산
		*f_sec = select_time_0 + select_time_1 + select_time_2;
		// 모터 구동 시작
		motor_start();
		motor_state = 1;	// RUN 상태로 전환
	}
	// RUN 상태 -> PAUSE(일시정지)
	else if (motor_state == 1) {
		motor_stop();
		motor_state = 2;	// PAUSE
	}
	// PAUSE 상태 -> RUN(재개)
	else if (motor_state == 2) {
		motor_start();
		motor_state = 1;	// RUN
	}
}


int main(void)
{
	// 모든 주변장치 초기화
	init_all();
	
	while (1)
	{
		seconds_count();		// 1초 Count
		half_seconds_count();	// 0.5초 Count
		displayUpdate();		// 7-Segment Display 갱신
		
		// LED 동작
		control_led_by_time();
		
		// 0번 버튼 입력
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			button_state[0]++;
			button_state[0] %= 4;
			
			timeORselect = 0;
			circleORselect = 0;
			washORrinseORdry = 0;
			
			select_time_0 = select_time[button_state[0]];
		}
		
		// 1번 버튼 입력
		else if (get_button(BUTTON_1, BUTTON_1_PIN))	// Up Speed
		{
			button_state[1]++;
			button_state[1] %= 4;
			
			timeORselect = 0;
			circleORselect = 0;
			washORrinseORdry = 1;
			
			select_time_1 = select_time[button_state[1]];
		}
		
		// 2번 버튼 입력
		else if (get_button(BUTTON_2, BUTTON_2_PIN))	// Down Speed 
		{
			button_state[2]++;
			button_state[2] %= 4;
			
			timeORselect = 0;
			circleORselect = 0;
			washORrinseORdry = 2;
			
			select_time_2 = select_time[button_state[2]];
		}
		
		// 3번 버튼 입력
		else if (get_button(BUTTON_3, BUTTON_3_PIN))	// Motor Direction
		{
			timeORselect = 1;
			circleORselect = 1;
			
			// 모터 상태를 토글(STOP->RUN, RUN->PAUSE, PAUSE->RUN)
			toggle_motor_state();
		}
		
		// 시간 선택 완료 후 최종 동작
		if (*f_sec > 0) {
			wash_mode();
		}
		else if(motor_state == 1 & *f_sec == 0) {
			motor_state = 0;
			motor_stop();
			music_player(samsung, samsung_beats);
		}
	}
	
	return 0;
}


void wash_mode(void)
{
	if (wash_mode_timer > 2500) {
		motor_direction_change();
		wash_mode_timer = 0;
	}
}

// 모터 방향 토글
void motor_direction_change(void)
{
	motor_forward = !motor_forward;
	PORTF = 1 << 6 | 1 << 7;				// IN1, IN2 reset
	PORTF = 0;
	PORTF = (motor_forward) ? (PORTF | 1 << 6) : (PORTF | 1 << 7);
	OCR3C = 250;
}

// 모든 주변장치 초기화
void init_all(void)
{
	init_button();
	init_fnd();
	init_timer0();
	init_timer3();
	init_L298N();
	init_buzzer();
	
	// 전역 인터럽트 허용
	sei();
}

void seconds_count(void)
{
	// 1초 Count
	if (milliseconds > 999) {
		milliseconds = 0;
		seconds--;
	}
}

void half_seconds_count(void)
{
	// 0.5초 Count
	if (fnd_circle_timer > 499) {
		fnd_circle_timer = 0;
		half_seconds++;
	}
}

void displayUpdate(void){
	// 7-Segment Display 갱신
	if (displayUpdateCounter > 1) {
		displayUpdateCounter = 0;
		
		// 출력 함수 호출
		fnd_display_0(f_sec, f_hsec);
	}
}

void motor_start(void)
{
	timer_active = 1;	// timer 활성화
	motor_active = 1;	// motor 활성화
	OCR3C = 250;
	motor_speed = 5;
}

void motor_stop(void)
{
	timer_active = 0;	// timer 비활성화
	motor_active = 0;	// motor 비활성화
	OCR3C = 0;
	motor_speed = 0;
}

void control_led_by_time(void)
{
	uint32_t remain = *f_sec;
	uint32_t s0 = select_time_0;
	uint32_t s1 = select_time_1;
	uint32_t s2 = select_time_2;

	uint8_t led_value = 0x00;

	// 첫 구간 남아있으면 PB3 켜기
	if (remain > (s1 + s2)) {
		led_value |= 0x08;  // PB2
	}
	// 둘째 구간 남아있으면 PB2 켜기
	if (remain > s2) {
		led_value |= 0x04;  // PB1
	}
	// 셋째 구간 남아있으면 PB0 켜기
	if (remain > 0) {
		led_value |= 0x01;  // PB0
	}

	PORTB = led_value;
}
