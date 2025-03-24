#include "uart0.h" // UART0_transmit(bt_data); 사용
#include "uart1.h"


volatile uint8_t bt_data = 0;
ISR(USART1_RX_vect)
{
	bt_data = UDR1;		// BT로부터 들어온 HW register(UDR1)을 1byte 읽어 들인다.
						// bt_data = UDR1; 실행하면 UDR1의 내용이 클리어됨.
	UART0_transmit(bt_data);	// BT로부터 들어온 문자가 어떤 것인지 확인하기 위해서 comport master로 출력
}

void init_uart1(void)
{
	UBRR1H = 0x00;
	UBRR1L = 207; // 9600bps

	// 2배속 통신
	UCSR1A |= 1 << U2X1;
	UCSR1C |= 0x06;		// 비동기 - data 8bits - none parity
	// RXEN1 : UART1로부터 수신이 가능하도록
	// TXEN1 : UART1로부터 송신이 가능하도록
	// RXCIE1 : UART1로부터 1byte가 들어오면(stop bit가 들어오면) rx interrupt를 발생 시켜라!
	UCSR1B |= 1 << RXEN1 | 1 << TXEN1 | 1 << RXCIE1;
}
