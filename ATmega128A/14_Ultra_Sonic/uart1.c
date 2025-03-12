#include "uart1.h"

volatile int uart1_rear = 0;
volatile int uart1_front = 0;
ISR(USART1_RX_vect)
{
	volatile uint8_t rx_data;
	volatile static int i = 0;
		
	rx_data = UDR1;
	
	if (rx_data == '\n') {
		rx_1_buff[uart1_rear++][i] = '\0';
		uart1_rear %= COMMAND_NUMBER;
		i = 0;
	}
	else {
		rx_1_buff[uart1_rear][i++] = rx_data;
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

char* led_func_1[8] = {
	"led_all_on",
	"led_all_off",
	"shift_left_led_on",
	"shift_right_led_on",
	"shift_left_keep_led_on",
	"shift_right_keep_led_on",
	"flower_on",
	"flower_off"
};
void bt_command_processing(void)
{
	if (uart1_front != uart1_rear)	// 새 명령이 수신됨
	{
		// 큐에서 문자열 한 줄을 꺼내 확인
		printf("%s\n", rx_1_buff[uart1_front]);		// ring buffer 출력 (디버그용)
		
		for (int i = 0; i < 8; i++)
		{
			if (strncmp((char*)rx_1_buff[uart1_front], led_func_1[i], strlen(led_func_1[i])) == 0)
			{
				printf("find!\n");
				fp_num = i;
				break;
			}
		}
		
		// 다음 데이터로 넘어가기 위해 front 인덱스 증가
		uart1_front = (uart1_front + 1) % COMMAND_NUMBER;
		// 큐가 가득 찬 상태에서의 처리(overflow)는 추가 로직 필요
	}
}
