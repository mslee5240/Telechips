#define F_CPU 16000000UL    // 동작 주파수를 16MHz로 지정, unsigned long
#include <avr/io.h>         // AVR 마이크로컨트롤러의 입출력 포트 제어를 위한 라이브러리
#include <util/delay.h>     // 지연 함수(_delay_ms, _delay_us)를 사용하기 위한 유틸리티 헤더

extern int led_main(void);

// none O/S 방식, loop monitor 방식
int main(void)
{
    DDRA = 0b11111111;      // DDRA는 PORTA의 데이터 방향을 설정하는 레지스터, PORTA의 모든 핀을 출력(OUTPUT, 1)으로 설정
                            // DDR(Data Direction Register): 방향 설정
                            // 1: 출력, 0: 입력
                            // 0b: 2진수
                            // 0x: 16진수(hex) => DDRA = 0xff;
                            // 상위 nibble = 상위 4bits / 하위 nibble = 하위 4bits
    while (1)
    {
        PORTA = 0b11111111; // 모든 핀 HIGH (LED ON), => PORTA = 0xff;
        _delay_ms(1000);    // 1초 대기

        PORTA = 0b00000000; // 모든 핀 LOW (LED OFF), => PORTA = 0x00;
        _delay_ms(1000);    // 1초 대기
    }

    return 0;
}

// [ASCII-CODE] - 암기 사항
// 48 - 0x30 - '0'
// 65 - 0x41 - 'A'
// 97 - 0x61 - 'a'
// 32 - 0x20 - 'Space'