// CPU 클록 주파수 정의(16MHz)
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// 초음파 센서의 Trigger 핀 정의
// 보드에 맞게 적절히 포트와 핀 넘버를 매핑해야 함
#define TRIG_L_PIN		0		// 왼쪽
#define TRIG_M_PIN		1		// 중앙
#define TRIG_R_PIN		2		// 오른쪽
#define TRIG_PORT		PORTA
#define TRIG_DDR		DDRA

// 초음파 센서의 Echo 핀 정의
// 보드 설계에 따라 PE4로 입력 받고, 해당 핀은 외부 인터럽트(INT4) 사용
#define ECHO_L_PIN		4
#define ECHO_M_PIN		5
#define ECHO_R_PIN		6
#define ECHO_PIN		PINE
#define ECHO_DDR		DDRE

// 함수 프로토타입
void init_ultrasonic(void);
void trigger_ultrasonic(void);
void distance_ultrasonic(void);

