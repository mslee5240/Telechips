#define F_CPU 16000000UL
#include <avr/io.h>         // AVR 입출력 관련 라이브러리
#include <util/delay.h>     // 딜레이 함수 사용을 위한 라이브러리

#include "led.h"
#include "button.h"
#include "fnd.h"


int main(void)
{
	init_button();
	int button_state[4] = { 0 };
	
	init_fnd();
	uint32_t ms_count = 0;
	uint32_t sec_count = 0;
	uint32_t * f_ms = &ms_count;
	uint32_t* f_sec = &sec_count;
	
	void (*fp_0[])(uint32_t* ms_count, uint32_t* sec_count) =
	{
		fnd_display_1,
		fnd_display_2
	};
	
	while (1)
	{
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			button_state[0]++;
			button_state[0] %= 2;
		}
		fp_0[button_state[0]] (f_ms, f_sec);
		_delay_ms(1);
		ms_count++;
		if (ms_count >= 999)   // 1000ms = 1sec
		{
			ms_count = 0;
			sec_count++;
		}

		if (get_button(BUTTON_1, BUTTON_1_PIN))
		{
			ms_count = 0;
			sec_count = 0;
			init_fnd();
		}
	}

	return 0;
}
