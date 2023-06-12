/*
 * DRV_PWM.c
 *
 *  Created on: June 12, 2023
 *      Author: R.Lin
 */

#include "DRV_PWM.h"

/**
  * @brief  Start PWM channel
  * @note	Duty cycle is set to 0%
  */
void PWM_Start(){
	TIM3->CCR1 = 0;
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

/**
  * @brief  Stop PWM channel
  * @note	Duty cycle is set to 0%
  */
void PWM_Stop(){
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	TIM3->CCR1 = 0;
}

/**
  * @brief  Set PWM channel to High Z or to PWM control
  * @warn	As soon as the channel is back to PWM control, the latest duty cycle is used
  * @param state true = high Z, false = PWM control
  */
void PWM_HZ(bool state) {
	// set to high Z
	if (state) TIM3->CCER = TIM3->CCER & 0xFFFFFFFE; // set Capture/compare 1 output enable bit to 0
	// set to PWM control
	else TIM3->CCER = TIM3->CCER | 0x1; // set Capture/compare 1 output enable bit to 1
}


/**
  * @brief  set PWM channel duty cycle
  * @param  float DC
  * 		Duty cycle set in percent
  * 		This parameter can be a value between 0.0 and 100.0
  */
void PWM_Set_DutyCycle(float DC){
	uint32_t CCR = 0;

	// make sure the input value is clamped between 0 and 100
	if((DC >= 0.0) | (DC <= 100.0)) CCR = htim3.Init.Period * DC * 0.01;

	// write to register
	TIM3->CCR1 = CCR;
}

/**
  * @brief  set PWM channel frequency
  * @param  float freq
  * 		freq set in Hz
  * 		This parameter can be a value between 100 and 8000
  */
void PWM_Set_Frequency(float freq){

}
