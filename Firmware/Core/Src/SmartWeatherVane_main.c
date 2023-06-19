/*
 * SmartWeatherVane_main.c
 *
 *  Created on: 22 May 2023
 *      Author: R.Lin
 */

#include "SmartWeatherVane_main.h"

uint16_t raw_angle = 0;
float current_angle_map = 0;
float angle = 0;

TMC Motor;
AS5048A Encoder;

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  */
void SmartWeatherVane_main(){

	// initialise Stepper motor
	TMC_init(&Motor);

	// initialise magnetic absolute encoder
	AS5048A_init(&Encoder, &hspi2, AS5048_CS_GPIO_Port, AS5048_CS_Pin);
	HAL_Delay(100);
	uint16_t zero_position;
	float zero_position_map;
	zero_position = AS5048A_getRawRotation(&Encoder);
	printf("Zero: %d\n", zero_position);
	zero_position_map = AS5048A_read2angle(&Encoder, zero_position);
	printf("Angle: %f\n", zero_position_map);

	// initialise uart communication
	UART_init();

	UART_send_start_msg();
	UART_send_instruction_msg();

	// start 19kHz timer callback
	Timer_Callback_START();

	//TMC_test_run();

	// super-loop
	while(1){}
}

/**
  * @brief  TIM10 callback running @ 10kHz
  */
void Timer_Callback(){
	// get angle
	raw_angle = AS5048A_getRawRotation(&Encoder);
	angle =  AS5048A_read2angle(&Encoder, raw_angle);

	char uart_tx_buffer[1024];
	snprintf(uart_tx_buffer, sizeof uart_tx_buffer, "%.3f \r\n", angle);
	// truncate buffer at newline character
	char line_end = '\n';
	char *ptr = strchr(uart_tx_buffer, line_end);
	if(ptr){
		uint16_t size = ptr - uart_tx_buffer + 1;
		// send through uart
		HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, size, 100);
	}
}


int _write(int file, char *ptr, int len)
{
	for (int i = 0; i < len; i++){
		ITM_SendChar(*ptr++);
	}
	return len;
}

