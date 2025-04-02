/*
 * extern.h
 *
 *  Created on: Mar 26, 2025
 *      Author: microsoft
 */

#ifndef INC_EXTERN_H_
#define INC_EXTERN_H_

extern uint8_t rx_data;
extern UART_HandleTypeDef huart2;
extern char *func_names[];
extern void (*funcs[])(void);
extern int led_select;
extern volatile int TIM11_1ms_counter;
extern t_print o_ptr;
extern TIM_HandleTypeDef htim2;

extern void led_main(void);
extern void button_toggle_test(void);
extern void ds1302_main(void);
extern void pc_command_processing(void);

extern void set_rtc(char* daytime);
extern void delay_us(int us);

extern void flash_main();
extern HAL_StatusTypeDef flash_read(uint32_t *addr32, int size);
extern HAL_StatusTypeDef flash_write (uint32_t *data32, int size);
extern HAL_StatusTypeDef flash_erase();
extern int is_flash_data(void);

extern void i2c_lcd_main(void);

#endif /* INC_EXTERN_H_ */
