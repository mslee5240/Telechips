#include "fnd.h"

void init_fnd(void);
int fnd_main(void);
void fnd_display(void);

uint32_t ms_count = 0;      // ms를 세는 count 변수, unsigned int == uint32_t
uint32_t sec_count = 0;     // s를 세는 count 변수

int fnd_main(void)
{
	init_fnd();

	while (1)
	{
		fnd_display();
		_delay_ms(1);
		ms_count++;
		if (ms_count >= 999)   // 1000ms = 1sec
		{
			ms_count = 0;
			sec_count++;
		}
	}
	return 0;
}

void init_fnd(void)
{
	FND_DATA_DDR = 0xFF;    // 출력 모드로 설정
	FND_DIGIT_DDR |= (1 << FND_DIGIT_D1) | (1 << FND_DIGIT_D2) | (1 << FND_DIGIT_D3) | (1 << FND_DIGIT_D4); // 더 좋은 코딩 방법
	//  FND_DIGIT_DDR |= 0xF0;  // 자릿수 선택 7654

	// fnd를 all off
#if 1   // common Anode
	FND_DATA_PORT = ~0x00;  // fnd를 all off: 0xFF;
#else   // common Cathode
	FND_DATA_PORT = 0x00;  // fnd를 all off: 0x00;
#endif
}

void fnd_display(void)
{
#if 1   // common Anode
	uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                            0x92, 0x82, 0xD8, 0x80, 0x98,
                            0x7F
	                    };
#else   // common Cathode
	uint8_t fnd_font[] = { ~0xC0, ~0xF9, ~0xA4, ~0xB0, ~0x99,
                            ~0x92, ~0x82, ~0xD8, ~0x80, ~0x98,
                            ~0x7F
	                    };
#endif

	static int digit_select = 0;    // static을 쓰면 전역 변수처럼 사용 가능

	switch (digit_select)
	{
#if 1   // common Anode
		case 0:
            FND_DIGIT_PORT = 0x80;    // 10000000
            FND_DATA_PORT = fnd_font[sec_count % 10];   // 0~9초
            break;
		case 1:
            FND_DIGIT_PORT = 0x40;    // 01000000
            FND_DATA_PORT = fnd_font[sec_count / 10 % 6];   // 10단위 초
            break;
		case 2:
            FND_DIGIT_PORT = 0x20;    // 00100000
            FND_DATA_PORT = fnd_font[sec_count / 60 % 10];   // 1단위 분
            // 부가 기능 구현: 1초마다 점 찍기.
            _delay_ms(1);
			if (* sec_count % 2) {
				FND_DATA_PORT = fnd_font[10];
			}
            break;
		case 3:
            FND_DIGIT_PORT = 0x10;    // 00010000
            FND_DATA_PORT = fnd_font[sec_count / 600 % 6];   // 10단위 분
            break;
#else   // common Cathode
		case 0:
		    FND_DIGIT_PORT &= ~(1 << FND_DIGIT_D4);    // 01111111
		    break;
		case 1:
		    FND_DIGIT_PORT &= ~(1 << FND_DIGIT_D3);    // 10111111
		    break;
		case 2:
		    FND_DIGIT_PORT &= ~(1 << FND_DIGIT_D2);    // 11011111
		    break;
		case 3:
		    FND_DIGIT_PORT &= ~(1 << FND_DIGIT_D1);    // 11101111
		    break;
#endif
	}

	digit_select++;
	digit_select %= 4;  // 다음 표시할 자릿수 선택
}