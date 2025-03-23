#include "ultrasonic.h"

// Timer0과 ISR(TIMER0_OVF_vect)에서 사용하는 변수
extern volatile uint16_t ultrasonic_check_timer;
extern volatile uint16_t ultrasonic_print_timer;

// 함수 포인터 배열 인덱스 접근하기 위한 변수
extern int func_idx;

// 거리 저장 배열
volatile uint32_t ultrasonic_dis[3] = { 0 } ;

// ISR에서 사용할 버퍼
volatile uint32_t start_tcnt[3] = { 0 };
volatile uint32_t start_ovf[3] = { 0 };
	
// Timer2 오버플로우 횟수
volatile uint32_t timer2_ovf = 0;     

// 순차적으로 트리거 되는 순서를 결정하기 위한 함수 포인터 배열
void (*fp[])(void) = { trigger_left, trigger_mid, trigger_right };

// Timer2 오버플로우 인터럽트: Timer2가 255에서 0으로 넘어갈 때마다 호출됨
ISR(TIMER2_OVF_vect) {
	timer2_ovf++;
}

// 외부 인터럽트(INT) ISR: 에코 신호의 상승/하강 에지에서 호출됨
ISR(INT4_vect) {
	// ECHO 핀 상태에 따라 상승/하강 에지 구분
	if (ECHO_PIN & (1 << ECHO_LEFT)) {	// 상승 에지: 에코 시작
		start_tcnt[LEFT] = TCNT2;
		start_ovf[LEFT] = timer2_ovf;
	} else {	// 하강 에지: 에코 종료
		// 전체 카운트: (오버플로우 횟수 * 256) + 현재 TCNT2 값
		uint32_t ovf = timer2_ovf - start_ovf[LEFT];
		uint32_t temp_tcnt = TCNT2 - start_tcnt[LEFT];
		uint32_t total_ticks = (ovf << 8) + temp_tcnt;
		
		//ultrasonic_dis = (total_ticks * 128UL) / 16;
		ultrasonic_dis[LEFT] = total_ticks * 8;
	}
}

// 위 주석과 같은 내용이므로 주석 생략
ISR(INT5_vect) {
	if (ECHO_PIN & (1 << ECHO_MID)) { 
		start_tcnt[MID] = TCNT2;
		start_ovf[MID] = timer2_ovf;
	} else {
		uint32_t ovf = timer2_ovf - start_ovf[MID];
		uint32_t temp_tcnt = TCNT2 - start_tcnt[MID];
		uint32_t total_ticks = (ovf << 8) + temp_tcnt;

		ultrasonic_dis[MID] = total_ticks * 8;
	}
}

ISR(INT6_vect) {
	if (ECHO_PIN & (1 << ECHO_RIGHT)) {
		start_tcnt[RIGHT] = TCNT2;
		start_ovf[RIGHT] = timer2_ovf;
	} else {
		uint32_t ovf = timer2_ovf - start_ovf[RIGHT];
		uint32_t temp_tcnt = TCNT2 - start_tcnt[RIGHT];
		uint32_t total_ticks = (ovf << 8) + temp_tcnt;
		
		ultrasonic_dis[RIGHT] = total_ticks * 8;
	}
}

void init_ultrasonic(void) {
	TRIG_DDR |= 1 << TRIG_LEFT | 1 << TRIG_MID | 1 << TRIG_RIGHT;		// 트리거 핀 출력 설정
	ECHO_DDR &= ~(1 << ECHO_LEFT | 1 << ECHO_MID | 1 << ECHO_RIGHT);	// 에코 핀 입력 설정
	
	// 외부 인터럽트 설정: INT를 "논리 변화" 감지로 설정
	EICRB &= ~((1 << ISC41) | (1 << ISC40) | (1 << ISC51) | (1 << ISC50) | (1 << ISC61) | (1 << ISC60)); // 초기화
	EICRB |= (0 << ISC41) | (1 << ISC40) | (0 << ISC51) | (1 << ISC50) | (0 << ISC61) | (1 << ISC60);	 // 설정
	
	// Timer2 설정: Normal 모드(기본값) 및 128 분주로 동작하도록 설정
	TCCR2 = (1 << CS22) | (0 << CS21) | (1 << CS20);
	
	// Timer2 오버플로우 인터럽트 활성화
	TIMSK |= (1 << TOIE2);
	
	// 외부 인터럽트 활성화
	EIMSK |= 1 << INT4 | 1 << INT5 | 1 << INT6;
}

// 방법_1: 순차적으로 신호 보내기
void trigger_left(void) {	// 왼쪽 센서
	TRIG_PORT &= ~(1 << TRIG_LEFT);
	_delay_us(1);
	TRIG_PORT |= (1 << TRIG_LEFT);
	_delay_us(13); //  (규격: 10µs 펄스)
	TRIG_PORT &= ~(1 << TRIG_LEFT);
}

void trigger_mid(void) {	// 중앙 센서
	TRIG_PORT &= ~(1 << TRIG_MID);
	_delay_us(1);
	TRIG_PORT |= (1 << TRIG_MID);
	_delay_us(13);
	TRIG_PORT &= ~(1 << TRIG_MID);
}

void trigger_right(void) {	// 오른쪽 센서
	TRIG_PORT &= ~(1 << TRIG_RIGHT);
	_delay_us(1);
	TRIG_PORT |= (1 << TRIG_RIGHT);
	_delay_us(13);
	TRIG_PORT &= ~(1 << TRIG_RIGHT);
}

// 거리 측정을 위한 트리거 함수 호출
void distance_check(void) {
	static int idx = 0;
	
	if (ultrasonic_check_timer > 60) { // 60ms마다 측정
		ultrasonic_check_timer = 0;
		
		// 순차적 측정을 위한 트리거 함수 호출
		fp[idx++]();
		idx %= 3;
		
		func_idx = MODE_CHECK;
	}
}

// 디버깅용 거리 출력 함수
void distance_print(void) {
	if (ultrasonic_print_timer > 999) {
		ultrasonic_print_timer = 0;
		
		for (int i = 0; i < 3; i++) {
			printf("%d_Distance: %ld\n", i, ultrasonic_dis[i]);
		}
	}
}
