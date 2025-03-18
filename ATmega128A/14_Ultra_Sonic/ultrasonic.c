#include "ultrasonic.h"

// main.c에서 선언된 전역 변수. 초음파 센서 트리거 주기를 제어하기 위해 사용
extern volatile int ultrasonic_check_timer;

// ultrasonic_dis: 측정된 거리값(정확히는 타이머카운트 기반의 값)
// scm: 거리 정보를 문자열로 저장하기 위한 버퍼
volatile int ultrasonic_dis = 0;
volatile char scm[50];

//----------------------------------------------------
// [ ISR(INT4_vect) ]
// PE4 핀에 연결된 외부 인터럽트4. (ECHO 핀 신호가 바뀔 때마다 인터럽트 발생)
// 초음파 센서에서는 'ECHO' 핀이 HIGH -> LOW로 변화하는 Edge를 이용해
// 돌아온 초음파의 펄스 폭(High 구간 지속 시간)을 계산한다.
// 본 코드에서는 Rising Edge와 Falling Edge 모두 인터럽트를 받도록 설정하여,
// - Rising Edge에서는 Timer1을 0으로 초기화
// - Falling Edge에서는 Timer1 카운트값을 기반으로 시간 계산을 진행
//----------------------------------------------------
ISR(INT4_vect)
{
    // ECHO 핀이 1이면(Rising Edge) -> 초음파 펄스가 시작되는 시점
    if (ECHO_PIN & (1 << ECHO))
    {
        // Timer1 카운터를 0으로 클리어(펄스 시작)
        TCNT1 = 0;
    }
    else
    {
        // ECHO 핀이 0이면(Falling Edge) -> 초음파 펄스가 끝나는 시점
        // Timer1에 누적된 카운트값을 시간(us)으로 환산
        // 16MHz를 1024로 분주 → 15625Hz(약 64us/카운트)
        // = 1카운트마다 64us
        // 그래서 (카운트값 × 64us)가 ECHO 핀 High 지속 시간
        ultrasonic_dis = 1000000.0 * TCNT1 * 1024 / F_CPU;
        
        // 일반적으로 1cm를 이동하는 데 약 58us 소요되므로
        // 측정된 시간(us)을 58로 나눈 값이 센서와 물체 사이의 거리(cm)
        sprintf(scm, "dis : %dcm\n", ultrasonic_dis / 58);
    }
}

//----------------------------------------------------
// 초음파 센서 초기화 함수
// - 트리거(Trig) 핀을 출력 모드로 설정
// - 에코(Echo) 핀을 입력 모드로 설정
// - INT4(에코 핀)에 대해 Rising Edge와 Falling Edge 모두 인터럽트 설정
// - Timer1을 설정하여 ECHO 핀의 High 구간을 측정
//----------------------------------------------------
void init_ultrasonic(void)
{
    // Trig 핀 출력 설정
    TRIG_DDR |= (1 << TRIG);
    
    // Echo 핀 입력 설정 (초음파 센서 모듈로부터 신호를 받아야 하므로)
    ECHO_DDR &= ~(1 << TRIG);
    
    // EICRB: INT4에 대해 입력 신호가 변할 때(양·음 에지) 모두 인터럽트를 발생시키도록 설정
    // ISC41=0, ISC40=1 → "The low level of INTn generates an interrupt request."와
    //                    "Any logical change on INTn generates an interrupt request."
    // 자료실 마다 정확한 매크로가 다를 수 있으므로, 실제로는
    // '논리적 변화(logical change)' 설정을 의미한다.
    EICRB |= (0 << ISC41) | (1 << ISC40);
    
    // Timer1 설정(16bit). 분주비 1024로 설정
    // 16MHz / 1024 = 15625Hz → 1카운트당 약 64us
    TCCR1B |= (1 << CS12) | (1 << CS10);
    
    // EIMSK: 외부 인터럽트4 활성화 (ECHO 핀에서 Rising/Falling Edge 감지)
    EIMSK |= (1 << INT4);
}

//----------------------------------------------------
// 초음파 센서에 트리거 신호를 주어 초음파를 발사시키는 함수
// - Trig 핀을 짧은 시간(10~15us 정도) High로 유지했다가 Low로 내려서
//   초음파 센서가 펄스를 발사하도록 함
//----------------------------------------------------
void trigger_ultrasonic(void)
{
    // Trig 핀을 Low
    TRIG_PORT &= ~(1 << TRIG);
    _delay_us(1);
    
    // Trig 핀을 High (약 10us ~ 15us)
    TRIG_PORT |= (1 << TRIG);
    _delay_us(15);
    
    // 다시 Trig 핀 Low
    TRIG_PORT &= ~(1 << TRIG);
}

//----------------------------------------------------
// distance_ultrasonic()
// - 약 1초 간격으로 초음파 트리거를 발생시키고, 이전 계산된 거리를 UART로 출력
// - ultrasonic_check_timer 변수가 main.c의 타이머0 ISR에서
//   1ms 단위로 증가하므로 1000이 되면 1초가 지난 것으로 판단
//----------------------------------------------------
void distance_ultrasonic(void)
{
    // 1초 간격으로 동작
    if (ultrasonic_check_timer >= 1000)
    {
        ultrasonic_check_timer = 0;
        
        // 이전 인터럽트에서 계산된 거리값(scm 변수)을 UART로 출력
        printf("%s", scm);
        
        // 초음파 신호 발사(트리거)
        trigger_ultrasonic();
    }
}
