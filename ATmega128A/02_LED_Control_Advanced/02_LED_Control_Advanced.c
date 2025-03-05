/*
 * led.c
 *
 * Created: 2025-03-05 오전 10:21:52
 *  Author: eec04
 */ 

 #include "led.h"

 int led_main(void);	// 선언
 void led_all_on(void);
 void led_all_off(void);
 void shift_left_led_on(void);
 void shift_right_led_on(void);
 void shift_left_keep_led_on();
 void shift_right_keep_led_on();
 
 void shift_left_keep_led_off();
 void shift_right_keep_led_off();
 
 void flower_on(void);
 void flower_off(void);
 
 
 int led_main(void)	// 정의
 {
     DDRA = 0xff;	// PORTA에 연결된 pin 8개를 OUTPUT Mode로 설정
     
     while (1)
     {
         /*
         led_all_on();
         _delay_ms(500);
         led_all_off();
         _delay_ms(500);
         */
         
         // shift led
         _delay_ms(200);
         shift_left_led_on();
         _delay_ms(200);
         shift_right_led_on();
         _delay_ms(200);
         
         // keep led
         _delay_ms(200);
         shift_left_keep_led_on();
         shift_left_keep_led_off();
         _delay_ms(200);
         shift_right_keep_led_on();
         shift_right_keep_led_off();
         _delay_ms(200);
         
         // flower led
         _delay_ms(200);
         led_all_off();
         _delay_ms(200);
         flower_on();
         _delay_ms(200);
         flower_off();
         _delay_ms(200);
         led_all_off();
         _delay_ms(200);
     }
     
     return 0;
 }
 
 void led_all_on(void)
 {
     PORTA = 0xff;
 }
 
 void led_all_off(void)
 {
     PORTA = 0x00;
 }
 
 void shift_left_led_on(void)
 {
     PORTA = 0x00;
     for (int i = 0; i < 8; i++)
     {
         PORTA = 0b00000001 << i;
         _delay_ms(200);
     }
 }
 
 void shift_right_led_on(void)
 {
     PORTA = 0x00;
     for (int i = 0; i < 8; i++)
     {
         PORTA = 0b10000000 >> i;
         _delay_ms(200);
     }
 }
 
 void shift_left_keep_led_on()
 {
     PORTA = 0x00;
     for (int i = 0; i < 8; i++)
     {
         PORTA |= 0b00000001 << i;	// PORTA += 0b00000001 << i;
         _delay_ms(200);
     }
 }
 
 void shift_right_keep_led_on()
 {
     PORTA = 0x00;
     for (int i = 0; i < 8; i++)
     {
         PORTA |= 0b10000000 >> i;	// PORTA += 0b00000001 >> i;
         _delay_ms(200);
     }
 }
 
 void shift_left_keep_led_off()
 {
     PORTA = 0xff;
     for (int i = 0; i < 8; i++)
     {
         PORTA -= 0b00000001 << i;
         _delay_ms(200);
     }
 }
 
 void shift_right_keep_led_off()
 {
     PORTA = 0xff;
     for (int i = 0; i < 8; i++)
     {
         PORTA -= 0b10000000 >> i;
         _delay_ms(200);
     }
 }
 
 // 내 방법 flower
 void flower_on(void) {
     PORTA = 0b00011000;
     for (int i = 0; i < 3; i++)
     {	
         _delay_ms(300);
         PORTA |= (PORTA >> 1) | (PORTA << 1);
         
     }
 }
 // 우선순위 연산자를 사용해서 괄호를 치지 않는 습관을 들이자!! => 코드가 더러워짐

 void flower_off(void) {
    PORTA = 0b11111111;
    for (int i = 0; i < 3; i++)
    {
        PORTA &= (PORTA >> 1) & (PORTA << 1);
        _delay_ms(300);
    }
}

 // 교수님 flower
 void flower_on(void) {
    PORTA = 0;
    for (int i = 0; i < 4; i++)
    {	
        PORTA |= 0x10 << i | 0x08 >> i;
        _delay_ms(100);
    }
}

void flower_off(void) {
    unsigned char high_nibble = 0xf0;
    unsigned char low_nibble = 0x0f;

    PORTA = 0;
    for (int i = ; i < 4; i++)
    {
        PORTA = (high_nibble >> i) & 0xf0 | (low_nibble << i) & 0x0f;
        _delay_ms(100);
    }
    PORTA = 0;
    _delay_ms(200);
}
 
