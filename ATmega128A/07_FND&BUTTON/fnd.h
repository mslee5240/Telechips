#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_DATA_PORT		PORTC
#define FND_DATA_DDR		DDRC

#define FND_DIGIT_PORT		PORTB
#define FND_DIGIT_DDR		DDRB
#define FND_DIGIT_D1		4
#define FND_DIGIT_D2		5
#define FND_DIGIT_D3		6
#define FND_DIGIT_D4		7

void init_fnd(void);
void fnd_display_1(uint32_t* ms_count, uint32_t* sec_count);
void fnd_display_2(uint32_t* ms_count, uint32_t* sec_count);

#endif /* INCFILE1_H_ */