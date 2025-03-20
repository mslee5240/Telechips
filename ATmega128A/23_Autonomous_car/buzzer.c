#include "buzzer.h"
// C, D, E, F, G, A, B(도, 레, 미, 파, 솔, 라, 시)

// [Samsung Washing Machine Melody]
// E A A C# C# A E E E E B A G# F# E
// E A A C# C# A E A G# F# G# A D# E
// E G# G# A G# F# G# A E A G# G# G# D B G# A
// A F# F# F# A A E E E E B G# A
// A G# F# F# F# A G# B A E E E E B G# A
// C# E B C# A F#
int samsung[] = {
	E5, A5, A5, C6S, C6S, A5, E5, E5, E5, E5, B5, A5, G5S, F5S, E5,
	E5, A5, A5, C6S, C6S, A5, E5, A5, G5S, F5S, G5S, A5, D5S, E5,
	E5, G5S, G5S, A5, G5S, F5S, G5S, A5, E5, A5, G5S, G5S, G5S, D6, B5, G5S, A5,
	A5, F5S, F5S, F5S, A5, A5, E5, E5, E5, E5, B5, G5S, A5,
	A5, G5S, F5S, F5S, F5S, A5, G5S, B5, A5, E5, E5, E5, E5, B5, G5S, A5,
	C6S, E6, B5, C6S, A5, F5S, '\0'
};

int samsung_beats[] = {
	B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8,
	B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_8, B_1_8, B_1_4, B_1_8, B_1_8,
	B_1_4, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8, B_1_4, B_1_4, B_1_4, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8, B_1_8, B_1_4,
	B_1_4, B_1_4, B_1_4, B_1_4, B_1_4, B_1_2, B_1_4, B_1_4, B_1_2, B_1_8, B_1_4, B_1_8, B_1_4,
	B_1_4, B_1_8, B_1_8, B_1_4, B_1_8, B_1_8, B_1_8, B_1_8, B_1_4, B_1_4, B_1_4, B_1_2, B_1_4, B_1_8, B_1_8, B_1_2,
	B_1_4, B_1_8, B_1_4, B_1_8, B_1_8, B_1_8
};

// - 인자로 전달된 음표 배열(tone)과 박자 배열(beats)을 순차적으로 읽어
//   PWM 출력 비교값 (OCR1A)을 설정하여 지정한 주파수의 음을 재생합니다.
// - 각 음의 지속시간은 해당 박자 값(밀리초 단위) 만큼 유지되며, 음 사이에 짧은 정지(10ms)를 줍니다.
void music_player(int *tone, int *beats)
{
	while(*tone != '\0')
	{
		OCR1A = *tone;		// 현재 음의 주파수를 설정 (OCR1A는 타이머 비교값)
		delay_ms(*beats);	// 지정한 시간 동안 음 재생
		tone++;
		beats++;
		OCR1A = 0;			// 음 출력 종료 (스피커 off)
		_delay_ms(10);		// 음과 음 사이 짧은 휴지
	}
	return;
}

// - PB5 핀을 출력으로 설정하여 스피커에 연결된 PWM 신호를 출력합니다.
// - Timer1을 CTC 모드(출력 비교 일치시 토글)로 설정하고, 프리스케일러를 8로 지정하여
//   원하는 주파수 범위 내에서 PWM 신호를 생성합니다.
void init_buzzer(void)
{
	DDRE |= (1 << 3);				
	TCCR3A = (1 << COM3A0);					
	TCCR3B = (1 << WGM32) | (1 << CS31);	
	TCCR3C = 0;
	OCR3A = 0;								
	
	return;
}

// - 인자로 전달된 횟수만큼 고정 주파수(500) 음을 200ms 재생한 후 200ms 정지하는 단순 비프음을 출력합니다.

void beep(void)
{
	OCR3A = C5;	// 고정 주파수 설정 (출력 PWM 주파수 결정)
	beep_active = 1;
	beep_timer = 0;

}

void mute(void)
{
	OCR3A = 0;
	beep_active = 0;
	beep_timer = 0;
}

// - 사이렌 효과를 위해 반복적으로 주파수를 점진적으로 낮췄다가 다시 높이는 방식으로 음을 재생합니다.
// - OCR1A 값을 조절하여 출력 PWM의 주파수를 변화시킵니다.
void siren(int repeat)
{
	// static 변수: 한 번 초기화하면 함수 호출 간에도 값 유지
	static uint8_t initialized = 0;
	static uint8_t phase = 0;         // 0: 주파수 낮추는 단계 (OCR3A 증가 → 주파수 감소), 1: 주파수 높이는 단계 (OCR3A 감소 → 주파수 증가)
	static uint16_t step = 0;         // 각 단계에서 진행한 스텝 수 (0 ~ 99)
	static uint8_t current_repeat = 0;  // 완료된 반복 횟수
	static uint32_t last_update = 0;  // 마지막 업데이트 시점 (ms 단위, buzzer_timer 값)

	// 초기화: 첫 호출 시 초기값 설정
	if (!initialized) {
		OCR3A = 900;          // 시작 주파수 설정
		last_update = buzzer_timer;
		phase = 0;
		step = 0;
		current_repeat = 0;
		initialized = 1;
	}

	// 모든 반복이 완료되면 비프음 종료
	if (current_repeat >= repeat) {
		OCR3A = 0;            // 비프음 종료 (출력 주파수 0)
		initialized = 0;      // 다음 호출을 위해 초기화 변수 리셋
		return;
	}

	// 20ms 간격으로 주파수 업데이트 (즉, 1ms 인터럽트에서 buzzer_timer가 20씩 증가하는 것을 이용)
	if ((buzzer_timer - last_update) >= 20) {
		last_update = buzzer_timer;  // 타이머 리셋

		if (phase == 0) {
			// 주파수를 낮추는 과정: OCR3A 값을 증가시키면 출력 주파수는 감소함
			OCR3A += 10;
			} else {
			// 주파수를 높이는 과정: OCR3A 값을 감소시키면 출력 주파수는 증가함
			OCR3A -= 10;
		}

		step++;  // 각 단계에서 한 스텝 증가

		// 한 단계(100 스텝, 약 2초 동안) 완료 시
		if (step >= 100) {
			step = 0;  // 스텝 초기화

			if (phase == 0) {
				// 낮추는 과정을 완료했으면 다음엔 주파수를 높이는 단계로 전환
				phase = 1;
				} else {
				// 높이는 과정을 완료하면 한 사이클 종료
				phase = 0;             // 다음 사이클은 낮추는 단계부터 시작
				current_repeat++;      // 반복 횟수 증가
				OCR3A = 900;           // 시작 주파수로 재설정 (원하는 경우)
			}
		}
	}
}


//void siren(int repeat)
//{
	//OCR3A = 900;	// 시작 주파수 설정
	//
	//for(int i=0; i < repeat; i++)
	//{
		//// 주파수를 낮추는 과정: OCR1A 값을 증가시키면 출력 주파수는 감소함
		//for(int j = 0; j < 100; j++)
		//{
			//OCR3A += 10;
			//_delay_ms(20);
		//}
		//// 주파수를 높이는 과정: OCR1A 값을 감소시키면 출력 주파수는 증가함
		//for(int j = 0; j < 100; j++)
		//{
			//OCR3A -= 10;
			//_delay_ms(20);
		//}
	//}
//}

void rrr(void)
{
	for(int i=0; i<20; i++)
	{
		OCR1A = 1136;
		_delay_ms(100);
		OCR1A = 0;
		_delay_ms(20);
	}
}

