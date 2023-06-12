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

void PWM_Start();
void PWM_Stop();
void PWM_HZ(bool state);
void PWM_Set_DutyCycle(float DC);
void PWM_Set_Frequency(float freq);

extern TIM_HandleTypeDef htim3;

#endif /* SRC_DRIVERS_DRV_PWM_H_ */
