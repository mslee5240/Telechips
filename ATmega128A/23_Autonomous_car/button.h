#include <avr/io.h>
#include "isr.h"
#include "def.h"
#include "led.h"
#include "buzzer.h"
#include "pwm.h"


// 버튼 관련 설정
#define BUTTON_DDR		DDRG    // 버튼 데이터 방향 레지스터
#define BUTTON_PIN		PING	// 버튼 입력 핀 (PING를 통해 PORTG의 핀 상태를 읽음)
								// PIND는 PORTD를 읽는 register / 5v = 1, 0v = 0
// 버튼 핀 정의 (PORTD의 특정 핀에 연결)
#define BUTTON_0_PIN	3	    // PORTG.3


// 버튼 번호 정의 (논리적 버튼 인덱스)
#define BUTTON_0		0	// PORTD의 가상의 index(S/W 번호)
				
// 버튼 개수 정의
#define BUTTON_NUMBER	1

// 버튼 상태 정의
#define BUTTON_PRESS	1	// 버튼이 눌린 상태 (Active-High)
#define BUTTON_RELEASE	0	// 버튼이 떼어진 상태 (Active-Low)

// 함수 프로토타입 선언
void init_button(void);
int get_button(int button_num, int button_pin);

void auto_mode_check(void);

