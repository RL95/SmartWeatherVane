/*
 * DRV_AS5048A.c
 *
 *  Created on: Jun 5, 2023
 *      Author: R.Lin
 */

#include "DRV_AS5048A.h"

/**
 * @brief Initialiser Sets up the SPI interface
 */
void AS5048A_init(AS5048A *sensor, SPI_HandleTypeDef *hspi, GPIO_TypeDef* arg_ps, uint16_t arg_cs){
	AS5048_DIS_SPI;
	sensor->errorFlag = 0;
	sensor->_cs = arg_cs;
	sensor->_ps = arg_ps;
	sensor->_spi = hspi;
	sensor->errorFlag = 0;
	sensor->position = 0;

	AS5048A_close(sensor);
	AS5048A_open(sensor);
}

/**
 * @brief 	Closes the SPI connection
 * @note  	SPI has an internal SPI-device counter, for each init()-call the close() function must be called exactly 1 time
 */
void AS5048A_close(AS5048A *sensor){
	if (HAL_SPI_DeInit(sensor->_spi) != HAL_OK);
}

/**
 * @brief 	Open the SPI connection
 * @note  	SPI has an internal SPI-device counter, for each init()-call the close() function must be called exactly 1 time
 */
void AS5048A_open(AS5048A *sensor){
	if (HAL_SPI_Init(sensor->_spi) != HAL_OK);
}

/**
 * @brief 	Utility function used to calculate even parity of word
 */
uint8_t AS5048A_spiCalcEvenParity(AS5048A *sensor, uint16_t value){
	uint8_t cnt = 0;
	uint8_t i;

	for (i = 0; i < 16; i++){
		if (value & 0x1){
			cnt++;
		}
		value >>= 1;
	}
	return cnt & 0x1;
}

/*
 * @brief  	Read a register from the sensor
 * 	       	Takes the address of the register as a 16 bit word
 * @return 	Returns the value of the register
 */
uint16_t AS5048A_read(AS5048A *sensor, uint16_t registerAddress){

	uint8_t data[2];

	uint16_t command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint16_t)AS5048A_spiCalcEvenParity(sensor, command)<<15);

	//Split the command into two bytes
	data[1] = command & 0xFF;
	data[0] = ( command >> 8 ) & 0xFF;

	AS5048_EN_SPI;
	HAL_SPI_Transmit(sensor->_spi, (uint8_t *)&data, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	AS5048_DIS_SPI;

	AS5048_EN_SPI;
	HAL_SPI_Receive(sensor->_spi, (uint8_t *)&data, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	AS5048_DIS_SPI;

	if (data[1] & 0x40) {
		sensor->errorFlag = 1;
	} else {
		sensor->errorFlag = 0;
	}

	//Return the data, stripping the parity and error bits
	return (( ( data[1] & 0xFF ) << 8 ) | ( data[0] & 0xFF )) & ~0xC000;
}

/*
 * @brief	Write to a register
 * @note 	Takes the 16-bit  address of the target register and the 16 bit word of data
 * 			to be written to that register
 * @return	Returns the value of the register after the write has been performed. This
 * 			is read back from the sensor to ensure a sucessful write.
 */
uint16_t AS5048A_write(AS5048A *sensor, uint16_t registerAddress, uint16_t data) {

	uint8_t dat[2];

	uint16_t command = 0b0000000000000000; // PAR=0 R/W=W
	command |= registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint16_t)AS5048A_spiCalcEvenParity(sensor, command)<<15);

	//Split the command into two bytes
	dat[1] = command & 0xFF;
	dat[0] = ( command >> 8 ) & 0xFF;

	//Start the write command with the target address
	AS5048_EN_SPI;
	HAL_SPI_Transmit(sensor->_spi, (uint8_t *)&dat, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	AS5048_DIS_SPI;

	uint16_t dataToSend = 0b0000000000000000;
	dataToSend |= data;

	//Craft another packet including the data and parity
	dataToSend |= ((uint16_t)AS5048A_spiCalcEvenParity(sensor, dataToSend)<<15);
	dat[1] = command & 0xFF;
	dat[0] = ( command >> 8 ) & 0xFF;

	//Now send the data packet
	AS5048_EN_SPI;
	HAL_SPI_Transmit(sensor->_spi, (uint8_t *)&dat, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	AS5048_DIS_SPI;

	//Send a NOP to get the new data in the register
	dat[1] = 0x00;
	dat[0] = 0x00;
	AS5048_EN_SPI;
	HAL_SPI_Transmit(sensor->_spi, (uint8_t *)&dat, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	HAL_SPI_Receive(sensor->_spi, (uint8_t *)&dat, 2, 0xFFFF);
	while (HAL_SPI_GetState(sensor->_spi) != HAL_SPI_STATE_READY) {}
	AS5048_DIS_SPI;

	//Return the data, stripping the parity and error bits
	return (( ( dat[1] & 0xFF ) << 8 ) | ( dat[0] & 0xFF )) & ~0xC000;
}

/**
 * @brief	Returns the raw angle directly from the sensor
 */
uint16_t AS5048A_getRawRotation(AS5048A *sensor){
	return AS5048A_read(sensor, AS5048A_ANGLE);
}

/**
 * @brief	Get the rotation of the sensor relative to the zero position.
 *
 * @return 	integer between -2^13 and 2^13
 */
int AS5048A_getRotation(AS5048A *sensor){
	uint16_t data;
	int rotation;

	data = AS5048A_getRawRotation(sensor);
	rotation = (int)data - (int)sensor->position;
	if(rotation > 8191) rotation = -((0x3FFF)-rotation); //more than -180
	//if(rotation < -0x1FFF) rotation = rotation+0x3FFF;

	return rotation;
}

/**
 * @brief 	the value of the state register
 * @return 	16 bit word containing flags
 */
uint16_t AS5048A_getState(AS5048A *sensor){
	return AS5048A_read(sensor, AS5048A_DIAG_AGC);
}

/*
 * Check if an error has been encountered.
 */
uint8_t AS5048A_error(AS5048A *sensor){
	return sensor->errorFlag;
}

/**
 * @brief 	Returns the value used for Automatic Gain Control (Part of diagnostic
 * 			register)
 */
uint8_t AS5048A_getGain(AS5048A *sensor){
	uint16_t data = AS5048A_getState(sensor);
	return (uint8_t) data & 0xFF;
}

/*
 * @brief 	Get and clear the error register by reading it
 */
uint16_t AS5048A_getErrors(AS5048A *sensor){
	return AS5048A_read(sensor, AS5048A_CLEAR_ERROR_FLAG);
}

/*
 * @brief 	Set the zero position
 */
void AS5048A_setZeroPosition(AS5048A *sensor, uint16_t arg_position){
	sensor->position = arg_position % 0x3FFF;
}

/*
 * @brief 	Returns the current zero position
 */
uint16_t AS5048A_getZeroPosition(AS5048A *sensor){
	return sensor->position;
}

/*
 * @brief 	Returns normalized angle value
 */
float AS5048A_normalize(AS5048A *sensor, float angle) {
	#ifdef ANGLE_MODE_1
		angle += 180;
	#endif
	angle = fmod(angle, 360);
	if (angle < 0) {
		angle += 360;
	}
	#ifdef ANGLE_MODE_1
		angle -= 180;
	#endif
	return angle;
}

/*
 * @brief 	Returns calculated angle value
 */
float AS5048A_read2angle(AS5048A *sensor, uint16_t angle) {
	return (float)angle * ((float)360 / 16383);
};
