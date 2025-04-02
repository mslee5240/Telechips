/*
 * ds1302.h
 *
 *  Created on: Mar 28, 2025
 *      Author: microsoft
 */

#ifndef INC_DS1302_H_
#define INC_DS1302_H_

#include "main.h"		// HAL, GPIO

#define ADDR_SECONDS	0x80	// second write addr
								// read addr = write addr + 1 = ADDR_SECONDS + 1
#define ADDR_MINUTES		0x82
#define ADDR_HOURS			0x84
#define ADDR_DATE			0x86
#define ADDR_MONTH			0x88
#define ADDR_DAYOFWEEK		0x8A
#define ADDR_YEAR			0x8C
#define ADDR_WRITEPROTECTED	0x8e

typedef struct s_ds1302{
	uint32_t magic;
	uint8_t year;
	uint8_t month;
	uint8_t date;
	uint8_t hours;			// hour
	uint8_t minutes;		//min
	uint8_t seconds;		//sec
	uint8_t dayofweek;		// 1 : SUN, 2 : MON ....
	uint8_t ampm;			// 1 : pm, 0 : am
	uint8_t hourmode;		// 0 : 24h, 1 : 12h
	uint8_t dummy[3];		// dalignment 맞추기
}t_ds1302;

extern t_ds1302 ds1302;

void ds1302_main(void);

void display_date_time_lcd(void);
void display_alarm_setting_lcd(void);
void display_alarm_end_lcd(void);
void display_alarm_time_lcd(void);


void set_rtc(char* daytime);

void write_flash_ds1302(void);
void read_flash_ds1302(void);

void init_date_time(void);
void init_gpio_ds1302(void);
void init_ds1302(void);
void write_ds1302(uint8_t addr, uint8_t data);
uint8_t read_ds1302(uint8_t addr);
uint8_t dec2bcd(uint8_t dec);
uint8_t bcd2dec(uint8_t bcd);
void tx_ds1302(uint8_t value);
void rx_ds1302(uint8_t *pdata);
void clock_ds1302(void);
void output_dataline_ds1302(void);
void input_dataline_ds1302(void);
void read_time_ds1302(void);
void read_date_ds1302(void);

#endif /* INC_DS1302_H_ */
