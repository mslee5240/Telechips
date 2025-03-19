﻿#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "I2C_LCD.h"

void I2C_LCD_Test()
{ 
	I2C_LCD_init();
	
	uint8_t toggle=0;
	char sbuf[20];
	int i=0;
	
	// TEST_3
	while (1)
	{
		I2C_write_byte(SLA_W, '7');
		I2C_write_byte(SLA_W, '3');
		_delay_ms(1000);
	}
	
	// TEST_1
	//while(1)
	//{	
		//I2C_LCD_write_string_XY(0,0,"Hello !!!"); //개행문자 쓰지마.
		//I2C_LCD_write_string_XY(1,0,"MSLEE");
		//_delay_ms(100); //프로토콜에 의해 실행되므로, 데이터를 다 받을때까지 기다려야한다.
	//}
	
	// TEST_2
	//while(1)
	//{
		//toggle = !toggle;
		//i++;
		//i %= 100;
		//sprintf(sbuf, "%3d", i);	// ASCII 문자로 변환하는 방법!
		//I2C_LCD_clear();
		//if (toggle)
		//{
			//I2C_LCD_write_string_XY(0,0,"hello !!!"); //개행문자 쓰지마.
		//}
		//else
		//{
			//I2C_LCD_write_string_XY(0,0,"MSLEE "); //개행문자 쓰지마.
		//}
		//I2C_LCD_write_string_XY(0,10,sbuf);
		//
		//_delay_ms(1000);		// 안정화 시간 필수
	//}
}
// 1byte를 write
void I2C_LCD_write_data(uint8_t data)
{
	char data_u, data_l;
	uint8_t data_t[4] = {0,};
		
	data_u = (data&0xf0);      // 상위 4bit 데이터
	data_l = ((data<<4)&0xf0); // 하위 4bit 데이터
	data_t[0] = data_u|0x0D;   //en=1, rs=1           |D7|D6|D5|D4|X|E|RW|RS|
	data_t[1] = data_u|0x09;   //en=0, rs=1
	data_t[2] = data_l|0x0D;   //en=1, rs=1
	data_t[3] = data_l|0x09;   //en=0, rs=1

	for(char i=0;i<4;i++){
		I2C_write_byte(SLA_W, data_t[i]);
	}
}

void I2C_LCD_write_command(uint8_t command)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (command&0xf0);      // command의 상위 4bit 저장
	data_l = ((command<<4)&0xf0); // command의 하위 4bit 저장
	data_t[0] = data_u|0x0C;  //en=1, rs=0           |D7|D6|D5|D4|X|E|RW|RS|
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	
	for(char i=0;i<4;i++){
		I2C_write_byte(SLA_W, data_t[i]);
	}
}

// 화면 clear
// 화면에 있는 내용만 지운다. 
void I2C_LCD_clear(void)
{
	I2C_LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

// LCD를 초기화
void I2C_LCD_init(void)
{
	I2C_init(10000);
	_delay_ms(50);
	//Initialization of HD44780-based LCD (4-bit HW)
	I2C_LCD_write_command(0x33);
	I2C_LCD_write_command(0x32);
	I2C_LCD_write_command(0x28);   //Function Set 4-bit mode
	I2C_LCD_write_command(0x0c);   //Display On/Off Control
	I2C_LCD_write_command(0x06);   //Entry mode set
	I2C_LCD_write_command(0x01);   //Clear Display
	//Minimum delay to wait before driving LCD module
	_delay_ms(10);
}
// 현재의 xy좌표에 printf처럼 스트링 값을 출력 
void I2C_LCD_write_string(char *string)
{
	uint8_t i;
	for(i=0; string[i]; i++) //"hello !!\0" 마지막 널문자에서 조건 거짓이 되어 빠져나온다.
	I2C_LCD_write_data(string[i]);
}

// 커서를 x,y좌표로 이동
void I2C_LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	I2C_LCD_write_command(command);
}

// x,y좌표로 이동을 하고 string값을 출력 한다. 
void I2C_LCD_write_string_XY(uint8_t row, uint8_t col, char *string)
{
	I2C_LCD_goto_XY(row, col);
	I2C_LCD_write_string(string);
}