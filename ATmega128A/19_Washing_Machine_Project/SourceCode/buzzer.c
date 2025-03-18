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
	DDRB |= (1 << 5);						// PB5를 출력으로 설정
	TCCR1A = (1 << COM1A0);					// OC1A 핀 토글 모드 설정
	TCCR1B = (1 << WGM12) | (1 << CS11);	// CTC 모드, 프리스케일러 8 설정
	TCCR1C = 0;
	OCR1A = 0;								// 초기 출력 비교값 0 (음 없음)
	
	return;
}

// - 인자로 전달된 횟수만큼 고정 주파수(500) 음을 200ms 재생한 후 200ms 정지하는 단순 비프음을 출력합니다.
void beep(void)
{
	OCR1A = C5;	// 고정 주파수 설정 (출력 PWM 주파수 결정)
	beep_active = 1;
	beep_timer = 0;
}

void mute(void)
{
	OCR1A = 0;
	beep_active = 0;
	beep_timer = 0;
}

// - 사이렌 효과를 위해 반복적으로 주파수를 점진적으로 낮췄다가 다시 높이는 방식으로 음을 재생합니다.
// - OCR1A 값을 조절하여 출력 PWM의 주파수를 변화시킵니다.
void siren(int repeat)
{
	OCR1A = 900;	// 시작 주파수 설정
	
	for(int i=0; i < repeat; i++)
	{
		// 주파수를 낮추는 과정: OCR1A 값을 증가시키면 출력 주파수는 감소함
		for(int j = 0; j < 100; j++)
		{
			OCR1A += 10;
			_delay_ms(20);
		}
		// 주파수를 높이는 과정: OCR1A 값을 감소시키면 출력 주파수는 증가함
		for(int j = 0; j < 100; j++)
		{
			OCR1A -= 10;
			_delay_ms(20);
		}
	}
}

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

void delay_ms(int ms)
{
	while(ms-- != 0)_delay_ms(1);
}