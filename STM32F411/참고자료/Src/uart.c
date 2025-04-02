/*
 * uart.c
 *
 *  Created on: Mar 31, 2025
 *      Author: microsoft
 */

#include "uart.h"
#include "extern.h"
#include <string.h>
#include <stdio.h>



t_print o_ptr;

void pc_command_processing(void);

int led_select = 0;


/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  *
  * move from stm32f4xx_hal_uart.c
  * comportmaster로부터 char한개를 받으면, 요 함수로 들어온다.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	volatile static int i = 0;	// buffer의 index

//	rx_data = UDR0; // uart0 하드웨어로 들어온 문자 읽어오기
//					// 이렇게 assign연산자로 UDR0값을 읽어오는 순간, UDR0는 empty가됨 (자동)

	if(huart == &huart2)
	{
		if(rx_data == '\n')
		{
			rx_buff[rear++][i] = 0; // 문장의 끝은 항상 0
			rear %= COMMAND_NUMBER; // 원형큐
			i = 0; // 새로오는건 버퍼에 새롭게 채워야함 (다른 메시지니까!)

			// 큐 full 여부 확인
		}
		else
		{
			// 그냥 버퍼에 넣기 (push)
			rx_buff[rear][i++] = rx_data;
			// command length 확인
		}
	}


	HAL_UART_Receive_IT(&huart2, &rx_data, 1); // 다음 interrupt를 위한 준비
}



void show_commands(void)
{
	int i;

	char *cmd[] = {
			"setrtc",
			"print_rtc",
			"printoff_rtc",
			"help"
	};

	for(i = 0; i<4; i++){
		printf("%s\n", cmd[i]);
	}
}

void pc_command_processing(void)
{
	if(front != rear)
	{
		printf("uart2 :%s\n", (char *)rx_buff[front]);

		if(strncmp((const char *)rx_buff[front], "setrtc", strlen("setrtc")) == 0)
		{
			printf(">> %s\n", (char *)rx_buff[front]);
			set_rtc((char *)rx_buff[front] + 6);
		}else if(strncmp((const char *)rx_buff[front], "help", strlen("help")) == 0)
		{
			show_commands();
		}
		else if(strncmp((const char *)rx_buff[front], "print_rtc", strlen("print_rtc")) == 0)
		{
			o_ptr.p_rtc = 1;
			printf("print_rtc : %d\n", o_ptr.p_rtc);
		}
		else if(strncmp((const char *)rx_buff[front], "printoff_rtc", strlen("printoff_rtc")) == 0)
		{
			o_ptr.p_rtc = 0;
			printf("print_rtc : %d\n", o_ptr.p_rtc);
		}
		else{
			for(int i = 0; i<8; i++){
				if(strncmp((const char *)rx_buff[front], func_names[i], strlen(func_names[i])) == 0)
				{
					printf("uart0 find: %s\n", func_names[i]);
					led_select = i;
					break;
				}
			}
		}


		front++;
		front %= COMMAND_NUMBER;
	}
}
