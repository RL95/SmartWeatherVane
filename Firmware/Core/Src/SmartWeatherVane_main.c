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
float angle_offset = 0;

bool stream_en = 0;
bool stream_once = 0;

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
	HAL_Delay(100);/*
	uint16_t zero_position;
	float zero_position_map;
	zero_position = AS5048A_getRawRotation(&Encoder);
	printf("Zero: %d\n", zero_position);
	zero_position_map = AS5048A_read2angle(&Encoder, zero_position);
	printf("Angle: %f\n", zero_position_map);*/

	// initialise uart communication
	UART_init();

	// settling time
	HAL_Delay(1000);

	UART_send_start_msg();
	UART_send_instruction_msg();

	// start 19kHz timer callback
	Timer_Callback_START();

	//TMC_test_run();

	// super-loop
	while(1){}
}

/**
  * @brief  TIM10 callback running @ 10Hz
  */
void Timer_Callback_10Hz(){
	// send sensor angle if stream requested
	if(stream_en || stream_once){
		// get angle
		raw_angle = AS5048A_getRawRotation(&Encoder);
		float angle_temp =  AS5048A_read2angle(&Encoder, raw_angle) - angle_offset;
		angle = AS5048A_normalize(&Encoder,angle_temp);

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
		// reset stream once flag
		if (stream_once) stream_once = 0;
	}
}

/**
  * @brief  TIM11 callback running @ 10kHz
  */
void Timer_Callback_10kHz(){
	switch(UART_Rx_data[0])
	    {
	        case 's':
	        	UART_Rx_data[0] = '*';
	        	stream_en = 1;
	            break;

	        case 'a':
	        	UART_Rx_data[0] = '*';
	        	stream_once = 1;
	            break;

	        case 'z':
	        	UART_Rx_data[0] = '*';
	        	angle_offset = AS5048A_read2angle(&Encoder, raw_angle);
	        	char set_zero_msg[16];
				snprintf(set_zero_msg, sizeof set_zero_msg, "New Zero set!\r\n");
				// send through uart
				HAL_UART_Transmit(&huart2, (uint8_t *)&set_zero_msg, sizeof(set_zero_msg), 100);
	            break;

	        case '\e':
	        	UART_Rx_data[0] = '*';
	        	stream_en = 0;
	        	UART_send_instruction_msg();
	            break;

	        case '*':
	            break;

	        default:
	        	UART_Rx_data[0] = '*';
	        	char invalid_zero_msg[19];
				snprintf(invalid_zero_msg, sizeof invalid_zero_msg, "INVALID COMMAND!\r\n");
				// send through uart
				HAL_UART_Transmit(&huart2, (uint8_t *)&invalid_zero_msg, sizeof(invalid_zero_msg), 100);
	    }

	/*
	if(UART_Rx_data[0] == 's') stream_en = 1;
	else if (UART_Rx_data[0] == '\e') stream_en = 0;*/
}


int _write(int file, char *ptr, int len)
{
	for (int i = 0; i < len; i++){
		ITM_SendChar(*ptr++);
	}
	return len;
}

