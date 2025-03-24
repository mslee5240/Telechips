#include "timer0.h"

void init_timer0(void)
{
	// 초기 카운터값 설정
	TCNT0 = 6;
	
	// 분주비 256 : CS02 = 1, CS01 = 0, CS00 = 0
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	
	// Timer0 오버플로우 인터럽트 허용
	TIMSK |= (1 << TOIE0);
}

