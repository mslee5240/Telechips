#include "uart0.h"
#include "led.h"

/*
 * rx_msg_received :
 * - 이전 방식의 코드에서 '\n' 수신시 1로 설정해 메시지 완성을 알리는 플래그였으나,
 *	 현재 코드에서는 2차원 큐(rx_buff)를 활용하므로 직접 사용하지 않을 수 있습니다.
 *	 만약 필요하다면 ISR에서 '\n'을 수신했을 때 이 값을 1로 만들어
 *	 메인 루프가 메시지 도착을 감지하도록 쓸 수 있습니다.
*/
volatile uint8_t rx_msg_received = 0;

/*
 * ISR(USART0_RX_vect)
 * - PC 등에서 UART0로 1바이트가 수신될 때마다 호출됩니다.
 * - 수신된 문자를 rx_buff[rear] 배열에 저장하고, '\n'을 만나면
 *   문자열 끝에 '\0'을 추가하여 하나의 "명령" 단위가 완성됩니다.
 * - rear 인덱스를 증가시켜 다음 명령을 저장할 위치로 이동합니다.
 * - COMMAND_NUMBER, COMMAND_LENGTH 범위를 넘지 않도록 주의해야 합니다.
*/
volatile int rear = 0;
volatile int front = 0;		// pc_command_processing()에서 가져갈 위치

ISR(USART0_RX_vect)
{
	// static으로 선언해 한 번 ISR 진입 시 유지되는 1차원 인덱스
	volatile static int i = 0;
	volatile uint8_t rx_data = UDR0;	// 1바이트 읽으면 자동으로 RX 인터럽트 플래그 클리어
	
	if (rx_data == '\n') {
		// 수신 문자열의 끝 표시
		rx_buff[rear][i] = '\0';
		
		// 다음 문자열을 저장할 큐 위치로 이동
		rear = (rear + 1) % COMMAND_NUMBER;
		
		// 인덱스 i를 0으로 초기화하여 새 문자열을 받도록 준비
		i = 0;
		
		// 필요하다면 메시지 완성 플래그 설정 가능
		// rx_msg_received = 1;
	}
	else {
		// '\n' 전까지의 문자를 버퍼에 저장
		rx_buff[rear][i++] = rx_data;
		
		// COMMAND_LENGTH 범위를 넘어가면 오버플로 방지 로직이 필요함
		// ex) if (i >= COMMAND_LENGTH - 1) { i = COMMAND_LENGTH - 2; }
	}
}

/*
 * init_uart0()
 * - UART0을 9600bps(2배속 모드)로 동작하도록 설정합니다.
 * - RX, TX, RX Interrupt를 모두 활성화합니다.
*/
void init_uart0(void)
{
	// Baud Rate 설정: 9600bps @ 16MHz. 2배속
	UBRR0H = 0x00;
	UBRR0L = 207;	// 9600bps
	// UBRR0L = 16;		// 115,200bps (2배속 모드시)
	
	// 2배속 모드(U2X0=1)
	UCSR0A |= (1 << U2X0);
	
	// 비동기 모드, 8비트 데이터, No 패리티, 1스톱비트
	UCSR0C |= 0x06;
	
	// RXEN0: 수신 Enable, TXEN0: 송신 Enable, RXCIE0: RX 인터럽트 Enable
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

/*
 * UART0_transmit()
 * - 폴링 방식으로 1바이트를 전송합니다.
 * - UDR0의 전송 버퍼가 비어(UDRE0=1) 있을 때까지 대기 후, 데이터를 전송 레지스터에 기록
*/
void UART0_transmit(uint8_t data)
{
	// 전송 버퍼(UDR0)가 빌 때까지 대기
	while ( !(UCSR0A & (1 << UDRE0)) ) {
		// no operation
	}
	// UDR0에 쓰면 UART가 자동으로 해당 바이트 전송
	UDR0 = data;
}

char* led_func[8] = {
	"led_all_on",
	"led_all_off",
	"shift_left_led_on",
	"shift_right_led_on",
	"shift_left_keep_led_on",
	"shift_right_keep_led_on",
	"flower_on",
	"flower_off"
};

/*
 * pc_command_processing()
 * - 수신된 명령이 있으면(rx_buff에 데이터가 있으면) 순차적으로 꺼내 처리.
 * - front != rear => 큐에 새로운 문자열이 존재
 * - 문자열 비교(strncmp) 시 0이면 동일하다는 뜻이며, "led_all_on" 등을 찾으면 특정 동작 수행
*/
void pc_command_processing(void)
{
	if (front != rear)	// 새 명령이 수신됨
	{
		// 큐에서 문자열 한 줄을 꺼내 확인
		printf("%s\n", rx_buff[front]);		// ring buffer 출력 (디버그용)
		
		for (int i = 0; i < 8; i++)
		{
			if (strncmp((char*)rx_buff[front], led_func[i], strlen(led_func[i])) == 0)
			{
				printf("find!\n");
				fp_num = i;
				break;
			}
		}
		
		// 다음 데이터로 넘어가기 위해 front 인덱스 증가
		front = (front + 1) % COMMAND_NUMBER;
		// 큐가 가득 찬 상태에서의 처리(overflow)는 추가 로직 필요
	}
}


