#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"

extern int samsung[];
extern int samsung_beats[];

 int main(void)
 {
     init_buzzer();	
 
     while(1)
     {
         OCR1A=1702;		// 삐~뽀 레 
         _delay_ms(1000);
         OCR1A=1431;		// 파  
         _delay_ms(1000);
         
         beep(5);
		 
         rrr();
  		 _delay_ms(3000);
		 
  		 siren(5);
  		 _delay_ms(3000);

        music_player(samsung, samsung_beats);	
     }
	 
	 return 0;
 }
 