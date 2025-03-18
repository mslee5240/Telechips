#include "button.h"
#include "buzzer.h"

// # 버튼 초기화(방향 설정: 입력 0)
// DDRD : 76543210 (D의 pin)
//        -1010--- (초기값)
//      & 10000111 (마스킹)
// DDRD &= 0x87		// 3 4 5 6을 input으로 설정한다. <- 가독성 떨어짐(해석이 어려움)
//													<- port 변경시 프로그램 수정이 어려움

// @brief 버튼 입력 핀을 설정 (모두 입력 모드로 설정)
void init_button(void)
{
	BUTTON_DDR &= ~(
		1 << BUTTON_0_PIN
	  | 1 << BUTTON_1_PIN 
	  | 1 << BUTTON_2_PIN 
	  | 1 << BUTTON_3_PIN
	);
	// 해당 핀을 입력 모드로 설정 (0: 입력, 1: 출력)
}
// DDRD의 4, 5, 6, 7번 핀을 입력 모드(0)로 설정


// @brief 버튼 상태를 읽고, 버튼이 눌렸다가 떼어졌는지 확인하는 함수
// @param button_num 논리적 버튼 번호 (0~3)
// @param button_pin 물리적 버튼 핀 번호 (PORTD.4 ~ PORTD.7)
// @return 1 버튼이 눌렸다가 떼어진 경우 (완전한 버튼 입력)
// @return 0 버튼이 아직 눌려있거나, 변화가 없는 경우
int get_button(int button_num, int button_pin)
{
	// 버튼의 이전 상태를 저장 (static을 사용하여 함수 호출 간 값 유지)
	static unsigned char button_status[] =
	{ BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE, BUTTON_RELEASE };
	
	int current_state = BUTTON_PIN & (1 << button_pin); // 버튼 상태 읽기
	
	// 버튼이 눌린 경우 (기존 상태는 RELEASE)
	if (current_state && button_status[button_num] == BUTTON_RELEASE) // 버튼이 처음 눌려진 noise high 상태
	{
		btn_debounce_active = 1;
		if (debounce_timer > 30) {
			debounce_timer = 0;
			btn_debounce_active = 0;
			
			button_status[button_num] = BUTTON_PRESS;	// 버튼이 눌린 상태 저장; noise가 지나간 상태의 High 상태
			
			return 0;	// 아직 완전히 눌렸다 떼어진 상태가 아님
		}
	}
	
	// 버튼이 떼어진 경우 (기존 상태는 PRESS)
	else if (current_state == BUTTON_RELEASE && button_status[button_num] == BUTTON_PRESS)
	{
		btn_debounce_active = 1;
		if (debounce_timer > 30) {
			debounce_timer = 0;
			btn_debounce_active = 0;
			
			beep();		// 비프음 출력
			
			button_status[button_num] = BUTTON_RELEASE;	// 버튼 상태 초기화
			
			return 1;	// 버튼이 눌렸다가 떼어진 상태 (완전한 입력)
		}
	}
	
	return 0;	// 버튼이 눌리지 않음 (idle 상태)
}
