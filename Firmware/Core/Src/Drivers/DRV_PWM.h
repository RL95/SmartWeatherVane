/*
 * DRV_PWM.h
 *
 *  Created on: June 12, 2023
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_PWM_H_
#define SRC_DRIVERS_DRV_PWM_H_

#include "main.h"
#include <stdbool.h>

#define TIMER_CLOCK_FREQ 84000000.0f

void PWM_Start();
void PWM_Stop();
void PWM_HZ(bool state);
void PWM_Set_DutyCycle(float DC);
void PWM_Set_Frequency(float freq);
void PWM_Set(float freq, float DC);

extern TIM_HandleTypeDef htim3;

#endif /* SRC_DRIVERS_DRV_PWM_H_ */
