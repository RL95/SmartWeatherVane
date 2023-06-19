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
  * @note	TIMER 10 and 11 are configured
  * 		to call the interrupt routing @ 10Hz and 10kHz
  */
void Timer_Callback_START(){
	// start callback timer
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim11);
}

/**
  * @brief  Timer period elapsed callback routing definition
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// run callback
	if(htim == &htim10) Timer_Callback_10Hz();
	if(htim == &htim11) Timer_Callback_10kHz();
}
