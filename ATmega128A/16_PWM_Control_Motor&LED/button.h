#define F_CPU 16000000UL        // 마이크로컨트롤러 동작 클럭 설정 (16MHz)
#include <avr/io.h>
#include <util/delay.h>

// LED 관련 설정
// 이렇게 하는 이유: LED PORT가 변경되면, #define만 바꿔줘도 컴파일러가 변경해주기 때문

// 버튼 관련 설정
#define BUTTON_DDR		DDRD    // 버튼 데이터 방향 레지스터
#define BUTTON_PIN		PIND	// 버튼 입력 핀 (PIND를 통해 PORTD의 핀 상태를 읽음)
								// PIND는 PORTD를 읽는 register / 5v = 1, 0v = 0
// 버튼 핀 정의 (PORTD의 특정 핀에 연결)
#define BUTTON_0_PIN	4	    // PORTD.4
#define BUTTON_1_PIN	5	    // PORTD.5
#define BUTTON_2_PIN	6	    // PORTD.6
#define BUTTON_3_PIN	7	    // PORTD.7

// 버튼 번호 정의 (논리적 버튼 인덱스)
#define BUTTON_0		0	// PORTD의 가상의 index(S/W 번호)
#define BUTTON_1		1
#define BUTTON_2		2
#define BUTTON_3		3

// 버튼 개수 정의
#define BUTTON_NUMBER	4

// 버튼 상태 정의
#define BUTTON_PRESS	1	// 버튼이 눌린 상태 (Active-High)
#define BUTTON_RELEASE	0	// 버튼이 떼어진 상태 (Active-Low)

// 함수 프로토타입 선언
void init_button(void);
int get_button(int button_num, int button_pin);
