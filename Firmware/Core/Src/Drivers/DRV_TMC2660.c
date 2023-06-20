/*
 * DRV_TMC2660.c
 *
 *  Created on: Jun 6, 2023
 *      Author: R.Lin
 */

#include "DRV_TMC2660.h"
#include "../FSM.h"

int t = 1;
float current_freq = MIN_FREQ;

/**
 * @brief Initialiser Sets up the SPI interface
 */
void TMC_init(TMC *PMSM){
	TMC_DIS_SPI;
	TMC_DIS_DRV;
	TMC_DIR_CW;
	TMC_STEP_L;
}

void TMC_move_to(float target_angle, float current_angle, float maxfreq){
	// compute error
	float error = target_angle - current_angle;
	if(abs(error) > 1.0){
		//choose rotation direction (angle increase when rotating clockwise)
		if(error >= 0) {
			TMC_DIR_CW;
		}
		else {
			TMC_DIR_CCW;
		}
		// start driver
		PWM_Start();
		TMC_EN_DRV;
		// accelerate motor
		PWM_Set(current_freq, PWM_DUTY);
		if(current_freq < maxfreq)current_freq ++;
	}
	else{
		TMC_DIS_DRV;
		PWM_Stop();
		current_freq = MIN_FREQ;
	}


}


void TMC_test_run(){
	TMC_EN_DRV;
	TMC_DIR_CW;

	PWM_Start();
	for (int i = 20; i < 10000; i += 10){
		PWM_Set(i, 50);
		HAL_Delay(1);
	}
	HAL_Delay(10000);
	for (int i = 8000; i > 20; i -= 10){
		PWM_Set(i, 50);
		HAL_Delay(1);
	}
	PWM_Stop();
/*
	PWM_Start();
	PWM_Set(800, 50);
	HAL_Delay(10000);
	PWM_Stop();

	TMC_DIR_CCW;

	PWM_Start();
	PWM_Set(600, 50);
	HAL_Delay(10000);
	PWM_Set(100, 50);
	HAL_Delay(10000);
	PWM_Set(20, 50);
	HAL_Delay(10000);
	PWM_Stop();
*/

	/*
	for (uint16_t i = 0; i < 200 * MICROSTEPPING_SIZE; i++) {
		TMC_STEP_H;
		HAL_Delay(t);
		TMC_STEP_L;
		HAL_Delay(t);
	}
	TMC_DIR_CCW;
	for (uint16_t i = 0; i < 200 * MICROSTEPPING_SIZE; i++) {
		TMC_STEP_H;
		HAL_Delay(t);
		TMC_STEP_L;
		HAL_Delay(t);
	*/
	TMC_DIS_DRV;
	TMC_DIR_CW;

}
