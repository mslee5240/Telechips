#include "fnd.h"

void init_fnd(void)
{
	FND_DATA_DDR = 0xFF;    // 출력 모드로 설정
	FND_DIGIT_DDR |= (1 << FND_DIGIT_D1) | (1 << FND_DIGIT_D2) | (1 << FND_DIGIT_D3) | (1 << FND_DIGIT_D4); // 더 좋은 코딩 방법
	//  FND_DIGIT_DDR |= 0xF0;  // 자릿수 선택 7654

	// fnd를 all off
	FND_DATA_PORT = ~0x00;  // fnd를 all off: 0xFF;
}

void fnd_display_1(uint32_t* ms_count, uint32_t* sec_count)
{
	uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0x7F };

	static int digit_select = 0;    // static을 쓰면 전역 변수처럼 사용 가능

	switch (digit_select)
	{
		case 0:
		FND_DIGIT_PORT = 0x80;    // 10000000
		FND_DATA_PORT = fnd_font[*sec_count % 10];   	// 0~9초
		break;

		case 1:
		FND_DIGIT_PORT = 0x40;    // 01000000
		FND_DATA_PORT = fnd_font[*sec_count / 10 % 6];   // 10단위 초
		break;

		case 2:
		FND_DIGIT_PORT = 0x20;    // 00100000
		FND_DATA_PORT = fnd_font[*sec_count / 60 % 10];   // 1단위 분

		// 부가 기능 구현: 1초마다 점 찍기.
		_delay_ms(1);
		if (* sec_count % 2) {
			FND_DATA_PORT = fnd_font[10];
		}
		break;

		case 3:
		FND_DIGIT_PORT = 0x10;    // 00010000
		FND_DATA_PORT = fnd_font[*sec_count / 600 % 6];   // 10단위 분
		break;
	}

	digit_select++;
	digit_select %= 4;  // 다음 표시할 자릿수 선택
}

void fnd_display_2(uint32_t* ms_count, uint32_t* sec_count)
{
	
	uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0x7F };
	uint8_t fnd_2_font[] = { 0xfb, 0xf9, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf4, 0xf0 };
	uint8_t fnd_3_font[] = { 0xff, 0xff, 0xff, 0xfe, 0xde, 0xce, 0xc6, 0xc6, 0xff, 0xf7, 0xe7, 0xc7, 0xc6, 0xc6, 0xc6, 0xc6 };

	static int digit_select = 0;

	switch (digit_select)
	{
		case 0:
		FND_DIGIT_PORT = 0x80;
		FND_DATA_PORT = fnd_font[*sec_count % 10];
		break;
		
		case 1:
		FND_DIGIT_PORT = 0x40;
		FND_DATA_PORT = fnd_font[*sec_count / 10 % 6];
		break;
		
		case 2:
		FND_DIGIT_PORT = 0x20;
		FND_DATA_PORT = fnd_2_font[*sec_count % 16];
		break;
		
		case 3:
		FND_DIGIT_PORT = 0x10;
		FND_DATA_PORT = fnd_3_font[*sec_count % 16];
		break;
		
	}

	digit_select++;
	digit_select %= 4;
}

extern volatile int ultrasonic_dis;

void fnd_display_distance(void)
{
	int distance_cm = ultrasonic_dis / 58;
	uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0x7F };

	static int digit_select = 0;    // static을 쓰면 전역 변수처럼 사용 가능

	switch (digit_select)
	{
		case 0:
		FND_DIGIT_PORT = 0x80;    // 10000000
		FND_DATA_PORT = fnd_font[distance_cm % 10];  
		break;

		case 1:
		FND_DIGIT_PORT = 0x40;    // 01000000
		FND_DATA_PORT = fnd_font[distance_cm / 10 % 10];
		break;

		case 2:
		FND_DIGIT_PORT = 0x20;    // 00100000
		FND_DATA_PORT = fnd_font[distance_cm / 100 % 10]; 
		break;

		case 3:
		FND_DIGIT_PORT = 0x10;    // 00010000
		FND_DATA_PORT = fnd_font[distance_cm / 1000 % 10]; 
		break;
	}

	digit_select++;
	digit_select %= 4;  // 다음 표시할 자릿수 선택
}