/*
 * drv_timer_callback.h
 *
 *  Created on: Aug 20, 2022
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_TIMER_CALLBACK_H_
#define SRC_DRIVERS_DRV_TIMER_CALLBACK_H_

#include "../SmartWeatherVane_main.h"

void Timer_Callback_START();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

extern TIM_HandleTypeDef htim10;

extern void Timer_Callback();

extern bool CALLBACK_FLAG;

#endif /* SRC_DRIVERS_DRV_TIMER_CALLBACK_H_ */
