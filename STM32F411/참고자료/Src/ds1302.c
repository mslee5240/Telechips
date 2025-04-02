/*
 * ds1302.c
 *
 *  Created on: Mar 28, 2025
 *      Author: microsoft
 */

#include "ds1302.h"
#include "extern.h"
#include "i2c_lcd.h"
#include "button.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

t_ds1302 ds1302;
t_ds1302 alarm;


void ds1302_main(void)
{

	void (*display_funcs[])(void) = {
		display_date_time_lcd,
		display_alarm_setting_lcd,
		display_alarm_end_lcd
	};

	static int display_mode = 0;

	i2c_lcd_init();
	init_date_time();
	init_gpio_ds1302();
	init_ds1302();
	init_button_pullup();

	if(is_flash_data())
	{
		read_flash_ds1302();
		printf("read_flash\n");
	}else{
		alarm.magic = 0x55555555;
		alarm.hours = 24;
		alarm.minutes = 0;
		alarm.seconds = 0;
		write_flash_ds1302();
	}

	while(1)
	{

		read_time_ds1302();
		read_date_ds1302();
		pc_command_processing();

		if(get_button(GPIOC, GPIO_PIN_0, BTN_0) == BUTTON_PRESS)
		{
			if(display_mode)
			{
				// setting완료
				write_flash_ds1302();
			}
			display_mode = !display_mode;
			if(display_mode)
			{
				// setting mode
				alarm.hours = alarm.hours > 23 ? 0 : alarm.hours;
			}
		}
		if(get_button(GPIOC, GPIO_PIN_1, BTN_1) == BUTTON_PRESS)
		{
			if(display_mode == 1)
			{
				// setting mode
				alarm.hours++;
				alarm.hours = alarm.hours > 23 ? 23 : alarm.hours;
			}else
			{
				// 알람 울리는중
				display_mode = 0;
			}
		}
		if(get_button(GPIOC, GPIO_PIN_2, BTN_2) == BUTTON_PRESS)
		{
			alarm.minutes++;
			alarm.minutes = alarm.minutes > 59 ? 59 : alarm.minutes;
		}
		if(get_button(GPIOC, GPIO_PIN_3, BTN_3) == BUTTON_PRESS)
		{
			alarm.seconds++;
			alarm.seconds = alarm.seconds > 59 ? 59 : alarm.seconds;
		}

		if(display_mode != 1)
		{
			read_flash_ds1302();
			if(ds1302.hours == alarm.hours && ds1302.minutes == alarm.minutes && ds1302.seconds == alarm.seconds)
			{
				display_mode = 2;
			}
		}

		if(TIM11_1ms_counter > 1000)
		{
			TIM11_1ms_counter = 0;

			display_funcs[display_mode]();
		}
//
		funcs[led_select]();
	}
}

void display_alarm_setting_lcd(void)
{
	char time_string[16];
	char alarm_string[16] = "-ALARM SETTING- ";

	sprintf(time_string, "TIME: %02d:%02d:%02d", alarm.hours, alarm.minutes, alarm.seconds);

	move_cursor(0,0);
	lcd_string(alarm_string);
	move_cursor(1,0);
	lcd_string(time_string);
}

void display_alarm_end_lcd(void)
{
	void (*display_funcs[])(void) = {
		display_alarm_time_lcd,
		display_date_time_lcd
	};

	static int toggle = 0;

	display_funcs[toggle]();

	toggle = !toggle;

}

void display_alarm_time_lcd(void)
{
	char time_string[16];
	char alarm_string[16] = " !!!!!ALARM!!!!!";

	sprintf(time_string, "TIME: %02d:%02d:%02d", ds1302.hours, ds1302.minutes, ds1302.seconds);

	move_cursor(0,0);
	lcd_string(alarm_string);
	move_cursor(1,0);
	lcd_string(time_string);
}

void display_date_time_lcd(void)
{
	char time_string[16];
	char date_string[16];

	sprintf(date_string, "DATE: %4d-%02d-%02d",  ds1302.year + 2000, ds1302.month, ds1302.date);
	sprintf(time_string, "TIME: %02d:%02d:%02d", ds1302.hours, ds1302.minutes, ds1302.seconds);

	move_cursor(0,0);
	lcd_string(date_string);
	move_cursor(1,0);
	lcd_string(time_string);
}

void write_flash_ds1302(void)
{
	flash_erase(); // 기존에 저장했던거 지우기
	//flash_write((uint32_t *)&ds1302, sizeof(t_ds1302));
	flash_write((uint32_t *)&alarm, sizeof(t_ds1302));
}

void read_flash_ds1302(void)
{
	//flash_read((uint32_t *)&ds1302, sizeof(t_ds1302));
	flash_read((uint32_t *)&alarm, sizeof(t_ds1302));
}

void set_rtc(char* daytime)
{
	char str[20];
	char * tmp = str;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.year = atoi(tmp);
	tmp+=2;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.month = atoi(tmp);
	tmp+=2;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.date = atoi(tmp);
	tmp+=2;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.hours = atoi(tmp);
	tmp+=2;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.minutes = atoi(tmp);
	tmp+=2;

	strcpy(str, daytime);
	tmp[2] = 0;
	ds1302.seconds = atoi(tmp);
	tmp+=2;

//	uint8_t *pds = (uint8_t *)&ds1302;
//	int i;
//
//	for(i = 0; i<6; i++)
//	{
//		strcpy(str, daytime);
//		tmp[2] = 0;
//		//*pds = atoi(tmp);
//		*pds = (tmp[0] - 0x30) * 10 + (tmp[1] - 0x30);
//		tmp+=2;
//		pds+=sizeof(uint8_t);
//	}

	init_ds1302();
}

