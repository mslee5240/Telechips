/*
 * ds1302.c
 *
 * DS1302 RTC를 제어하는 인터페이스 코드.
 * DS1302의 초기화, 데이터 읽기/쓰기 기능을 제공.
 *
 *  Created on: Mar 28, 2025
 *      Author: eec04
 */

#include "ds1302.h"

// DS1302 RTC 초기화 및 지속적으로 시간 업데이트를 수행하는 메인 함수
void ds1302_main(void) {
	t_ds1302 ds1302;

	init_date_time(&ds1302);	// ds1302 구조체에 기본 날짜와 시간 설정
	init_gpio_ds1302();			// DS1302 통신용 GPIO 핀 초기화
	init_ds1302(&ds1302);				// DS1302 레지스터에 초기 시간 설정 값을 기록

	while (1) {
//		read_time_ds1302(&ds1302);		// DS1302에서 시간(초, 분, 시) 읽기
		read_date_ds1302(&ds1302);		// DS1302에서 날짜(일, 월, 요일, 연도) 읽기

		// 현재 날짜와 시간을 YYYY-MM-DD HH:MM:SS 형식으로 출력
		printf(" %4d-%02d-%02d : %2d:%2d:%2d\n",
				ds1302.year + 2000,
				ds1302.month,
				ds1302.date,
				ds1302.hours,
				ds1302.minutes,
				ds1302.seconds);

		HAL_Delay(1000);	// 1초 딜레이
	}
}

// ds1302 구조체에 기본 날짜와 시간 값을 초기화.
void init_date_time(t_ds1302* ds) {
	ds->year = 25;			// 연도 (예: 2025년 -> 25)
	ds->month = 3;
	ds->date = 28;
	ds->dayofweek = 6;		// 요일 (1: 일요일, ..., 6: 금요일)
	ds->hours = 14;			// 시 (24시간제)
	ds->minutes = 45;
	ds->seconds = 0;
}

// DS1302 통신용 GPIO 핀(CE, IO, CLK)을 초기 상태(LOW)로 설정.
void init_gpio_ds1302(void) {
//	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0); 	// PA10
//	HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 0);		// PA11
//	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 0);	// PA12

	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR &= ~(1 << 10 | 1 << 11 | 1 << 12);
}

// DS1302에 날짜와 시간 데이터를 기록하여 초기화.
void init_ds1302(t_ds1302* ds) {
	write_ds1302(ADDR_SECONDS, ds->seconds);
	write_ds1302(ADDR_MINUTES, ds->minutes);
	write_ds1302(ADDR_HOURS, ds->hours);
	write_ds1302(ADDR_DATE, ds->date);
	write_ds1302(ADDR_MONTH, ds->month);
	write_ds1302(ADDR_DAYOFWEEK, ds->dayofweek);
	write_ds1302(ADDR_YEAR, ds->year);
}

// DS1302의 특정 레지스터에 데이터를 기록
// @param addr : 쓰기 모드 레지스터 주소
// @param data : 10진수 데이터 (BCD로 변환되어 전송됨)
void write_ds1302(uint8_t addr, uint8_t data) {
	// 1. 통신 시작: CE를 HIGH로 설정
//	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 1);		// PA10
	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR |= 1 << 10;

	// 2. 레지스터 주소 전송 (쓰기 명령)
	tx_ds1302(addr);

	// 3. 데이터를 BCD 형식으로 변환 후 전송
	tx_ds1302(dec2bcd(data));

	// 4. 통신 종료: CE를 LOW로 설정
//	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);		// PA10
	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR &= ~(1 << 10);
}

// DS1302에 1바이트 데이터를 LSB부터 전송.
// @param value : 전송할 1바이트 값
void tx_ds1302(uint8_t value) {
	// IO 핀을 출력 모드로 설정
	output_dataline_ds1302();

	// 8비트를 LSB부터 순차적으로 전송
	for (int i = 0; i < 8; i++) {
		if (value & (1 << i)) {
//			HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 1);		// PA11
			// [DMA 방식으로 대체]
			*(uint32_t*)GPIOA_ODR |= 1 << 11;
		} else {
//			HAL_GPIO_WritePin(GPIOA, IO_DS1302_Pin, 0);		// PA11
			// DMA 방식으로 대체
			*(uint32_t*)GPIOA_ODR &= ~(1 << 11);
		}
		clock_ds1302(); // 각 비트 전송 후 클럭 펄스 발생
	}
}

// DS1302 클럭 라인을 토글하여 클럭 펄스를 생성.
void clock_ds1302(void) {
//	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 1);		// PA12
//	HAL_GPIO_WritePin(GPIOA, CLK_DS1302_Pin, 0);		// PA12

	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR |= 1 << 12;
	*(uint32_t*)GPIOA_ODR &= ~(1 << 12);
}

// DS1302 IO 핀을 입력 모드로 설정.
// DS1302로부터 데이터를 읽을 때 사용.
void input_dataline_ds1302(void) {
//	GPIO_InitTypeDef GPIO_init = { 0, };
//
//	GPIO_init.Pin = IO_DS1302_Pin;		// PA11
//	GPIO_init.Mode = GPIO_MODE_INPUT;	// 입력 모드
//	GPIO_init.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOA, &GPIO_init);

	// [DMA 방식으로 대체]
	// 초기화 시작 (설정과 똑같지만 쉽게 이해하기 위해 작성)
	*(uint32_t*)GPIOA_MODER &= ~(0b11 << (11 * 2));		// 입력 모드(00)
	*(uint32_t*)GPIOA_PUPDR &= ~(0b11 << (11 * 2));		// No Pull(00)

	// 설정 시작
	*(uint32_t*)GPIOA_MODER &= ~(0b11 << (11 * 2));		// 입력 모드(00)
	*(uint32_t*)GPIOA_PUPDR &= ~(0b11 << (11 * 2));		// No Pull(00)
}

