// CPU 클록 주파수 정의(16MHz)
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// 초음파 센서의 Trigger 핀 정의
// 보드에 맞게 적절히 포트와 핀 넘버를 매핑해야 함
#define TRIG        4
#define TRIG_PORT   PORTG
#define TRIG_DDR    DDRG

// 초음파 센서의 Echo 핀 정의
// 보드 설계에 따라 PE4로 입력 받고, 해당 핀은 외부 인터럽트(INT4) 사용
#define ECHO        4
#define ECHO_PIN    PINE
#define ECHO_DDR    DDRE

// 함수 프로토타입
void init_ultrasonic(void);
void trigger_ultrasonic(void);
void distance_ultrasonic(void);

