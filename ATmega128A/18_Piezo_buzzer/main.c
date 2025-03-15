#define F_CPU	16000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 
 extern const int Elise_Tune[];
 extern const int Elise_Beats[];
 
 int main(void)
 {
     init_speaker();	
 
     while(1)
     {
 /*
         OCR1A=1702;   // 삐~뽀 레 
         _delay_ms(1000);
         OCR1A=1431;   // 파  
         _delay_ms(1000);
 
 */
         
         //Beep(5);
         // RRR();
 // 		_delay_ms(3000);
 // 		Siren(5);
 // 		_delay_ms(3000);

        Music_Player(Elise_Tune, Elise_Beats);		
     }
 }
 