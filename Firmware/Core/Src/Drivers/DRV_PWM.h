/*
 * DRV_PWM.h
 *
 *  Created on: Oct 12, 2022
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_PWM_H_
#define SRC_DRIVERS_DRV_PWM_H_

#include "main.h"
#include <stdbool.h>

#define	PHASE_U 1
#define	PHASE_V 2
#define	PHASE_W 3
#define	CH_1 1
#define	CH_2 2
#define	CH_3 3

void PWM_Start_All();
void PWM_Stop_ALL();

void PWM_Start_UH();
void PWM_Start_VH();
void PWM_Start_WH();

void PWM_Start_UL();
void PWM_Start_VL();
void PWM_Start_WL();

void PWM_Stop_UH();
void PWM_Stop_VH();
void PWM_Stop_WH();

void PWM_Stop_UL();
void PWM_Stop_VL();
void PWM_Stop_WL();

void PWM_HZ_UH(bool state);
void PWM_HZ_VH(bool state);
void PWM_HZ_WH(bool state);

void PWM_HZ_UL(bool state);
void PWM_HZ_VL(bool state);
void PWM_HZ_WL(bool state);

void PWM_HZ_U(bool state);
void PWM_HZ_V(bool state);
void PWM_HZ_W(bool state);

void PWM_HZ_ALL(bool state);

void PWM_Set_DutyCycle_ALL(float DC);
void PWM_Set_DutyCycle(int CH, float DC);

extern TIM_HandleTypeDef htim1;

#endif /* SRC_DRIVERS_DRV_PWM_H_ */
