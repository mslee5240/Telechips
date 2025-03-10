#ifndef UART0_H_
#define UART0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "def.h"

// led_all_on\n
// led_all_off\n
volatile uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];	// uart0 에서 들어온 문자를 저장하는 버퍼(변수)
volatile int rear;	// input index: USART0_RX_vect에서 집어 넣어 주는 index값
volatile int front;	// output index

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);

volatile uint8_t rx_msg_received;


#endif /* UART0_H_ */
