#define F_CPU 16000000UL    // 동작 주파수를 16MHz로 지정
#include <avr/io.h>         // AVR 마이크로컨트롤러의 입출력 포트 제어를 위한 라이브러리
#include <util/delay.h>     // 지연 함수(_delay_ms, _delay_us)를 사용하기 위한 유틸리티 헤더

int main(void)
{
    DDRA = 0b11111111;      // DDRA는 PORTA의 데이터 방향을 설정하는 레지스터, PORTA의 모든 핀을 출력(OUTPUT, 1)으로 설정

    while (1)
    {
        PORTA = 0b11111111; // 모든 핀 HIGH (LED ON)
        _delay_ms(1000);    // 1초 대기

        PORTA = 0b00000000; // 모든 핀 LOW (LED OFF)
        _delay_ms(1000);    // 1초 대기
    }

    return 0;
}