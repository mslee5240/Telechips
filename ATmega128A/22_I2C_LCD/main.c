#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "uart0.h"
#include "uart1.h"
#include "I2C.h"
#include "I2C_LCD.h"

// stdout에 UART0_transmit을 연결하여
// printf()로 UART 송신을 할 수 있도록 설정
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE); // For printf()

int main(void)
{
	init_uart0();
	init_uart1();

	// 표준 출력(stdout)을 UART0의 OUTPUT 스트림에 연결
	stdout = &OUTPUT;

	// 전역 인터럽트 허용
	sei();

	I2C_LCD_Test();
	
	while (1)
	{
		
	}
	
	return 0;
}
