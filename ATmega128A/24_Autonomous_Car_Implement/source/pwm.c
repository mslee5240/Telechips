#include "pwm.h"
#include "buzzer.h"
extern int func_idx;

/*
	16bit Timer1 활용
	PWM 출력 신호 (2EA)
	===================
	PE5 : OC1A - 왼쪽 바퀴
	PE6 : OC1B - 오른쪽 바퀴
	BTN0 : Auto / Manual
*/
void init_timer1(void)
{
	// 분주비 64 설정: 16MHz / 64 = 250KHz (타이머 틱: 4us)
	// 256 카운트 시 약 1.02ms, 127 카운트 시 약 0.5ms 소요 (참조: p.318 표 14-1)
	TCCR1B |= 1 << CS11 | 1 << CS10;
	
	// Timer1을 고속 PWM 모드(모드 14)로 설정 (참조: p.327 표14-5) : 상향 카운트만 존재 (단일 경사 모드)
	// ICR1 레지스터 이용
	TCCR1A |= 1 << WGM11;	// TOP을 ICR에 지정 가능
	TCCR1B |= 1 << WGM13 | 1 << WGM12;
	
	// 반전 모드 TOP : ICR1 비교일치값(PWM) 지정 : OCR1A, OCR1B
	// 비반전 모드 : 비교 일치 발생시 OCn의 출력핀이 LOW로 바뀌고 BOTTOM에서 HIGH로 바뀐다.
	TCCR1A |= 1 << COM1A1 | 1 << COM1B1;
	
	ICR1 = 0x3ff;	// 1023 => 4ms, TOP : PWM값
}


/*
	방향 설정
	=========
	1. LEFT MOTOR
		- PF0 : IN1 (motor driver)
		- PF1 : IN2
	2. RIGHT MOTOR
		- PF2 : IN3	(motor driver)	// 임의로 설정 가능
		- PF3 : IN4
	
	IN1/IN3		IN2/IN4
	====================
	   0			1	:	역회전
       1			0	:	정회전
	   1			1	:	정지
*/
void init_L298N(void)
{
	MOTOR_PWM_DDR |= 1 << MOTOR_LEFT_PORT_DDR | 1 << MOTOR_RIGHT_PORT_DDR;	// 출력 모드로 설정
	MOTOR_DRIVER_DIRECTION_DDR |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;		// IN1 IN2 IN3 IN4 출력
	
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 2;		// 자동차를 전진 모드로 설정
}

void stop(void)
{
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;		// 정지 모드로 설정
}

void forward(int speed)
{
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 2;		// 전진 모드로 설정
	
	OCR1A = OCR1B = speed;	// PB5(OCR1A): 왼쪽, PB6(OCR1B): 오른쪽
}

void backward(int speed)
{
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 1 | 1 << 3;		// 후진 모드로 설정 1010
	
	OCR1A = OCR1B = speed;	// PB5(OCR1A): 왼쪽, PB6(OCR1B): 오른쪽
}

void turn_left(int speed)
{
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 2;		// 전진 모드
	
	OCR1A = 0;		// PB5(OCR1A): 왼쪽
	OCR1B = speed;	// PB6(OCR1B): 오른쪽
}

void turn_right(int speed)
{
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 2;		// 전진 모드
	
	OCR1A = speed;	// PB5(OCR1A): 왼쪽
	OCR1B = 0;		// PB6(OCR1B): 오른쪽
}

void auto_drive_mode(void) {
	siren(1);	// 사이렌 재생
	
	MOTOR_DRIVER_DIRECTION_PORT &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	MOTOR_DRIVER_DIRECTION_PORT |= 1 << 0 | 1 << 2;		// 전진 모드
	
	uint16_t base_speed = 0;
	int32_t error = 0;  // 회전 보정을 위한 오차 (음수 가능)
	
	// turning mode: 중앙 센서 값이 THRESH_CLOSE 미만이면 turning 적용
	if (ultrasonic_dis[LEFT] < THRESH_CLOSE | ultrasonic_dis[MID] < THRESH_CLOSE | ultrasonic_dis[RIGHT] < THRESH_CLOSE) {
		// 부호 있는 정수로 변환하여 에러 계산
		int32_t left_error = (int32_t)ultrasonic_dis[MID] - (int32_t)ultrasonic_dis[LEFT];
		int32_t right_error = (int32_t)ultrasonic_dis[MID] - (int32_t)ultrasonic_dis[RIGHT];
		
		// error = 오른쪽 에러 - 왼쪽 에러
		error = right_error - left_error;
		base_speed = SPEED_80;
	} else {
		// forward mode: 장애물이 충분히 멀다면
		if (ultrasonic_dis[MID] <= THRESH_SAFE) {
			base_speed = SPEED_80;
		} else {
			base_speed = MAX_SPEED;
		}
		error = 0;
	}
	
	// 모터 속도 계산:
	// error가 양수이면 왼쪽 모터 속도는 base_speed - (KP * error),
	// 오른쪽 모터 속도는 base_speed + (KP * error)
	// 양수 error -> 왼쪽으로 회전 (오른쪽 모터 빠름)
	int32_t left_speed = (int32_t)base_speed - KP * error;
	int32_t right_speed = (int32_t)base_speed + KP * error;
	
	// 속도 범위 0 ~ MAX_SPEED로 클램핑
	if (left_speed < 0) { 
		left_speed = 0;
	}
	if (left_speed > MAX_SPEED) {
		left_speed = MAX_SPEED;
	}
	if (right_speed < 0) {
		right_speed = 0;
	}
	if (right_speed > MAX_SPEED) {
		right_speed = MAX_SPEED;
	}
	
	// 계산된 모터 속도를 OCR1A와 OCR1B에 설정
	OCR1A = left_speed;
	OCR1B = right_speed;
}

