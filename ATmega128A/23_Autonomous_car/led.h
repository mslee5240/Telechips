#include <avr/io.h>

#define AUTO_RUN_LED_PORT		PORTG
#define AUTO_RUN_LED_PORT_DDR	DDRG
#define AUTO_RUN_LED_PIN		2


void init_led(void);

