/*
 * DRV_TMC2660.h
 *
 *  Created on: Jun 6, 2023
 *      Author: ruili
 */

#ifndef SRC_DRIVERS_DRV_TMC2660_H_
#define SRC_DRIVERS_DRV_TMC2660_H_

#include "main.h"

#define TMC_EN_SPI HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_RESET);
#define TMC_DIS_SPI HAL_GPIO_WritePin(TMC_CS_GPIO_Port, TMC_CS_Pin, GPIO_PIN_SET);

typedef struct TMC{
	uint8_t errorFlag;
	//uint16_t _cs;
	//GPIO_TypeDef* _ps;
	//SPI_HandleTypeDef* _spi;
	uint16_t position;
} TMC;

void TMC_init(TMC *PMSM);

#endif /* SRC_DRIVERS_DRV_TMC2660_H_ */
