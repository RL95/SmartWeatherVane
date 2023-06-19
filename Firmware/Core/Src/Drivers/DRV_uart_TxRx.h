/*
 * DRV_uart_TxRx.h
 *
 *  Created on: June 13, 2023
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_UART_TXRX_H_
#define SRC_DRIVERS_DRV_UART_TXRX_H_

#include "main.h"

void UART_send(char * msg);
void UART_send_start_msg();
void UART_send_instruction_msg();



#endif /* SRC_DRIVERS_DRV_UART_TXRX_H_ */
