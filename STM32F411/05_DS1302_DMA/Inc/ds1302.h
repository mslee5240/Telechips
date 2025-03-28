/*
 * ds1302.h
 *
 * DS1302 RTC 인터페이스를 위한 헤더 파일.
 *
 *  Created on: Mar 28, 2025
 *      Author: eec04
 */

#ifndef INC_DS1302_H_
#define INC_DS1302_H_

#include "main.h"	// HAL 및 GPIO 정의 포함

// 레지스터에 직접 접근하기 위함
#define GPIOA_MODER  	0x40020000		// mode register
#define GPIOA_OTYPER	0x40020004		// output type register
#define GPIOA_OSPEEDR	0x40020008		// output speed register
#define GPIOA_IDR		0x40020010		// input data register
#define GPIOA_PUPDR		0x4002000C		// pull-up/pull-down register
#define GPIOA_ODR  		0x40020014		// output data register


// DS1302 쓰기 모드 레지스터 주소 (읽기 주소는 쓰기 주소에 +1)
#define ADDR_SECONDS			0x80
#define ADDR_MINUTES			0x82
#define ADDR_HOURS				0x84
#define ADDR_DATE				0x86
#define ADDR_MONTH				0x88
#define ADDR_DAYOFWEEK 			0x8A
#define ADDR_YEAR				0x8C
#define ADDR_WRITEPROTECTED		0x8E	// 쓰기 보호 레지스터 (현재 코드에서 사용하지 않음)

typedef struct s_ds1302 {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t date;
	uint8_t month;
	uint8_t dayofweek;	// 1: sun, 		2: mon ...
	uint8_t year;
	uint8_t ampm;		// 1: PM, 		0 : AM
	uint8_t hourmode;	// 1: 12h mode, 0: 24h mode
} t_ds1302;

// 함수 프로토타입
void ds1302_main(void);
void init_date_time(t_ds1302* ds);
void init_gpio_ds1302(void);
void init_ds1302(t_ds1302* ds);
void write_ds1302(uint8_t addr, uint8_t data);
void tx_ds1302(uint8_t value);
void clock_ds1302(void);
void input_dataline_ds1302(void);
void output_dataline_ds1302(void);
void read_time_ds1302(t_ds1302* ds);
void read_date_ds1302(t_ds1302* ds);
uint8_t read_ds1302(uint8_t addr);
void rx_ds1302(uint8_t* pdata);
uint8_t bcd2dec(uint8_t bcd);
uint8_t dec2bcd(uint8_t dec);








#endif /* INC_DS1302_H_ */
