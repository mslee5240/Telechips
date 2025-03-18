#include "uart.h"

/*
 * rx_buff:
 * - [COMMAND_NUMBER][COMMAND_LENGTH] 크기의 2차원 배열
 * - 한 줄(문자열)씩 수신할 때마다 rear 인덱스가 가리키는 곳에 저장
 * - pc_command_processing()에서 front 인덱스를 통해 꺼내 감
*/
volatile uint8_t rx_1_buff[COMMAND_NUMBER][COMMAND_LENGTH];

// 큐의 삽입 및 추출 인덱스
volatile int uart1_rear;	// 데이터가 새로 들어갈 위치
volatile int uart1_front;	// 아직 처리하지 않은 데이터를 꺼낼 위치

// UART 초기화, 송신, PC 명령 처리 함수
void init_uart1(void);
void UART1_transmit(uint8_t data);
void bt_command_processing(void);


