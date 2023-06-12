/*
 * DRV_TMC2660.c
 *
 *  Created on: Jun 6, 2023
 *      Author: R.Lin
 */

#include "DRV_TMC2660.h"

/**
 * @brief Initialiser Sets up the SPI interface
 */
void TMC_init(TMC *PMSM){
	TMC_DIS_SPI;
	TMC_DIS_DRV;
	TMC_DIR_CW;
	TMC_STEP_L;
}

int t = 1;

void TMC_test_run(){
	TMC_EN_DRV;
	TMC_DIR_CW;

	PWM_Start();
	PWM_Set(700, 50);
	HAL_Delay(2000);
	PWM_Stop();

	TMC_DIR_CCW;

	PWM_Start();
	PWM_Set(700, 50);
	HAL_Delay(2000);
	PWM_Stop();


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
