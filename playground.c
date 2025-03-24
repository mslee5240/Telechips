volatile uint8_t timer2_ovf_right;
volatile uint8_t timer2_ovf_left;
volatile uint8_t timer2_ovf_forward;

ISR(TIMER2_OVF_vect) {
   
   ++timer2_ovf_right;
   ++timer2_ovf_left;
   ++timer2_ovf_forward;
}


// ISR INT7_vec
// 278page 표 12-3
// PE4 외부 INT4 초음파 센서의 상승 하강 에지 둘다 INT4_vec로 들어옴
// 상승 하강 한번씩 2번 들어옴
ISR(INT4_vect) {
   
   // 인터럽트가 들어왔는데... echo의 값이 high이면 상승이고
   if(ECHO_PIN & 1 << ECHO_RIGHT ) {
      // 상승에지
      //TCNT2 = 0;
      echoStartTimeArr[ULTRASONIC_RIGHT] = TCNT2;
      timer2_ovf_right = 0;   
   } 
   else {
      // low인 경우는 하강임
      // 하강 에지
      
      int count = TCNT2 - echoStartTimeArr[ULTRASONIC_RIGHT] + (timer2_ovf_right * 255);
      ultrasonic_dist_right = 1000000.0 * count * 1024 / F_CPU; // 거리 구하기
      //printf("low tcnt2 %d %d cnt:%d ovf:%d\r\n", TCNT2, echoStartTimeArr[ULTRASONIC_RIGHT], count, timer2_ovf);
   }
}

ISR(INT5_vect) {
   
   // 인터럽트가 들어왔는데... echo의 값이 high이면 상승이고
   if(ECHO_PIN & 1 << ECHO_FORWARD ) {
      // 상승에지
      //TCNT2 = 0;
      echoStartTimeArr[ULTRASONIC_FORWARD] = TCNT2;
      timer2_ovf_forward = 0;
   }
   else {
      // low인 경우는 하강임
      // 하강 에지
      int count = TCNT2 - echoStartTimeArr[ULTRASONIC_FORWARD] + (timer2_ovf_forward * 255);
      ultrasonic_dist_forward = 1000000.0 * count * 1024 / F_CPU; // 거리 구하기
   }
}

ISR(INT6_vect) {
   // 인터럽트가 들어왔는데... echo의 값이 high이면 상승이고
   if(ECHO_PIN & 1 << ECHO_LEFT ) {
      // 상승에지
      //TCNT2 = 0;
      echoStartTimeArr[ULTRASONIC_LEFT] = TCNT2;
      timer2_ovf_left = 0;
   }
   else {
      // low인 경우는 하강임
      // 하강 에지
      int count = TCNT2 - echoStartTimeArr[ULTRASONIC_LEFT] + (timer2_ovf_left * 255);
      ultrasonic_dist_left = 1000000.0 * count * 1024 / F_CPU; // 거리 구하기
   }

}



// ultrasonic 초기화
void init_ultrasonic() {
   
   // DDRG 4번 포트만 output mode 설정
   TRIG_DDR |= 1 << TRIG_LEFT | 1 << TRIG_RIGHT | 1 << TRIG_FORWARD;   
   
   // DDRE 4번 포트만 input모드로 설정
   ECHO_DDR &= ~(1 << ECHO_LEFT | 1 << ECHO_RIGHT | 1 << ECHO_FORWARD);
   
   
   // EICRB 레지스터 참고!
   // ISC 비트 설정에 따른 이터럽트 발생 시점 
   //apge 287 12-6
   // 0 1 : 상승 에지 ( rising edge) 하강 (falling edge) 둘 다 INT를 띄우도록
   EICRB |= 0 << ISC41 | 1 << ISC40;
   EICRB |= 0 << ISC51 | 1 << ISC50;
   EICRB |= 0 << ISC61 | 1 << ISC60;
   
   ULTRASONIC_TIMER_TCCR |= 1 << CS22 | 1 << CS20; // 1024로 분주 설정
   
   //TCNT1 = 0; // 이래도 될 것 같은데
   
   // 문 열어놓기
   // 287 page 12-6
   // EIMSK(External Interrupt Mask Register)은 외부 인터럽트를 활성화 & 비활성화하는 레지스터
   EIMSK |= 1 << INT4 | 1 << INT5 | 1 << INT6;
   
   // timer2 overflow INT 허용 ( enable )
   TIMSK |= 1 << TOIE2; // TIMSK |= 0x01;
}