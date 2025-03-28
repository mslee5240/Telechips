#include "uart.h"

// UART 초기화, 송신, PC 명령 처리 함수
void init_uart1(void);
void UART1_transmit(uint8_t data);
void bt_command_processing(void);

volatile uint8_t bt_data;
