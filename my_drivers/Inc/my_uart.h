/*
 * my_uart.h
 *
 *  Created on: Sep 30, 2023
 *      Author: mzeml
 */

#ifndef MY_UART_H_
#define MY_UART_H_

#include "stm32g031xx.h"

void my_uart1_init ( void ) ;
void my_uart1_on ( uint16_t ) ;
void my_uart2_init ( void ) ;
void my_uart2_on ( uint16_t ) ;

#endif /* MY_UART_H_ */
