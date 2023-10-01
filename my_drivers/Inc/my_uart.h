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
void my_uart1_on ( uint32_t , uint32_t ) ;
void my_uart2_init ( void ) ;
void my_uart2_on ( uint32_t , uint32_t ) ;
uint8_t rx_byte_my_uart1 ( void ) ;
uint8_t rx_byte_my_uart2 ( void ) ;
void tx_byte_my_uart1 ( uint8_t* ) ;
void tx_byte_my_uart2 ( uint8_t* ) ;

#endif /* MY_UART_H_ */
