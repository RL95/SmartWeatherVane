/*
 * SmartWeatherVane_main.c
 *
 *  Created on: 22 May 2023
 *      Author: R.Lin
 */

#include "SmartWeatherVane_main.h"

TMC Motor;
float cmd_angle = 0;

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  */
void SmartWeatherVane_main(){

	// initialise Stepper motor
	TMC_init(&Motor);

	// initialise FSM
	init_FSM();

	// initialise uart communication
	UART_init();

	// settling time
	HAL_Delay(1000);

	// send startup messages
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
	step_FSM_sendval();
}

/**
  * @brief  TIM11 callback running @ 10kHz
  */
void Timer_Callback_1kHz(){
	step_FSM_menu();
	step_FSM_retval();
	cmd_angle = get_FSM_target_angle();
	//TMC_move_to(90,8000);
}


int _write(int file, char *ptr, int len)
{
	for (int i = 0; i < len; i++){
		ITM_SendChar(*ptr++);
	}
	return len;
}

