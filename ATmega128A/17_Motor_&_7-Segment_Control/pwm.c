#include "pwm.h"

/*
	ATmega128A PWM 및 모터 제어 설정
	-------------------------------
	- 16비트 Timer3를 사용하여 8비트 고속 PWM 모드(모드 5)로 PWM 신호 생성
	- PWM 출력 핀:
		- PE3 : OC3A
		- PE4 : OC3B (초음파 에코 펄스 감지를 위해 외부 인터럽트(INT4)로 사용)
		- PE5 : OC3C (모터 연결)
	- 버튼 기능:
		- BTN0 : 시작/정지
		- BTN1 : 속도 증가 (OC3C PWM 값 20씩 증가, 최대 250)
		- BTN2 : 속도 감소 (OC3C PWM 값 20씩 감소, 최소 60)
*/

void init_timer3(void)
{
	// PE3(OC3A)와 PE5(OC3C)를 출력으로 설정
	// PE4는 초음파 에코 감지를 위합 입력(INT4)로 사용되므로 출력 설정 제외
	DDRE |= 1 << 3 | 1 << 5;
	
	// Timer3를 8비트 고속 PWM 모드(모드 5)로 설정 (참조: p.348 표15-6)
	TCCR3A |= 1 << WGM30;
	TCCR3B |= 1 << WGM32;
	
	// OC3C 채널을 비반전 PWM 모드로 설정
	// (타이머 카운터 값이 OCR3C와 일치할 때 OC3C 핀을 LOW로, BOTTOM에서는 HIGH로 설정)
	// (참조: p.350 표15-7)
	TCCR3A |= 1 << COM3C1;
	
	// 분주비 64 설정: 16MHz / 64 = 250KHz (타이머 틱: 4us)
	// 256 카운트 시 약 1.02ms, 127 카운트 시 약 0.5ms 소요 (참조: p.318 표 14-1)
	TCCR3B |= 1 << CS31 | 1 << CS30;

	// OC3C의 PWM duty cycle 초기값 0으로 설정
	OCR3C = 0;
}

// PF6 : IN1 (L298N)
// PF7 : IN2 (L298N)
// PF6(IN1), PF7(IN2)
//    0          0   : 정지
//    1          0   : 정회전
//    0          1   : 역회전
//    1          1   : STOP
void init_L298N(void)
{
	// PF6(IN1)와 PF7(IN2)를 출력으로 설정 (L298N 모터 드라이버 제어용)
	DDRF |= 1 << 6 | 1 << 7;

	// PF6, PF7 핀 초기화 (LOW로 클리어)
	PORTF &= ~(1 << 6 | 1 << 7);

	// PF6를 HIGH로 설정하여 정회전 모드 지정
	// L298N 제어 입력 조합:
	// PF6(IN1), PF(IN2):
	//      0    0 -> 모터 정지
	//      1    0 -> 정회전
	//      0    1 -> 역회전
	//      1    1 -> 정지(브레이크)
	PORTF |= 1 << 6;
	
	// 모터 회전을 위한 초기 PWM duty cycle을 250으로 설정
	OCR3C = 250;
}