void init_date_time(void)
{
	o_ptr.p_rtc = 1;

	ds1302.magic = 0x55555555;
	ds1302.year = 25;
	ds1302.month = 4;
	ds1302.date = 1;
	ds1302.dayofweek = 6;
	ds1302.hours = 0;
	ds1302.minutes = 0;
	ds1302.seconds = 30;


}

void init_gpio_ds1302(void)
{
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 0);
	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 0);
}

void init_ds1302(void)
{
	write_ds1302(ADDR_SECONDS, ds1302.seconds);
	write_ds1302(ADDR_MINUTES, ds1302.minutes);
	write_ds1302(ADDR_HOURS, ds1302.hours);
	write_ds1302(ADDR_DATE, ds1302.date);
	write_ds1302(ADDR_MONTH, ds1302.month);
	write_ds1302(ADDR_DAYOFWEEK, ds1302.dayofweek);
	write_ds1302(ADDR_YEAR, ds1302.year);
}

void write_ds1302(uint8_t addr, uint8_t data)
{
	// 1. CE LOW -> HIGH
	HAL_GPIO_WritePin(CE_DS1302_GPIO_Port, CE_DS1302_Pin, 1);

	// 2. ADDR
	tx_ds1302(addr);

	// 3. DATA
	tx_ds1302(dec2bcd(data));

	// 4. CE HIGH -> LOW
	HAL_GPIO_WritePin(CE_DS1302_GPIO_Port, CE_DS1302_Pin, 0);
}

uint8_t read_ds1302(uint8_t addr)
{
	uint8_t data8bit = 0;

	// 1. CE LOW -> HIGH
	HAL_GPIO_WritePin(CE_DS1302_GPIO_Port, CE_DS1302_Pin, 1);

	// 2. send ADDR
	tx_ds1302(addr + 1); // read 주소값!!

	// 3. read DATA
	rx_ds1302(&data8bit);

	// 4. CE HIGH -> LOW
	HAL_GPIO_WritePin(CE_DS1302_GPIO_Port, CE_DS1302_Pin, 0);

	// 5. BCD to Decimal
	//			BCD format으로 받아온걸 Decimal로 바꿔서 돌려줘야함
	return bcd2dec(data8bit);

}

uint8_t dec2bcd(uint8_t dec)
{
	uint8_t high, low;

	high = (dec / 10) << 4;
	low = dec % 10;

	return high + low;
}

uint8_t bcd2dec(uint8_t bcd)
{
	// 상위 nibble * 10 + 하위 nibble
	uint8_t high, low;

	low = bcd & 0x0f;
	high = (bcd >> 4) * 10; // masking할 필요 없이, 오른쪽으로 shift시키면 알아서 앞 4개만 잘린다 (빈칸은 0으로 채워지니까)

	return high + low;
}

void tx_ds1302(uint8_t value)
{
	output_dataline_ds1302();		// DDR output 변경
	// ex) tx 0x80 == 0b1000 0000
	//      10xx xxx0 의 x자리에 낑겨넣는다 == 1010 0000
	//		LSB부터 보내는것 주의!!!!
	//		즉 제일 오른쪽부터 마스킹해서 하나씩 보낸다

	for(int i = 0; i<8; i++)
	{
		if(value & (1 << i)) 	HAL_GPIO_WritePin(IO_DS1302_GPIO_Port, IO_DS1302_Pin, 1);
		else 					HAL_GPIO_WritePin(IO_DS1302_GPIO_Port, IO_DS1302_Pin, 0);

		clock_ds1302();

	}
}

void rx_ds1302(uint8_t *pdata)
{
	uint8_t temp = 0;

	input_dataline_ds1302();		// DDR iniput


	for(int i = 0; i<8; i++)
	{
		if(HAL_GPIO_ReadPin(IO_DS1302_GPIO_Port, IO_DS1302_Pin))
		{
			temp |= 1 << i;
		}

		if(i < 7)	clock_ds1302();
	}

	*pdata = temp;
}

void clock_ds1302(void)
{
	HAL_GPIO_WritePin(CLK_DS1302_GPIO_Port, CLK_DS1302_Pin, 1);
	HAL_GPIO_WritePin(CLK_DS1302_GPIO_Port, CLK_DS1302_Pin, 0);
}

void output_dataline_ds1302(void)
{
	GPIO_InitTypeDef GPIO_init = {0, };

	GPIO_init.Pin = IO_DS1302_Pin;
	GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_init.Pull = GPIO_NOPULL;
	GPIO_init.Speed = GPIO_SPEED_FREQ_HIGH; 	// LOW : 2MHz
												// HIGH : 25~100MHz

	HAL_GPIO_Init(IO_DS1302_GPIO_Port, &GPIO_init);
}

void input_dataline_ds1302(void)
{
	GPIO_InitTypeDef GPIO_init = {0, };

	GPIO_init.Pin = IO_DS1302_Pin;
	GPIO_init.Mode = GPIO_MODE_INPUT;
	GPIO_init.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(IO_DS1302_GPIO_Port, &GPIO_init);
}


void read_time_ds1302(void)
{
	ds1302.seconds = read_ds1302(ADDR_SECONDS);
	ds1302.minutes = read_ds1302(ADDR_MINUTES);
	ds1302.hours = read_ds1302(ADDR_HOURS);
}

void read_date_ds1302(void)
{
	ds1302.date = read_ds1302(ADDR_DATE);
	ds1302.month = read_ds1302(ADDR_MONTH);
	ds1302.year = read_ds1302(ADDR_YEAR);
	ds1302.dayofweek = read_ds1302(ADDR_DAYOFWEEK);
}
