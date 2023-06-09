/*
 * DRV_uart_TxRx.c
 *
 *  Created on: Jun 13, 2023
 *      Author: R.Lin
 */


#include "DRV_uart_TxRx.h"

uint8_t UART_Rx_data[1] = {'*'};  //  creating a buffer of 1 bytes
uint8_t cmd_buffer[8] = {' ',' ',' ',' ',' ',' ',' ',' '};
uint8_t cmd_buffer_end_idx = 0;
bool get_val_flag = 0;
bool get_val_done_flag = 0;

/**
  * @brief  Initialise the first call for UART interrupt call
  */
void UART_init(){
	HAL_UART_Receive_IT (&huart2, UART_Rx_data, 1);
}

void UART_send(char * msg){

}

void UART_send_start_msg(){
	char uart_tx_buffer[4096];
	snprintf(uart_tx_buffer, sizeof uart_tx_buffer,
			"\r\n"
			"\r\n"
			"\r\n"
			"	                           |--------------------------|\r\n"
			"	                           |--- SMART WEATHER VANE ---|\r\n"
			"	                           |--------------------------|\r\n"
			"	                           |                          |\r\n"
			"	                           |       Version 1.0        |\r\n"
			"	                           |                          |\r\n"
			"	                           |    HEPIA HES-SO 2023     |\r\n"
			"	                           |       Author : RL        |\r\n"
			"	                           |                          |\r\n"
			"	                           |--------------------------|\r\n"
			"\r\n*");
	//HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, 629, 100);
	// truncate buffer at newline character
	char line_end = '*';
	char *ptr = strchr(uart_tx_buffer, line_end);
	if(ptr){
		uint16_t size = ptr - uart_tx_buffer;
		// send through uart
		HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, size, 100);
	}
}

void UART_send_instruction_msg(){
	char uart_tx_buffer[4096];
	snprintf(uart_tx_buffer, sizeof uart_tx_buffer,
			"\r\n"
			"	---------------    Use commands below to control the system    ---------------\r\n"
			"\r\n"
			"	Send 'z'      To set current position as zero.\r\n"
			"	Send 'b'      To toggle brake state.\r\n"
			"	Send 'l'      To get current brake state (0 = unlocked, 1 = locked).\r\n"
			"	Send 'mX'     To move to a given X angle.\r\n"
			"	              For example :   'm12' will move the system to 12deg.\r\n"
			"	              For example :   'm-45' will move the system to -45deg.\r\n"
			"\r\n"
			"	Send 'jX'     To jog the system X degrees.\r\n"
			"	              For example :   'j2' will increase the current angle by +2 deg.\r\n"
			"	                              'j-2' will decrease the current angle by -2 deg.\r\n"
			"\r\n"
			"	Send 'a'      To request the current angle once.\r\n"
			"	Send 's'      To continuously stream the current angle.\r\n"
			"\r\n"
			"\r\n"
			"	Press ESC key to abort any action and return to this menu.\r\n"
			"\r\n"
			"	Good luck and don't set anything on fire! :)\r\n"
			"\r\n*");
	//HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, 629, 100);
	// truncate buffer at newline character
	char line_end = '*';
	char *ptr = strchr(uart_tx_buffer, line_end);
	if(ptr){
		uint16_t size = ptr - uart_tx_buffer;
		// send through uart
		HAL_UART_Transmit(&huart2, (uint8_t *)&uart_tx_buffer, size, 100);
	}
}

/**
  * @brief  Callback when UART data arrives via interruption
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_IT(huart, UART_Rx_data, 1);
  if(get_val_flag && cmd_buffer_end_idx != '\r'){
	  cmd_buffer[cmd_buffer_end_idx] = UART_Rx_data[0];
	  cmd_buffer_end_idx ++;
	  if (UART_Rx_data[0] == '\r') {
		  get_val_flag = 0;
		  get_val_done_flag = 1;
		  cmd_buffer_end_idx --;
	  }
  }

}
