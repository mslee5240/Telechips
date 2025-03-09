/* main.c - 버튼 제어 및 시간 기반 7-세그먼트 디스플레이 애플리케이션
 *
 * 이 파일은 하드웨어 초기화(버튼, 7-세그먼트, 타이머) 후, 메인 루프에서
 * 버튼 입력에 따른 모드 전환, 시간 업데이트, 깜빡임 효과 및 디스플레이 갱신을 수행합니다.
 */

 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "button.h"
 #include "fnd.h"
 
 // 전역 변수: 시간 측정 및 디스플레이 제어에 사용 (volatile로 선언하여 ISR과 공유)
 volatile uint32_t time_toggle = 0;   // 0: 시간 업데이트 활성, 1: 정지
 volatile uint32_t milliseconds = 0;      // 밀리초 카운터 (타이머 ISR에서 증가)
 volatile uint32_t displayUpdateCounter = 0;      // 디스플레이 갱신 주기 제어 변수
 volatile uint32_t blinkCounter = 0;       // 깜빡임 효과를 위한 카운터
 volatile uint32_t seconds = 0;       // 초 단위 카운터 (milliseconds에서 1초마다 증가)
 
 // 포인터를 사용해 디스플레이 함수에 시간 데이터를 전달
 volatile uint32_t* f_ms = &milliseconds;
 volatile uint32_t* f_sec = &seconds;
 
 /* reset_time()
  * 시간 관련 카운터(milliseconds, seconds)를 0으로 초기화합니다.
  */
 void reset_time() {
     milliseconds = 0;
     seconds = 0;
 }
 
 /* TIMER0_OVF_vect - 타이머0 오버플로우 인터럽트 서비스 루틴 (ISR)
  * - 타이머 카운터(TCNT0)를 6으로 재설정하여 일정 간격을 유지합니다.
  * - time_toggle이 0이면 밀리초 카운터와 깜빡임 카운터를 증가시킵니다.
  * - displayUpdateCounter를 증가시켜 메인 루프에서 디스플레이 갱신을 신호합니다.
  */
 ISR(TIMER0_OVF_vect)
 {
     TCNT0 = 6;  // 타이머 카운터 재설정
     if (time_toggle == 0)
     {
         milliseconds++;  // 밀리초 카운터 증가
         blinkCounter++;   // 깜빡임 카운터 증가
     }
     displayUpdateCounter++;      // 디스플레이 갱신 신호
 }
 
 /* 함수 프로토타입 선언: 타이머 및 전체 초기화 함수 */
 void init_timer_0(void);
 void init_all(void);
 
 int main(void)
 {
     init_all();  // 버튼, 디스플레이, 타이머 초기화
     
     int button_state[4] = { 0 };  
     // 버튼 상태 배열: 여기서는 index 0만 사용하여 디스플레이 모드를 선택합니다.
     
     // 디스플레이 모드별 함수 포인터 배열:
     //  - button_state[0] 값에 따라 fnd_display_1, fnd_display_2, fnd_display_3 중 하나를 호출합니다.
     void (*fp_0[])(volatile uint32_t*, volatile uint32_t*) =
     {
         fnd_display_1,
         fnd_display_2,
         fnd_display_3
     };
     
     int modeToggle = 0;
     while (1)
     {
         // 버튼 0 입력: 디스플레이 모드를 전환합니다.
         if (get_button(BUTTON_0, BUTTON_0_PIN))
         {
             if (button_state[0] == 2 && modeToggle == 0) {
                 modeToggle = !modeToggle;
             }
             if (button_state[0] == 0 && modeToggle == 1) {
                 modeToggle = !modeToggle;
             }
             
             if (modeToggle == 0) {
                 button_state[0]++;
             }
             else {
                 button_state[0]--;
             }
                 
             //button_state[0]++;          // 모드 인덱스 증가
             //button_state[0] %= 3;         // 0, 1, 2의 3가지 모드로 순환
             reset_time();               // 시간 카운터 초기화
             init_fnd();                 // 디스플레이 초기화 (자릿수 리셋)
         }
         
         // 디스플레이 갱신: displayUpdateCounter가 임계값을 넘으면 화면을 업데이트합니다.
         if (displayUpdateCounter > 1)
         {
             displayUpdateCounter = 0;  // 갱신 신호 리셋
             
             // 모드에 따라 깜빡임 효과를 위한 주기 및 끄는 시간 설정
             uint32_t blink_period = 900;       // 기본: 1초 주기
             uint32_t blink_off_duration = 100;    // 기본: 0.1초 동안 화면 OFF
             
             switch (button_state[0])
             {
                 case 0:  // 모드 0: 1초 주기
                     blink_period = 1000;
                     blink_off_duration = 100;
                     break;
                 case 1:  // 모드 1: 0.5초 주기
                     blink_period = 500;
                     blink_off_duration = 50;
                     break;
                 case 2:  // 모드 2: 0.1초 주기
                     blink_period = 100;
                     blink_off_duration = 10;
                     break;
             }
             
             // 깜빡임 효과: blinkCounter의 나머지를 비교하여 일정 시간 동안 화면을 끕니다.
             if ((blinkCounter % blink_period) < blink_off_duration) {
                 FND_DATA_PORT = 0xff;  // 화면 OFF (모든 세그먼트 비활성)
             }
             else {
                 // 현재 모드에 해당하는 디스플레이 함수를 호출하여 화면 갱신
                 fp_0[button_state[0]] (f_ms, f_sec);
             }
         }
         
         // 1초(약 1000ms)가 경과하면 초(seconds)를 증가시키고 밀리초 카운터를 초기화합니다.
         if (milliseconds >= 999)
         {
             milliseconds = 0;
             seconds++;
         }
         
         // 버튼 1 입력: 시간과 디스플레이를 리셋합니다.
         if (get_button(BUTTON_1, BUTTON_1_PIN))
         {
             reset_time();
             init_fnd();
         }
         
         // 버튼 2 입력: time_toggle 값을 토글하여 시간 업데이트를 멈추거나 재개합니다.
         if (get_button(BUTTON_2, BUTTON_2_PIN))
         {
             time_toggle = !time_toggle;
         }
     }
 
     return 0;
 }
 
 /* init_timer_0()
  * 타이머0을 초기화하여 주기적인 인터럽트를 발생시킵니다.
  *  - TCNT0를 프리로드하고, 프리스케일러를 설정합니다.
  *  - 타이머0 오버플로우 인터럽트를 활성화합니다.
  */
 void init_timer_0(void)
 {
     TCNT0 = 6;  // 타이머 카운터 프리로드
     TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;  // 프리스케일러 설정 (예: 256)
     TIMSK |= 1 << TOIE0;  // 타이머0 오버플로우 인터럽트 활성화
     sei();  // 전역 인터럽트 활성화
 }
 
 /* init_all()
  * 모든 하드웨어 모듈(버튼, 7-세그먼트, 타이머)을 초기화합니다.
  */
 void init_all(void)
 {
     init_button();
     init_fnd();
     init_timer_0();
 }
 