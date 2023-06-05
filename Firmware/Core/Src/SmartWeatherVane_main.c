/*
 * SmartWeatherVane_main.c
 *
 *  Created on: 22 May 2023
 *      Author: ruili
 */

#include "SmartWeatherVane_main.h"

int x = 0;
int y = 2;
uint8_t txdata[30] = "printing stuff on COM port\n\r";

/**
  * @brief  Master Rx Transfer completed callback.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void SmartWeatherVane_main(){


	while(1){
		printf("%d This is a test mouahaha!\n", x++);
		y--;
		HAL_UART_Transmit(&huart2, txdata, sizeof(txdata), 100);
		HAL_Delay(1000);
	}
}

void Timer_Callback(){

}


int _write(int file, char *ptr, int len)
{
	for (int i = 0; i < len; i++){
		ITM_SendChar(*ptr++);
	}
	return len;
}

