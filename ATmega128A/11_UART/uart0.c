#include "uart0.h"

volatile uint8_t rx_msg_received = 0;
/*
	PC comportmaster로부터 1byte가 들어올 때마다 이 곳으로 들어온다. (RX INT)
	예) led_all_on\n ==> 11번 이 곳으로 들어온다.
	    led_all_off\n
*/

volatile int rear = 0;
volatile int front = 0;
ISR(USART0_RX_vect)
{
	volatile uint8_t rx_data;
	volatile static int i = 0;
		
	rx_data = UDR0;	// uart0의 H/W register(UDR0)로부터 1byte를 읽어들인다.
					// rx_data = UDR0;를 실행하면 UDR0의 내용이 빈다.(Empty)
	if (rx_data == '\n') {
		rx_buff[rear++][i] = '\0';
		rear %= COMMAND_NUMBER;		// rear : 0~9
		i = 0;	// 다음 string을 저장하기 위한 1차원 index 값을 0으로
				// rx_buffer queue full check하는 logic 추가 필요!
		/*
		rx_msg_received = 1;	// 완전한 message 수신
		rx_buff[i] = '\0';		// 문장의 끝을 NULL로 집어 넣는다.
		i = 0;
		*/
	}
	else {
		rx_buff[rear][i++] = rx_data;	// COMMAND_LENGTH를 check하는 logic 추가 필요
		/*
		rx_buff[i++] = rx_data;
		*/
	}
}

/*
	1. 전송 속도: 9600bps [총 글자수 : 9600 / 10bit = > 960자]      
		1글자를 송.수신 하는데 소요 시간: 약 1ms
	2. 비동기 방식(start / stop 부호 비트로 데이터를 구분)
	3. RX(수신) : 인터럽트 방식으로 구현 
*/

void init_uart0(void)
{
	// 1. 9600bps로 설정; (p.219 표9-9)
	UBRR0H = 0x00;
	UBRR0L = 207; // 9600bps
	//UBRR0L = 16;	// 115,200bps

	// 2. 2배속 통신; (p.215 표9-1)
	UCSR0A |= 1 << U2X0;
	UCSR0C |= 0x06;		// 비동기 - data 8bits - none parity
	// RXEN0 : UART0로부터 수신이 가능하도록
	// TXEN0 : UART0로부터 송신이 가능하도록
	// RXCIE0 : UART0로부터 1byte가 들어오면(stop bit가 들어오면) rx interrupt를 발생 시켜라!
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0;
}

// UART0로 1byte를 전송하는 함수(Polling방식)
void UART0_transmit(uint8_t data)
{
	// 데이터 전송 중이면 전송이 끝날 때까지 기다린다.
	while ( !(UCSR0A & 1 << UDRE0) )
		;	// no operation
	UDR0 = data;	// data를 H/W전송 register에 쓴다.
}

void pc_command_processing(void)
{
	if (front != rear)	// rx_buffer에 data가 존재
	{
		printf("%s\n", rx_buff[front]);		// &rx_buff[front][0]
		if (strncmp(rx_buff[front], "led_all_on", strlen("led_all_on")) == NULL) 
		{
			printf("find: led_all_on\n");
			led_all_on();
		}
		front++;
		front %= COMMAND_NUMBER;
		// Queue Full Check 하는 logic 필요!
	}	
}