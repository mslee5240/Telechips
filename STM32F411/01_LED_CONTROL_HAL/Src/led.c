#include "led.h"

void led_all_on(void) {
//	HAL_GPIO_WritePin(GPIOB, 0xFF, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
							 GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 1);
}

void led_all_off(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
								 GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, 0);
}

void led_main(void) {
	while (1) {
//		led_all_on();
//		HAL_Delay(50);
//		led_all_off();
//		HAL_Delay(50);

		shift_left_led_on();
		shift_right_led_on();
		shift_left_keep_led_on();
		shift_right_keep_led_on();
		flower_on();
		flower_off();
	}
}

void shift_left_led_on(void) {
	int pin = GPIO_PIN_0;

	for (int i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOB, pin << i, 1);
		HAL_Delay(200);
		led_all_off();
	}
}

void shift_right_led_on(void) {
	int pin = GPIO_PIN_7;

	for (int i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOB, pin >> i, 1);
		HAL_Delay(200);
		led_all_off();
	}
}

void shift_left_keep_led_on(void) {
	int pin = GPIO_PIN_0;

	for (int i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOB, pin << i, 1);
		HAL_Delay(200);
	}
	led_all_off();
}

void shift_right_keep_led_on(void) {
	int pin = GPIO_PIN_7;

	for (int i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(GPIOB, pin >> i, 1);
		HAL_Delay(200);
	}
	led_all_off();
}

void flower_on(void) {
	int pin = GPIO_PIN_3 | GPIO_PIN_4;

	for (int i = 0; i < 3; i++) {
		HAL_GPIO_WritePinS(GPIOB, pin, 1);
		HAL_Delay(200);
		pin = pin >> 1 | pin << 1;
	}
	led_all_off();
}

void flower_off(void) {
    int pin = 0xFF;

    for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(GPIOB, pin, 1);
        HAL_Delay(200);
        pin &= ~((1 << i) | (1 << (7 - i)));
        led_all_off();
    }

    led_all_off();
}
