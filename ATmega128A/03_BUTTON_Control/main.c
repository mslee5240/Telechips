#define F_CPU 16000000UL
#include <avr/io.h>         // AVR 입출력 관련 라이브러리
#include <util/delay.h>     // 딜레이 함수 사용을 위한 라이브러리

#include "led.h"
#include "button.h"

// none O/S 방식 (루프 모니터 방식의 버튼 & LED 제어)
int main(void)
{
	// 포트 설정 (LED 출력)
	DDRA = 0b11111111;	// Data Direction Register
	// PORTA의 모든 핀을 출력(1)으로 설정
	
	// 버튼 상태 변수 초기화
	int button_0_state = 0;     // 버튼 0의 상태 (0: OFF, 1: ON)
	int button_1_state = 0;
	int button_2_state = 0;
	int button_3_state = 0;
	
	// 버튼 초기화 (입력 모드로 설정)
	init_button();
	
	// 버튼 상태 감지 및 LED 제어
	while (1)
	{
		// BUTTON_0: LED 전체 ON/OFF 토글
		// 버튼이 눌리면 'button_0_state'를 반전시켜 LED 전체를 ON/OFF
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			button_0_state = !button_0_state;	// 상태 토글 (0 <-> 1)
			if (button_0_state)
			{
				shift_left_led_on();
			}
			else
			{
				shift_right_led_on();
			}
		}

		if (get_button(BUTTON_1, BUTTON_1_PIN))
		{
			button_1_state = !button_1_state;
			if (button_1_state)
			{
				shift_left_keep_led_on();
			}
			else
			{
				shift_left_keep_led_off();
			}
		}

		if (get_button(BUTTON_2, BUTTON_2_PIN))
		{
			button_2_state = !button_2_state;
			if (button_2_state)
			{
				shift_right_keep_led_on();
			}
			else
			{
				shift_right_keep_led_off();
			}
		}

		if (get_button(BUTTON_3, BUTTON_3_PIN))
		{
			button_3_state = !button_3_state;
			if (button_3_state)
			{
				flower_on();
			}
			else
			{
				flower_off();
			}
		}
	}

	return 0;
}