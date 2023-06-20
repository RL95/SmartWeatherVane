/*
 * DRV_uart_TxRx.h
 *
 *  Created on: June 13, 2023
 *      Author: R.Lin
 */

#ifndef SRC_DRIVERS_DRV_UART_TXRX_H_
#define SRC_DRIVERS_DRV_UART_TXRX_H_

#include "main.h"

void UART_init();
void UART_send(char * msg);
void UART_send_start_msg();
void UART_send_instruction_msg();

extern uint8_t UART_Rx_data[1];
extern uint8_t cmd_buffer[8];
extern uint8_t cmd_buffer_end_idx;
extern bool get_val_flag;
extern bool get_val_done_flag;

#endif /* SRC_DRIVERS_DRV_UART_TXRX_H_ */
