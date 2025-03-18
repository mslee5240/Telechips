#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

// 하드웨어 초기화 및 사용을 위해 include
#include "led.h"
#include "button.h"
#include "fnd.h"
#include "uart0.h"
#include "uart1.h"
#include "ultrasonic.h"

// msec_count: 대략 1ms 단위로 증가하는 카운터(타이머0 오버플로우로 증가)
// ultrasonic_check_timer: 초음파를 주기적으로 측정하기 위한 타이머 역할
volatile int msec_count = 0;
volatile int ultrasonic_check_timer = 0;

// stdout을 UART0 출력 함수에 연결해서 printf()가 가능하도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

//----------------------------------------------------
// [ ISR(TIMER0_OVF_vect) ]
// Timer0 오버플로우가 발생할 때마다 호출되는 인터럽트 서비스 루틴(ISR).
// - 분주비 설정에 따라 일정 시간마다 오버플로우가 일어남
// - 본 예제에서는 약 1ms 주기로 오버플로우가 일어나도록 설정
//----------------------------------------------------
ISR(TIMER0_OVF_vect)
{
    // Timer0의 오버플로우 시점마다 TCNT0를 재설정해서 1ms 간격을 유지
    TCNT0 = 6;
    
    // ms 단위 카운터 증가
    msec_count++;
    // 초음파 센서 측정을 일정 주기로 실행하기 위해 증가
    ultrasonic_check_timer++;
}

//----------------------------------------------------
// 타이머0 초기화 함수
// - 분주비 설정, 초기 카운터값 설정, 인터럽트 활성화
//----------------------------------------------------
void init_timer_0(void)
{
    // Timer0 카운터 초기값 설정
    // (오버플로우가 256카운트 - 6 = 250카운트 남음)
    // 250 × (분주비 256 / CPU클록 16MHz) = 250 × 16μs = 4000μs(4ms)에 한 번씩
    // 실제 코드에서는 약 1ms 주기로 맞춘 예제이지만
    // 오버플로우 간격은 계산 시 사용 환경에 따라 조정 가능
    TCNT0 = 6;
    
    // 분주비 256로 설정: (CS02=1, CS01=0, CS00=0)
    TCCR0 |= (1 << CS02);

    // Timer0 오버플로우 인터럽트 활성화
    TIMSK |= (1 << TOIE0);
}

// 외부에서 함수 포인터로 LED 제어 함수를 호출할 때 사용하려는 것 같지만,
// 현재 예제에서는 구체적으로 사용되지 않는 부분
extern volatile int fp_num;
void (*fp_led[])(void) =
{
    led_all_on,
    led_all_off,
    shift_left_led_on,
    shift_right_led_on,
    shift_left_keep_led_on,
    shift_right_keep_led_on,
    flower_on,
    flower_off
};

// 메인 함수
int main(void)
{
    // UART 초기화 및 타이머 초기화
    init_timer_0();    // Timer0 설정
    init_uart0();      // UART0 설정
    init_uart1();      // UART1 설정
    init_ultrasonic(); // 초음파 센서 관련(Trigger, Echo, Timer1, EXTI 등) 초기화
    
    // 표준출력(stdout)을 UART0로 연결하여 printf()를 사용 가능하게 함
    stdout = &OUTPUT;
    
    // 전역 인터럽트 허용(모든 개별 인터럽트 설정 후 sei()로 전체 허용)
    sei();
    
    // LED, 버튼 등 다른 주변장치 초기화
    init_led();
    init_button();
    
    // 버튼 상태를 저장하기 위한 변수 (예제에는 실제 사용 안 함)
    int button_state[4] = {0};
    
    // 무한 루프
    while (1)
    {
        // 주기적(약 1초 간격)으로 초음파 센서 거리 측정 및 출력
        distance_ultrasonic();
    }
    return 0;
}
