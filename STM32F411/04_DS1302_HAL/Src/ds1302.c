/*
 * ds1302.c
 *
 *  Created on: Mar 28, 2025
 *      Author: eec04
 */

#include "ds1302.h"

void ds1302_main(void) {
	init_date_time();
	init_gpio_ds1302();
	init_ds1302();

	while (1) {
		read_time_ds1302();
		read_date_ds1302();
		// 날짜와 시각을 출력
		printf(" %4d-%02d-%02d : %2d:%2d:%2d\n",
				ds1302.year + 2000,
				ds1302.month,
				ds1302.date,
				ds1302.hours,
				ds1302.minutes,
				ds1302.seconds);

		HAL_Delay(1000);
	}
}

void init_date_time(void) {
	ds1302.year = 25;
	ds1302.month = 3;
	ds1302.date = 28;
	ds1302.dayofweek = 6;
	ds1302.hours = 14;
	ds1302.minutes = 45;
	ds1302.seconds = 00;
}

void init_gpio_ds1302(void) {
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 0);
}

void init_ds1302(void) {
	write_ds1302(ADDR_SECONDS, ds1302.seconds);
	write_ds1302(ADDR_MINUTES, ds1302.minutes);
	write_ds1302(ADDR_HOURS, ds1302.hours);
	write_ds1302(ADDR_DATE, ds1302.date);
	write_ds1302(ADDR_MONTH, ds1302.month);
	write_ds1302(ADDR_DAYOFWEEK, ds1302.dayofweek);
	write_ds1302(ADDR_YEAR, ds1302.year);
}

void write_ds1302(uint8_t addr, uint8_t data) {
	// 1. CE Low -> High
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 1);

	// 2. addr Transmission
	tx_ds1302(addr);

	// 3. data Transmission
	tx_ds1302(dec2bcd(data));

	// 4. CE High -> Low
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);
}

void tx_ds1302(uint8_t value) {
	output_dataline_ds1302();

	// 예) addr 초를 write하는
	// 80h M		L
	//     1000 0000 실제값	(B0를 전송시)
	//	   0000 0001 &
	//     0000 0000  ==> HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);

	//     1000 0000 실제값	(B7를 전송시)
	//	   1000 0000 &
	//     1000 0000  ==> HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 1);

	for (int i = 0; i < 8; i++) {
		if (value & (1 << i)) {
			HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 1);
		} else {
			HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 0);
		}
		clock_ds1302();
	}
}

void clock_ds1302(void) {
	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 1);
	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 0);
}

void input_dataline_ds1302(void) {
	GPIO_InitTypeDef GPIO_init = { 0, };

	GPIO_init.Pin = IO_DS1302_Pin;
	GPIO_init.Mode = GPIO_MODE_INPUT;	// INPUT Mode
	GPIO_init.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_init);
}

void output_dataline_ds1302(void) {
	GPIO_InitTypeDef GPIO_init = { 0, };

	GPIO_init.Pin = IO_DS1302_Pin;
	GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;	// OUTPUT Mode
	GPIO_init.Pull = GPIO_NOPULL;
	GPIO_init.Speed = GPIO_SPEED_FREQ_HIGH;	// LOW : 2MHz,	HIGH : 25~100MHz
	HAL_GPIO_Init(GPIOA, &GPIO_init);
}

void read_time_ds1302(void) {
	ds1302.seconds = read_ds1302(ADDR_SECONDS);
	ds1302.minutes = read_ds1302(ADDR_MINUTES);
	ds1302.hours = read_ds1302(ADDR_HOURS);
}

void read_date_ds1302(void) {
	ds1302.date = read_ds1302(ADDR_DATE);
	ds1302.month = read_ds1302(ADDR_MONTH);
	ds1302.dayofweek = read_ds1302(ADDR_DAYOFWEEK);
	ds1302.year = read_ds1302(ADDR_YEAR);
}

uint8_t read_ds1302(uint8_t addr) {
	unsigned char data8bits = 0;	// 1bit씩 넘어온 것을 담을 그릇(변수)
	// 1. CE High
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 1);

	// 2. addr transmission
	tx_ds1302(addr + 1);	// read addr

	// 3. data read
	rx_ds1302(&data8bits);

	// 4. CE Low
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);



	// 5. return (bcd to dec)
	return bcd2dec(data8bits);
}

void rx_ds1302(unsigned char* pdata) {
	unsigned char temp = 0;

	// IO Port를 입력 모드로 전환
	input_dataline_ds1302();

	// DS1302로 부터 들어온 bit를 LSB부터 8bit를 받아서 temp 변수에 저장
	for (int i = 0; i < 8; i++) {
		// 1bit를 읽어 들인다.
		if (HAL_GPIO_ReadPin(GPIOA, IO_DS1302_Pin)) {
			// 1의 조건만 set
			temp |= 1 << i;
		}
		if (i != 7) {
			clock_ds1302();
		}
	}
	*pdata = temp;
}

// 1. Input : bcd
// 예) 2025년의 bcd -> dec
//     7654 3210
//     0010 0101
//        2    5
//      x10   x1
//   -----------
//            25
uint8_t bcd2dec(uint8_t bcd) {
	uint8_t high, low;

	low = bcd & 0x0F;
	high = (bcd >> 4) * 10;

	return (high + low);
}

// dec -> bcd
// 예) 2025년
// dec    	  bcd
// 00011001	  00100101
uint8_t dec2bcd(uint8_t dec) {
	uint8_t high, low;

	high = (dec / 10) << 4;
	low = dec % 10;

	return (high + low);
}