// DS1302 IO 핀을 푸시풀 출력 모드로 설정
// DS1302에 데이터를 전송할 때 사용
void output_dataline_ds1302(void) {
//	GPIO_InitTypeDef GPIO_init = { 0, };
//
//	GPIO_init.Pin = IO_DS1302_Pin;			// PA11
//	GPIO_init.Mode = GPIO_MODE_OUTPUT_PP;	// 푸시풀 출력 모드
//	GPIO_init.Pull = GPIO_NOPULL;
//	GPIO_init.Speed = GPIO_SPEED_FREQ_HIGH;	// LOW : 2MHz,	HIGH : 25~100MHz
//	HAL_GPIO_Init(GPIOA, &GPIO_init);

	// [DMA 방식으로 대체]
	// 초기화 시작
	*(uint32_t*)GPIOA_MODER &= ~(0b11 << (11 * 2));
	*(uint32_t*)GPIOA_OTYPER &= ~(1 << 11);
	*(uint32_t*)GPIOA_PUPDR &= ~(0b11 << (11 * 2));
	*(uint32_t*)GPIOA_OSPEEDR &= ~(0b11 << (11 * 2));

	// 설정 시작
	*(uint32_t*)GPIOA_MODER |= 0b01 << (11 * 2);		// 출력 모드(01)
	*(uint32_t*)GPIOA_OTYPER &= ~(1 << 11);				// push-pull(0)
	*(uint32_t*)GPIOA_PUPDR &= ~(0b11 << (11 * 2));		// No Pull(00)
	*(uint32_t*)GPIOA_OSPEEDR |= 0b11 << (11 * 2);		// High speed(11)
}

// DS1302에서 시간(초, 분, 시)을 읽어 ds1302 구조체에 업데이트
void read_time_ds1302(t_ds1302* ds) {
	ds->seconds = read_ds1302(ADDR_SECONDS);
	ds->minutes = read_ds1302(ADDR_MINUTES);
	ds->hours = read_ds1302(ADDR_HOURS);
}

// DS1302에서 날짜(일, 월, 요일, 연도)를 읽어 ds1302 구조체에 업데이트
void read_date_ds1302(t_ds1302* ds) {
	ds->date = read_ds1302(ADDR_DATE);
	ds->month = read_ds1302(ADDR_MONTH);
	ds->dayofweek = read_ds1302(ADDR_DAYOFWEEK);
	ds->year = read_ds1302(ADDR_YEAR);
}

// DS1302의 특정 레지스터로부터 데이터를 읽는다.
// @param addr : 쓰기 모드 주소 (읽기 시 addr+1 사용)
// @return : BCD 형식 데이터를 10진수로 변환한 값
uint8_t read_ds1302(uint8_t addr) {
	unsigned char data8bits = 0;

	// 1. 통신 시작: CE를 HIGH로 설정
//	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 1);		// PA10
	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR |= 1 << 10;

	// 2. 읽기용 주소 전송 (addr+1)
	tx_ds1302(addr + 1);	// read addr

	// 3. DS1302로부터 데이터 수신
	rx_ds1302(&data8bits);

	// 4. 통신 종료: CE를 LOW로 설정
	HAL_GPIO_WritePin(GPIOA, CE_DS1302_Pin, 0);
	// [DMA 방식으로 대체]
	*(uint32_t*)GPIOA_ODR &= ~(1 << 10);

	// 5. 수신한 BCD 데이터를 10진수로 변환 후 반환
	return bcd2dec(data8bits);
}

// DS1302로부터 1바이트 데이터를 LSB부터 수신.
// @param pdata : 수신한 데이터를 저장할 포인터
void rx_ds1302(uint8_t* pdata) {
	uint8_t temp = 0;

	// 데이터를 수신하기 위해 IO 핀을 입력 모드로 전환
	input_dataline_ds1302();

	// 8비트를 LSB부터 순차적으로 수신
	for (int i = 0; i < 8; i++) {
		// 현재 비트를 읽어온 후 temp 변수에 저장
//		if (HAL_GPIO_ReadPin(GPIOA, IO_DS1302_Pin)) {	// PA11
//			temp |= 1 << i;
//		}
		// [DMA 방식으로 대체]
		if (*(uint32_t*)GPIOA_IDR & (1 << 11)) {
			temp |= 1 << i;
		}

		// 각 비트마다 클럭 펄스 생성 (마지막 비트 제외)
		if (i != 7) {
			clock_ds1302();
		}
	}
	*pdata = temp;
}

// BCD 형식의 값을 10진수로 변환.
// @param bcd : BCD 인코딩 값
// @return : 10진수 값
// 예: 0x25 (0010 0101)는 25로 변환
uint8_t bcd2dec(uint8_t bcd) {
	uint8_t high, low;

	low = bcd & 0x0F;			// 하위 4비트: 1의 자리
	high = (bcd >> 4) * 10;		// 상위 4비트: 10의 자리

	return (high + low);
}

// 10진수 값을 BCD 형식으로 변환.
// @param dec : 10진수 값 (0~99)
// @return BCD : 인코딩 값
// 예: 25는 0x25로 변환
uint8_t dec2bcd(uint8_t dec) {
	uint8_t high, low;

	high = (dec / 10) << 4;		// 10의 자리 값을 상위 4비트로 이동
	low = dec % 10;				// 1의 자리

	return (high + low);
}
