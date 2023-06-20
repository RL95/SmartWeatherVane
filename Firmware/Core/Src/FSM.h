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

#endif /* SRC_FSM_H_ */
