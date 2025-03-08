/* fnd.c - 7-세그먼트 디스플레이 업데이트 함수
 *
 * 이 파일은 숫자 및 특수 패턴 폰트를 정의하고, 멀티플렉싱을 통해
 * 여러 모드로 디스플레이를 갱신하는 함수를 구현합니다.
 */

#include "fnd.h"

// 폰트 배열 정의:
// fnd_font: 0~9 숫자 및 특수 패턴 (인덱스 10)
// fnd_2_font, fnd_3_font: 추가 모드에서 사용할 대체 패턴 배열
uint8_t fnd_font[] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xD8, 0x80, 0x98, 0x7F };
uint8_t fnd_2_font[] = { 0xfb, 0xf9, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf6, 0xf4, 0xf0 };
uint8_t fnd_3_font[] = { 0xff, 0xff, 0xff, 0xfe, 0xde, 0xce, 0xc6, 0xc6, 0xff, 0xf7, 0xe7, 0xc7, 0xc6, 0xc6, 0xc6, 0xc6 };

/* init_fnd()
 * 7-세그먼트 디스플레이를 초기화합니다.
 *  - PORTC의 모든 핀을 출력으로 설정하여 세그먼트 데이터를 출력합니다.
 *  - PORTB의 D1~D4 핀을 출력으로 설정하여 각 자리(디지털)를 제어합니다.
 *  - 모든 세그먼트를 끄는 상태로 초기화합니다.
 */
void init_fnd(void)
{
    FND_DATA_DDR = 0xFF;  // PORTC의 모든 핀을 출력으로 설정
    FND_DIGIT_DDR |= (1 << FND_DIGIT_D1) | (1 << FND_DIGIT_D2) | (1 << FND_DIGIT_D3) | (1 << FND_DIGIT_D4);
    FND_DATA_PORT = ~0x00;  // 모든 세그먼트 OFF (active-low 가정)
}

/* fnd_display_1()
 * 디스플레이 모드 1 업데이트 함수:
 *  - 4자리 디스플레이의 각 자리를 순차적으로 갱신합니다.
 *  - 초(seconds)와 분(minutes)를 표시하며, 1초마다 점(특수 패턴)을 깜빡이게 합니다.
 *  - 매개변수 'seconds'는 전체 초 값을 나타냅니다.
 */
void fnd_display_1(uint32_t* millis, uint32_t* seconds)
{
    static int digit_select = 0;  // 현재 활성화된 자리를 기억 (0~3)
    
    switch (digit_select)
    {
        case 0:
            FND_DIGIT_PORT = 0x80;  // 첫 번째 자리 활성화 (10000000)
            FND_DATA_PORT = fnd_font[*seconds % 10];  // 초의 일의 자리 (0~9)
            break;
            
        case 1:
            FND_DIGIT_PORT = 0x40;  // 두 번째 자리 활성화 (01000000)
            FND_DATA_PORT = fnd_font[(*seconds / 10) % 6];  // 초의 십의 자리 (0~5)
            break;
            
        case 2:
            FND_DIGIT_PORT = 0x20;  // 세 번째 자리 활성화 (00100000)
            // 추가 기능: 1초마다 점(특수 패턴)을 깜빡임
            if ((*seconds) % 2)
                FND_DATA_PORT = fnd_font[10] & fnd_font[(*seconds / 60) % 10];
            else
                FND_DATA_PORT = fnd_font[(*seconds / 60) % 10];  // 분의 일의 자리 (0~9)
            break;
            
        case 3:
            FND_DIGIT_PORT = 0x10;  // 네 번째 자리 활성화 (00010000)
            FND_DATA_PORT = fnd_font[(*seconds / 600) % 6];  // 분의 십의 자리 (0~5)
            break;
    }
    
    // 다음 자리로 이동 (순환 방식)
    digit_select = (digit_select + 1) % 4;
}

/* fnd_display_2()
 * 디스플레이 모드 2 업데이트 함수:
 *  - 4자리 디스플레이를 순차 갱신하며, 초 값을 표준 폰트와 대체 폰트를 혼합해 표시합니다.
 */
void fnd_display_2(uint32_t* millis, uint32_t* seconds)
{
    static int digit_select = 0;
    
    switch (digit_select)
    {
        case 0:
            FND_DIGIT_PORT = 0x80;  // 첫 번째 자리
            FND_DATA_PORT = fnd_font[*seconds % 10];  // 초의 일의 자리
            break;
            
        case 1:
            FND_DIGIT_PORT = 0x40;  // 두 번째 자리
            FND_DATA_PORT = fnd_font[(*seconds / 10) % 6];  // 초의 십의 자리
            break;
            
        case 2:
            FND_DIGIT_PORT = 0x20;  // 세 번째 자리
            FND_DATA_PORT = fnd_2_font[*seconds % 16];  // 대체 폰트 적용
            break;
            
        case 3:
            FND_DIGIT_PORT = 0x10;  // 네 번째 자리
            FND_DATA_PORT = fnd_3_font[*seconds % 16];  // 또 다른 대체 폰트 적용
            break;
    }
    
    digit_select = (digit_select + 1) % 4;
}

/* fnd_display_3()
 * 디스플레이 모드 3 업데이트 함수:
 *  - 밀리초(ms)와 초(sec)의 일부 값을 조합하여 표시합니다.
 *  - 첫 두 자리에는 밀리초의 일부, 마지막 두 자리에는 초 값을 표시합니다.
 */
void fnd_display_3(uint32_t* millis, uint32_t* seconds)
{
    static int digit_select = 0;
    
    switch (digit_select)
    {
        case 0:
            FND_DIGIT_PORT = 0x80;  // 첫 번째 자리
            FND_DATA_PORT = fnd_font[(*millis / 10) % 10];  // 밀리초의 십의 자리
            break;
            
        case 1:
            FND_DIGIT_PORT = 0x40;  // 두 번째 자리
            FND_DATA_PORT = fnd_font[(*millis / 100) % 10];  // 밀리초의 백의 자리
            break;
            
        case 2:
            FND_DIGIT_PORT = 0x20;  // 세 번째 자리
            FND_DATA_PORT = fnd_font[*seconds % 10];  // 초의 일의 자리
            break;
            
        case 3:
            FND_DIGIT_PORT = 0x10;  // 네 번째 자리
            FND_DATA_PORT = fnd_font[(*seconds / 10) % 6];  // 초의 십의 자리
            break;
    }
    
    digit_select = (digit_select + 1) % 4;
}
