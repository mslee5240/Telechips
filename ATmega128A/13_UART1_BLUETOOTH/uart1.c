#include "uart1.h"

volatile int uart1_rear_idx = 0;
volatile int uart1_front_idx = 0;
ISR(USART1_RX_vect)
{
	volatile uint8_t rx_data;
	volatile static int i = 0;
		
	rx_data = UDR0;
	
	if (rx_data == '\n') {
		rx_1_buff[uart1_rear_idx++][i] = '\0';
		uart1_rear_idx %= COMMAND_NUMBER;
		i = 0;
	}
	else {
		rx_1_buff[uart1_rear_idx][i++] = rx_data;
	}
}

void init_uart1(void)
{
	UBRR1H = 0x00;
	UBRR1L = 207; // 9600bps

	// 2배속 통신
	UCSR1A |= 1 << U2X1;
	UCSR1C |= 0x06;		// 비동기 - data 8bits - none parity
	// RXEN0 : UART0로부터 수신이 가능하도록
	// TXEN0 : UART0로부터 송신이 가능하도록
	// RXCIE0 : UART0로부터 1byte가 들어오면(stop bit가 들어오면) rx interrupt를 발생 시켜라!
	UCSR1B |= 1 << RXEN1 | 1 << TXEN1 | 1 << RXCIE1;
}


void UART1_transmit(uint8_t data)
{
	while ( !(UCSR1A & 1 << UDRE1) )
		;
	UDR1 = data;
}
