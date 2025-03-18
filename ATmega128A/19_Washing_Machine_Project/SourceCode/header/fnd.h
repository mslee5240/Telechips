#include <avr/io.h>

// 7-세그먼트 디스플레이 세그먼트 데이터 포트 및 데이터 방향 레지스터
#define FND_DATA_PORT       PORTC
#define FND_DATA_DDR        DDRC

// 7-세그먼트 디스플레이 자리(디지털) 제어 포트 및 데이터 방향 레지스터
#define FND_DIGIT_PORT      PORTA
#define FND_DIGIT_DDR       DDRA

// 4자리 디스플레이의 각 자리 제어 핀 (PORTB의 핀 번호)
// 오른쪽 디스플레이
#define FND_R_DIGIT_D1		4
#define FND_R_DIGIT_D2		5
#define FND_R_DIGIT_D3		6
#define FND_R_DIGIT_D4		7

// 왼쪽 디스플레이
#define FND_L_DIGIT_D1		0
#define FND_L_DIGIT_D2		1
#define FND_L_DIGIT_D3		2
#define FND_L_DIGIT_D4		3

// 함수 프로토타입: 디스플레이 초기화 및 업데이트 함수
void init_fnd(void);
void fnd_display_0(uint32_t* seconds, uint32_t* half_seconds);

