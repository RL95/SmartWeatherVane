/*
 * drv_timer_callback.h
 *
 *  Created on: Jun 06, 2023
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_AS5048A_H_
#define SRC_DRIVERS_DRV_AS5048A_H_

#include "main.h"

#define EN_SPI HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
#define DIS_SPI HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

#define AS5048A_CLEAR_ERROR_FLAG              0x0001
#define AS5048A_PROGRAMMING_CONTROL           0x0003
#define AS5048A_OTP_REGISTER_ZERO_POS_HIGH    0x0016
#define AS5048A_OTP_REGISTER_ZERO_POS_LOW     0x0017
#define AS5048A_DIAG_AGC                      0x3FFD
#define AS5048A_MAGNITUDE                     0x3FFE
#define AS5048A_ANGLE                         0x3FFF

typedef struct AS5048A{
	uint8_t errorFlag;
	uint16_t _cs;
	uint16_t cs;
	GPIO_TypeDef* _ps;
	SPI_HandleTypeDef* _spi;
	uint8_t dout;
	uint8_t din;
	uint8_t clk;
	uint16_t position;
	//uint16_t transaction(uint16_t data);
} AS5048A;

void AS5048A_init(AS5048A *sensor, SPI_HandleTypeDef *hspi, GPIO_TypeDef* arg_ps, uint16_t arg_cs);
void AS5048A_close(AS5048A *sensor);
void AS5048A_open(AS5048A *sensor);
uint16_t AS5048A_read(AS5048A *sensor, uint16_t registerAddress);
uint16_t AS5048A_write(AS5048A *sensor, uint16_t registerAddress, uint16_t data);
uint16_t AS5048A_getRawRotation(AS5048A *sensor);
int AS5048A_getRotation(AS5048A *sensor);
uint16_t AS5048A_getState(AS5048A *sensor);
uint8_t AS5048A_error(AS5048A *sensor);
uint8_t AS5048A_getGain(AS5048A *sensor);
uint16_t AS5048A_getErrors(AS5048A *sensor);
void AS5048A_setZeroPosition(AS5048A *sensor, uint16_t arg_position);
uint16_t AS5048A_getZeroPosition(AS5048A *sensor);
float AS5048A_normalize(AS5048A *sensor, float angle);
float read2angle(AS5048A *sensor, uint16_t angle);
uint8_t spiCalcEvenParity(AS5048A *sensor, uint16_t value);

extern SPI_HandleTypeDef hspi2;


#endif /* SRC_DRIVERS_DRV_AS5048A_H_ */
