/*
 * uart.h
 *
 *  Created on: Mar 31, 2025
 *      Author: microsoft
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

#define COMMAND_NUMBER	20
#define COMMAND_LENGTH	40

volatile uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];

// -> buffer가 command를 element로 하는 원형큐가 되는것!!
volatile int rear; // push (HAL_UART_RxCpltCallback에서)
volatile int front; // pop (main에서)

#endif /* INC_UART_H_ */
