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
	TMC_DIS_DRV;
}

void TMC_test_run(){
	TMC_EN_DRV;
	TMC_DIR_CW;
	for (uint16_t i = 0; i < 200; i++) {
		TMC_STEP_H;
		HAL_Delay(10);
		TMC_STEP_L;
		HAL_Delay(10);
	}
	TMC_DIR_CCW;
	for (uint16_t i = 0; i < 200; i++) {
		TMC_STEP_H;
		HAL_Delay(10);
		TMC_STEP_L;
		HAL_Delay(10);
	}
	TMC_DIS_DRV;

}
