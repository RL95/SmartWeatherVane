/*
 * drv_timer_callback.c
 *
 *  Created on: Aug 20, 2022
 *      Author: R.Lin
 */

#include "DRV_timer_callback.h"

bool CALLBACK_FLAG = 0;

/**
  * @brief  start the timer interrupt counter
  * @note	TIMER 2, 15 and 3 that are configured
  * 		to call the interrupt routing @ 10kHz, 1kHz and 100Hz
  * 		with internal clock at 170MHz ARR was set to 17000
  * 		TIMER 2  -> 170MHz / ARR = 10kHz with Prescaler of 1
  * 		TIMER 15 -> 170MHz / ARR = 1kHz  with Prescaler of 10
  * 		TIMER 3  -> 170MHz / ARR = 100Hz with Prescaler of 100
  */
void Timer_Callback_START(){
	// start callback timer
	HAL_TIM_Base_Start_IT(&htim10);
}

/**
  * @brief  Timer period elapsed callback routing definition
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// run callback
	if(htim == &htim10) Timer_Callback();
}
