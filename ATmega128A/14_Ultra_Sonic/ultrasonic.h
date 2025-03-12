#define F_CPU   16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIG		4
#define TRIG_PORT	PORTG
#define TRIG_DDR	DDRG

#define ECHO		4
#define ECHO_PIN	PINE	// External INT 4
#define ECHO_DDR	DDRE

void init_ultrasonic(void);
void trigger_ultrasonic(void);
void distance_ultrasonic(void);

