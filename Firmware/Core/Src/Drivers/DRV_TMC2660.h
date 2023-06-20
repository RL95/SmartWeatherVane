/*
 * DRV_TMC2660.h
 *
 *  Created on: Jun 6, 2023
 *      Author: ruili
 */

#ifndef SRC_DRIVERS_DRV_TMC2660_H_
#define SRC_DRIVERS_DRV_TMC2660_H_

#include "main.h"

// ####### specifications for 103H7823-5740 #######
#define HOLDING_TORQUE		2.7f		// Nm
#define RATED_CURRENT		2.0f		// A
#define WINDING_RESISTANCE	2.4f		// ohm/phase
#define WINDING_INDUCTANVE	9.5f		// mH/phase
#define ROTOR_INERTIA		0.000084f	// kg*m^2
#define STEP_SIZE			1.8f		// deg
#define STEP_NUMBER			200.0f		// step/revolution
#define MIN_FREQ			20.0f		// Hz
#define MAX_SELF_START_FREQ	800.0f		// Hz (when motor not loaded and in full-step mode)
#define MICROSTEPPING_SIZE	16.0f		// Step size is multiplied by this factor
#define PWM_DUTY			50.0f		// fixed step signal duty cycle


// GPIO macros
#define TMC_EN_SPI HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);
#define TMC_DIS_SPI HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);

#define TMC_EN_DRV HAL_GPIO_WritePin(TMC_EN_GPIO_Port, TMC_EN_Pin, GPIO_PIN_RESET);
#define TMC_DIS_DRV HAL_GPIO_WritePin(TMC_EN_GPIO_Port, TMC_EN_Pin, GPIO_PIN_SET);

#define TMC_STEP_H HAL_GPIO_WritePin(TMC_STEP_GPIO_Port, TMC_STEP_Pin, GPIO_PIN_SET);
#define TMC_STEP_L HAL_GPIO_WritePin(TMC_STEP_GPIO_Port, TMC_STEP_Pin, GPIO_PIN_RESET);

#define TMC_DIR_CW HAL_GPIO_WritePin(TMC_DIR_GPIO_Port, TMC_DIR_Pin, GPIO_PIN_SET);
#define TMC_DIR_CCW HAL_GPIO_WritePin(TMC_DIR_GPIO_Port, TMC_DIR_Pin, GPIO_PIN_RESET);

typedef struct TMC{
	uint8_t errorFlag;
	//uint16_t _cs;
	//GPIO_TypeDef* _ps;
	//SPI_HandleTypeDef* _spi;
	uint16_t position;
} TMC;

void TMC_init(TMC *PMSM);
void TMC_move_to(float target_angle, float current_angle, float maxfreq);
void TMC_test_run();

#endif /* SRC_DRIVERS_DRV_TMC2660_H_ */
