#include "ultrasonic.h"

extern volatile int ultrasonic_check_timer;

volatile int ultrasonic_dis = 0;
volatile char scm[50];

// p.278 (표12-3)
// PE4 : 외부 INT4; 초음파 센서의 상승, 하강 에지 둘 다 INT가 ISR(INT4_vect)로 들어온다.
// 결국 2번(상승일 때 1번, 하강일 때 1번)들어온다.
ISR(INT4_vect)
{
	// 1. 상승 에지
	if (ECHO_PIN & 1 << ECHO)
	{
		TCNT1 = 0;		// Timer1 H/W counter를 clear
	}
	else // 2. 하강 에지
	{
		// ECHO핀에 들어온 펄스 개수를 us로 환산
		ultrasonic_dis = 1000000.0 * TCNT1 * 1024 / F_CPU;
		// 예) TCINT에 10이 들어 있다고 가정하자.
		// 15.625KHz의 1주기 64us이다
		// 0.000064sec(64us) * 10 ==> 0.00064sec(640us)
		// 640us / 58us(1cm 이동하는데 소요 시간) ==> 11cm이다.
		// --- 1cm : 58us
		sprintf(scm, "dis : %dcm\n", ultrasonic_dis / 58);	// cm 환산
	}
}

void init_ultrasonic(void)
{
	TRIG_DDR |= 1 << TRIG;
	ECHO_DDR &= ~(1 << TRIG);	// input mode; ECHO_DDR &= 0b11110111;
	// p.289 (표12-6)
	// 0 1 : 상승 에지(Rising Edge)와 하강 에지(Falling Edge) 둘 다 INT를 띄우도록 요청
	EICRB |= 0 << ISC41 | 1 << ISC40;
	// 16bit Timer1을 설정해서 사용; max: 65535 = (0xffff)
	// 16Mhz를 1024로 분주; 16000000Hz/1024 = 15625Hz(= 15.625KHz)
	// 1주기 : T(주기) = 1/f;  1/15625 = 0.000064sec(= 64us)
	// p.318
	TCCR1B |= 1 << CS12 | 1 << CS10;	// 1024로 분주
	// p.287
	EIMSK |= 1 << INT4;		// EXTERNAL INT 4 (ECHO핀)
}

void trigger_ultrasonic(void)
{
	TRIG_PORT &= ~(1 << TRIG);	// Low
	_delay_us(1);
	TRIG_PORT |= 1 << TRIG;		// High
	_delay_us(15);				// 규격(10us), 여유를 둬서 15us
	TRIG_PORT &= ~(1 << TRIG);	// Low
}

void distance_ultrasonic(void)
{
	if (ultrasonic_check_timer >= 1000)		// 1초
	{
		ultrasonic_check_timer = 0;
		printf("%s", scm);
		trigger_ultrasonic();
	}
}
