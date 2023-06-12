/*
 * SmartWeatherVane_main.h
 *
 *  Created on: 22 May 2023
 *      Author: R.Lin
 */

#ifndef SRC_SMARTWEATHERVANE_MAIN_H_
#define SRC_SMARTWEATHERVANE_MAIN_H_

#include <main.h>
#include <stdio.h>
#include <math.h>
#include "stdbool.h"
#include "stdarg.h"
#include "string.h"
#include "Drivers/DRV_timer_callback.h"
#include "Drivers/DRV_AS5048A.h"
#include "Drivers/DRV_TMC2660.h"

void SmartWeatherVane_main();
void Timer_Callback();
int _write(int file, char *ptr, int len);

extern UART_HandleTypeDef huart2;

#endif /* SRC_SMARTWEATHERVANE_MAIN_H_ */
