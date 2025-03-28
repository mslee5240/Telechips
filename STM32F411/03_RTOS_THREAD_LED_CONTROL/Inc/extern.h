/*
 * extern.h
 *
 *  Created on: Mar 26, 2025
 *      Author: eec04
 */

#ifndef INC_EXTERN_H_
#define INC_EXTERN_H_

extern void led_main(void);

extern void button_led_toggle_test(void);
extern int get_button(GPIO_TypeDef* GPIO, int GPIO_Pin, int button_num);


#endif /* INC_EXTERN_H_ */
