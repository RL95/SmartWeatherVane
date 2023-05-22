/*
 * SmartWeatherVane_main.h
 *
 *  Created on: 22 May 2023
 *      Author: ruili
 */

#ifndef SRC_SMARTWEATHERVANE_MAIN_H_
#define SRC_SMARTWEATHERVANE_MAIN_H_

#include <main.h>
#include <stdio.h>
#include "stdbool.h"
#include "Drivers/DRV_timer_callback.h"

void SmartWeatherVane_main();
void Timer_Callback();
int _write(int file, char *ptr, int len);

extern UART_HandleTypeDef huart2;

#endif /* SRC_SMARTWEATHERVANE_MAIN_H_ */
