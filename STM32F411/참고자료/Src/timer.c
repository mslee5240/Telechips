/*
 * timer.c
 *
 *  Created on: Mar 31, 2025
 *      Author: microsoft
 */


#include "timer.h"
#include "extern.h"

void delay_us(int us)
{
	// 카운터 reset
	__HAL_TIM_SET_COUNTER(&htim2, 0);

	// us동안 기다림
	while(__HAL_TIM_GET_COUNTER(&htim2) < us) ;

}
