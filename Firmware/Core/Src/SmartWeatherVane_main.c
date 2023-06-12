/*
 * SmartWeatherVane_main.c
 *
 *  Created on: 22 May 2023
 *      Author: ruili
 */

#include "SmartWeatherVane_main.h"

float current_angle = 0;
float current_angle_map = 0;
float angle = 0;

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  */
void SmartWeatherVane_main(){

	// initialise Stepper motor
	TMC Motor;
	TMC_init(&Motor);

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

	//TMC_test_run();

	// super-loop
	while(1){

		current_angle = AS5048A_getRawRotation(&Encoder);

		char uart_tx_buffer[30];
		snprintf(uart_tx_buffer, sizeof uart_tx_buffer, "Current Angle: %f \r\n", current_angle);
		HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, sizeof(uart_tx_buffer), 100);

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

