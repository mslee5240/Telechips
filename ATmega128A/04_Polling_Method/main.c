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
	int button_state[4] = { 0 };
	
	// 버튼 초기화 (입력 모드로 설정)
	init_button();
	
	// Polling Method, Loop Monitoring Method
	while (1)
	{
		if (get_button(BUTTON_0, BUTTON_0_PIN))
		{
			button_state[0]++;
			button_state[0] %=8;
			_delay_ms(100);
		}
		switch (button_state[0]) {
			case 0 :
				led_all_off();
				break;
			case 1:
				led_all_on();
				break;
			case 2:
				shift_left_led_on();
				break;
			case 3:
				shift_right_led_on();
				break;
			case 4:
				shift_left_keep_led_on();
				break;
			case 5:
				shift_right_keep_led_on();
				break;
			case 6:
				flower_on();
				break;
			case 7:
				flower_off();
				break;
		}
	}

	return 0;
}

