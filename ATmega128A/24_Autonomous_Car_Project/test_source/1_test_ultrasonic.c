#include "ultrasonic.h"

extern volatile int ultrasonic_check_timer;
volatile uint32_t ultrasonic_dis = 0;
volatile uint16_t timer2_overflow = 0;     // Timer2 오버플로우 횟수


// Timer2 오버플로우 인터럽트: Timer2가 255에서 0으로 넘어갈 때마다 호출됨
ISR(TIMER2_OVF_vect) {
    timer2_overflow++;
}

// 외부 인터럽트(INT5) ISR: 에코 신호의 상승/하강 에지에서 호출됨
ISR(INT5_vect) {
    // ECHO 핀 상태에 따라 상승/하강 에지 구분
    if (ECHO_PIN & (1 << ECHO)) {  // 상승 에지: 에코 시작
        TCNT2 = 0;               // Timer2 카운터 리셋
        timer2_overflow = 0;     // 오버플로우 횟수도 초기화
    } else {                     // 하강 에지: 에코 종료
        // 전체 카운트: (오버플로우 횟수 * 256) + 현재 TCNT2 값
        uint32_t total_ticks = ((uint32_t)timer2_overflow << 8) + TCNT2;
        
        //ultrasonic_dis = (total_ticks * 128UL) / 16;
		ultrasonic_dis = total_ticks * 8;
    }
}

void init_ultrasonic(void) {
    TRIG_DDR |= (1 << TRIG);   // 트리거 핀 출력 설정
    ECHO_DDR &= ~(1 << ECHO);  // 에코 핀 입력 설정
    
    // 외부 인터럽트 설정: INT5를 "논리 변화" 감지(ISC51:0 = 01)로 설정
    EICRB &= ~((1 << ISC51) | (1 << ISC50));
    EICRB |= (0 << ISC51) | (1 << ISC50);
    
    // Timer2 설정: Normal 모드(기본값) 및 128 분주로 동작하도록 설정
    TCCR2 = (1 << CS22) | (0 << CS21) | (1 << CS20);
    
    // Timer2 오버플로우 인터럽트 활성화
    TIMSK |= (1 << TOIE2);
    
    // 외부 인터럽트 INT5 활성화
    EIMSK |= (1 << INT5);
}

void trigger_ultrasonic(void) {
    TRIG_PORT &= ~(1 << TRIG); // Low
    _delay_us(1);
    TRIG_PORT |= (1 << TRIG);  // High
    _delay_us(12);             // 10µs 펄스 (규격)
    TRIG_PORT &= ~(1 << TRIG); // Low
}


void distance_ultrasonic(void) {
    if (ultrasonic_check_timer > 999) { // 1초마다 실행
        ultrasonic_check_timer = 0;
        
        // cm 단위 거리 계산 (1cm 당 약 58.8µs)
        printf("Distance: %ld\n", ultrasonic_dis);
        
        // 측정을 위한 초음파 트리거
        trigger_ultrasonic();
    }
}
