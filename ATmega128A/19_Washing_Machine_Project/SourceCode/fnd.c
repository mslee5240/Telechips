#include "fnd.h"

// 포인터 배열에서 접근하기 위한 변수
extern volatile uint8_t timer_active;	// timer가 비활성화 되면 "StOP"을 출력하기 위함
extern volatile uint8_t motor_forward;	// 회전 방향에 맞게 출력하기 위함

extern int timeORselect;
extern int circleORselect;
extern int washORrinseORdry;
extern int select_time[];
extern int button_state[4];
extern int select_time_0;
extern int select_time_1;
extern int select_time_2;

// Decimal 폰트 배열 정의:
uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0x7F };
	
// 각 세그먼트 정방향 Circle 폰트
uint8_t fnd_font_forward_circle_0[] = { 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf4, 0xf0, 0x0C };
uint8_t fnd_font_forward_circle_1[] = { 0xff, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf6, 0xf6, 0xf6, 0xC0 };
uint8_t fnd_font_forward_circle_2[] = { 0xff, 0xff, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0x07 };
uint8_t fnd_font_forward_circle_3[] = { 0xff, 0xff, 0xff, 0xf7, 0xe7, 0xc7, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x92 };

// 각 세그먼트 역방향 Circle 폰트
uint8_t fnd_font_reverse_circle_0[] = { 0xfb, 0xf9, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0x0C };
uint8_t fnd_font_reverse_circle_1[] = { 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf6, 0xf6, 0xC0 };
uint8_t fnd_font_reverse_circle_2[] = { 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf6, 0xf6, 0xf6, 0x07 };
uint8_t fnd_font_reverse_circle_3[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xde, 0xce, 0xc6, 0xc6, 0xc6, 0xc6, 0x92 };

// 정방향 Circle 폰트 포인터 배열
uint8_t * fnd_font_forward_circle[] = {	fnd_font_forward_circle_0, fnd_font_forward_circle_1, fnd_font_forward_circle_2, fnd_font_forward_circle_3 };

// 역방향 Circle 폰트 포인터 배열
uint8_t * fnd_font_reverse_circle[] = { fnd_font_reverse_circle_0, fnd_font_reverse_circle_1, fnd_font_reverse_circle_2, fnd_font_reverse_circle_3 };

// Circle 폰트 포인터 배열 - 이중 포인터 배열로 통합
uint8_t ** fnd_font_circle[] = { fnd_font_forward_circle, fnd_font_reverse_circle };

uint8_t fnd_font_wash[] = { 0x95, 0x88, 0x92, 0x89 };
uint8_t fnd_font_rins[] = { 0xAF, 0xF9, 0xAB, 0x92 };
uint8_t fnd_font_dry[] = { 0xA1, 0xAF, 0x91, 0xFF };
uint8_t * fnd_font_mode[] = { fnd_font_wash, fnd_font_rins, fnd_font_dry };


void init_fnd(void)
{
	// PORTC의 모든 핀을 출력으로 설정
    FND_DATA_DDR = 0xFF; 
	 
	// 오른쪽 FND 디스플레이
    FND_DIGIT_DDR |= (1 << FND_R_DIGIT_D1) | (1 << FND_R_DIGIT_D2) | (1 << FND_R_DIGIT_D3) | (1 << FND_R_DIGIT_D4);
	
	// 왼쪽 FND 디스플레이
	FND_DIGIT_DDR |= (1 << FND_L_DIGIT_D1) | (1 << FND_L_DIGIT_D2) | (1 << FND_L_DIGIT_D3) | (1 << FND_L_DIGIT_D4);
	
    FND_DATA_PORT = ~0x00;  // 모든 세그먼트 OFF (active-low 가정)
}

void fnd_display_0(uint32_t* seconds, uint32_t* half_seconds)
{
    static int digit_select = 0;		// 현재 활성화된 자리를 기억 (0~3)
	volatile uint32_t idx = *half_seconds;	// 왼쪽 FND 출력 font index
	
	if (timer_active == 0) {
		idx = 12;	// Timer와 Motor가 정지하면 "StOP" 출력을 위한 index
	}
	else {
		idx %= 12;
	}
    
    switch (digit_select)
    {
		// 오른쪽 FND 출력
        case 0:
            FND_DIGIT_PORT = 0x80;  // 첫 번째 자리 활성화 (10000000)
			if (timeORselect) {
				FND_DATA_PORT = fnd_font[*seconds % 10];  // 초의 일의 자리 (0~9)
			}
			else {
				FND_DATA_PORT = fnd_font[select_time[button_state[washORrinseORdry]] % 10];  // 초의 일의 자리 (0~9)
			}
            
            break;
            
        case 1:
            FND_DIGIT_PORT = 0x40;  // 두 번째 자리 활성화 (01000000)
			if (timeORselect) {
				FND_DATA_PORT = fnd_font[(*seconds / 10) % 6];  // 초의 십의 자리 (0~5)
			}
			else {
				FND_DATA_PORT = fnd_font[(select_time[button_state[washORrinseORdry]] / 10) % 6];  // 초의 십의 자리 (0~5)
			}
			
            break;
            
        case 2:
            FND_DIGIT_PORT = 0x20;  // 세 번째 자리 활성화 (00100000)
			if (timeORselect) {
				FND_DATA_PORT = fnd_font[(*seconds / 60) % 10];  // 분의 일의 자리 (0~9)
			}
			else {
				FND_DATA_PORT = fnd_font[(select_time[button_state[washORrinseORdry]] / 60) % 10];  // 분의 일의 자리 (0~9)
			}
            
            break;
            
        case 3:
            FND_DIGIT_PORT = 0x10;  // 네 번째 자리 활성화 (00010000)
			if (timeORselect) {
				FND_DATA_PORT = fnd_font[(*seconds / 600) % 6];  // 분의 십의 자리 (0~5)
			}
			else {
				FND_DATA_PORT = fnd_font[(select_time[button_state[washORrinseORdry]] / 600) % 6];  // 분의 십의 자리 (0~5)
			}
            
            break;
		
		// 왼쪽 FND 출력
		case 4:
			FND_DIGIT_PORT = 0x08;  // 첫 번째 자리
			if (circleORselect) {
				FND_DATA_PORT = fnd_font_circle[motor_forward][0][idx];
			}
			else {
				FND_DATA_PORT = fnd_font_mode[washORrinseORdry][3];
			}
			break;
		
		case 5:
			FND_DIGIT_PORT = 0x04;  // 두 번째 자리
			if (circleORselect) {
				FND_DATA_PORT = fnd_font_circle[motor_forward][1][idx];
			}
			else {
				FND_DATA_PORT = fnd_font_mode[washORrinseORdry][2];
			}
			break;
		
		case 6:
			FND_DIGIT_PORT = 0x02;  // 세 번째 자리
			if (circleORselect) {
				FND_DATA_PORT = fnd_font_circle[motor_forward][2][idx];
			}
			else {
				FND_DATA_PORT = fnd_font_mode[washORrinseORdry][1];
			}
			break;
		
		case 7:
			FND_DIGIT_PORT = 0x01;  // 네 번째 자리
			if (circleORselect) {
				FND_DATA_PORT = fnd_font_circle[motor_forward][3][idx];
			}
			else {
				FND_DATA_PORT = fnd_font_mode[washORrinseORdry][0];
			}
			break;	
    }
    
    // 다음 자리로 이동 (순환 방식)
    digit_select = (digit_select + 1) % 8;
	
}