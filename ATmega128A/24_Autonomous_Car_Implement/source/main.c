#include "main.h"

volatile uint32_t seconds = 0;						// 초 단위 카운터 (milliseconds에서 1초마다 증가)
volatile uint32_t half_seconds = 0;					// 0.5초 단위 카운터 (milliseconds_1에서 0.5초마다 증가)
volatile uint32_t* f_sec = &seconds;
volatile uint32_t* f_hsec = &half_seconds;


// stdout에 UART0_transmit을 연결하여 printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int func_idx = MANUAL_MODE;
void (*pfunc[]) (void) =
{
	manual_mode,		// 수동 mode
	distance_check,		// 초음파 거리 측정
	auto_mode_check,	// btn check
	auto_mode			// 자율 주행 
};

int main(void)
{
	// 모든 주변장치 초기화 및 전역 인터럽트 허용
	init_all();

	while (1)
	{
		//seconds_count();		// 1초 Count
		//half_seconds_count();	// 0.5초 Count
		//displayUpdate();		// 7-Segment Display 갱신
		//lcdDisplayUpdate();
		//siren(2);
		distance_check();
		auto_drive_mode();
		
		//pfunc[func_idx]();
		//distance_print();		// 디버깅 용 출력 함수
		
	}
	
	return 0;
}

// 모든 주변장치 초기화
void init_all(void)
{
	init_timer0();		// Timer0 초기화 : milliseconds 카운터
	init_timer1();		// Timer1 초기화 : DC 모터 PWM 제어
	//init_uart0();		// Uart0 초기화 : COM포트 연결
	//init_uart1();		// Uart1 초기화 : Bluetooth 연결
	//init_buzzer();		// Buzzer 초기화 : Timer1을 CTC 모드(출력 비교 일치시 토글)로 설정
	//init_led();			// LED 초기화 
	//init_button();		// BTN 초기화
	//init_fnd();			// 7-Segment 초기화
	//init_I2C_LCD();		// I2C_LCD 초기화
	init_L298N();		// L298N 모터 드라이버 초기화
	init_ultrasonic();	// 초음파 센서 초기화 : Timer2 설정: Normal 모드(기본값) 설정
	
	sei();	// 전역 인터럽트 허용
	
	stdout = &OUTPUT;	// 표준 출력(stdout)을 UART0의 OUTPUT 스트림에 연결
}

// 자동차 기능 구현
void manual_mode(void)		// 수동 mode
{
	switch (bt_data)
	{
		case 'W':
		case 'w':
			forward(1023);
			break;
			
		case 'S':	
		case 's':
			backward(1023);
			break;
			
		case 'A':
		case 'a':
			turn_left(1023);
		break;
		
		case 'D':
		case 'd':
			turn_right(1023);
			break;
			
		case 'M':
		case 'm':
			stop();
			break;
			
		default:
			break;
	}
	func_idx = DISTANCE_CHECK;
}

void auto_mode(void)			// 자율 주행
{
	func_idx = MANUAL_MODE;
}


// 기본 기능 구현
void seconds_count(void)
{
	// 1초 Count
	if (milliseconds > 999) {
		milliseconds = 0;
		seconds++;
	}
}

void half_seconds_count(void)
{
	// 0.5초 Count
	if (fnd_circle_timer > 499) {
		fnd_circle_timer = 0;
		half_seconds++;
	}
}

void displayUpdate(void) {
	// 7-Segment Display 갱신
	if (displayUpdateCounter > 1) {
		displayUpdateCounter = 0;
		
		// 출력 함수 호출
		fnd_display_0(f_sec, f_hsec);
	}
}

void lcdDisplayUpdate(void) {
	// 7-Segment Display 갱신
	if (lcd_displayUpdateCounter > 100) {
		lcd_displayUpdateCounter = 0;
		
		// 출력 함수 호출
		I2C_LCD_write_string_XY(0,0,"Hello !!!");
		I2C_LCD_write_string_XY(1,0,"MSLEE");
	}
}
