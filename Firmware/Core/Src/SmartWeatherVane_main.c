/*
 * SmartWeatherVane_main.c
 *
 *  Created on: 22 May 2023
 *      Author: ruili
 */

#include "SmartWeatherVane_main.h"

// COM port buffer
uint8_t txdata[30] = "printing stuff on COM port\n\r";

uint16_t current_angle = 0;
float current_angle_map = 0;
float angle = 0;

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  */
void SmartWeatherVane_main(){

	// initialise magnetic absolute encoder
	AS5048A Encoder;
	AS5048A_init(&Encoder, &hspi2, AS5048_CS_GPIO_Port, AS5048_CS_Pin);
	HAL_Delay(100);
	uint16_t zero_position;
	float zero_position_map;
	zero_position = AS5048A_getRawRotation(&Encoder);
	printf("Zero: %d\n", zero_position);
	zero_position_map = AS5048A_read2angle(&Encoder, zero_position);
	printf("Angle: %f\n", zero_position_map);

	// initialise Stepper motor
	TMC Motor;
	TMC_init(&Motor);

	// super-loop
	while(1){
		TMC_test_run();

		current_angle = AS5048A_getRawRotation(&Encoder);
		current_angle_map = AS5048A_read2angle(&Encoder, current_angle);

		float angle_temp = current_angle_map - zero_position_map;
		angle = AS5048A_normalize(&Encoder, angle_temp);

		printf("Current Angle: %d\nCurrent Angle Map: %f\nAngle: %f\n\n", current_angle, current_angle_map, angle);

		if (AS5048A_error(&Encoder)) {
		  printf("ERROR: %d\n", AS5048A_getErrors(&Encoder));
		}

		HAL_UART_Transmit(&huart2, txdata, sizeof(txdata), 100);
		HAL_Delay(10);
	}
}

/**
  * @brief  TIM10 callback running @ 10kHz
  */
void Timer_Callback(){

}


int _write(int file, char *ptr, int len)
{
	for (int i = 0; i < len; i++){
		ITM_SendChar(*ptr++);
	}
	return len;
}

