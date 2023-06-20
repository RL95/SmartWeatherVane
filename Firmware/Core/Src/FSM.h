/*
 * FSM.h
 *
 *  Created on: Jun 20, 2023
 *      Author: R.Lin
 */

#ifndef SRC_FSM_H_
#define SRC_FSM_H_

#include "main.h"
#include "Drivers/DRV_AS5048A.h"
#include <stdbool.h>

void init_FSM();
void step_FSM_menu();
void step_FSM_retval();
void step_FSM_sendval();
void get_target_angle();
void update_current_angle();
float get_current_angle();
float get_FSM_target_angle();

#endif /* SRC_FSM_H_ */
