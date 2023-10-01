/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32g031xx.h"
#include "my_tims.h"
#include "my_uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define MY_G031_SYSCLOCK	(uint32_t) 16000000
#define MY_UART1_BAUDRATE	(uint32_t) 9600
#define MY_UART2_BAUDRATE	(uint32_t) 115200

uint8_t my_tim16_up ;
uint8_t rx_byte_uart1[1] ;


int main(void)
{
	my_uart2_init () ;
	my_uart2_on ( MY_G031_SYSCLOCK , MY_UART2_BAUDRATE ) ;
	my_uart1_init () ;
	my_uart1_on ( MY_G031_SYSCLOCK , MY_UART1_BAUDRATE ) ;
	while ( !( USART2->ISR & USART_ISR_TXE_TXFNF ) )
	{
		;
	}
	USART2->TDR = '@' ; // TX test
	while ( !( USART1->ISR & USART_ISR_TXE_TXFNF ) )
	{
		;
	}
	USART1->TDR = '@' ; // TX test
	rx_byte_uart1[0] = 0x00 ;
	my_tim16_up = 0 ;
	//config_my_tim16 ( MY_G031_SYSCLOCK ) ;
	//start_my_tim16 ( (uint16_t) 1000 ) ;
	/* Loop forever */
	while ( 1 )
	{
		rx_byte_my_uart1 ( rx_byte_uart1 ) ;
		if ( rx_byte_uart1[0] )
		{
			tx_byte_my_uart2 ( rx_byte_uart1 ) ;
			rx_byte_uart1[0] = 0x00 ;
		}
		/*
		tx_byte_to_uart2 = rx_byte_from_uart2 ? rx_byte_from_uart2 : tx_byte_to_uart2 ;
		if ( my_tim16_up == 1)
		{
			my_tim16_up = 0 ;
			tx_byte_my_uart2 ( &rx_byte_uart1 ) ;
		}
		*/
	}
}

void TIM16_IRQHandler ( void )
{
	my_tim16_up = 1 ;
	TIM16->SR &= ~TIM_SR_UIF ;		//Clean UIF Flag
}
