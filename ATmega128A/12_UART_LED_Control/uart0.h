#ifndef UART0_H_
#define UART0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "def.h"

/*
 * rx_buff:
 * - [COMMAND_NUMBER][COMMAND_LENGTH] 크기의 2차원 배열
 * - 한 줄(문자열)씩 수신할 때마다 rear 인덱스가 가리키는 곳에 저장
 * - pc_command_processing()에서 front 인덱스를 통해 꺼내 감
*/
volatile uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];

// 큐의 삽입 및 추출 인덱스
volatile int rear;	// 데이터가 새로 들어갈 위치
volatile int front;	// 아직 처리하지 않은 데이터를 꺼낼 위치

// 필요 시 '\n' 기반 메시지 완료 플래그
volatile uint8_t rx_msg_received;

// UART 초기화, 송신, PC 명령 처리 함수
void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);


#endif /* UART0_H_ */