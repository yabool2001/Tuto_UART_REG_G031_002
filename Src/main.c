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

#define MY_G031_SYSCLOCK	(uint16_t) 16000000
#define MY_UART1_BAUDRATE	(uint16_t) 9600
#define MY_UART2_BAUDRATE	(uint16_t) 115200

uint8_t my_tim16_up = 0 ;

int main(void)
{
	my_uart2_init () ;
	my_uart2_on ( MY_G031_SYSCLOCK , MY_UART2_BAUDRATE ) ;
	while ( !( USART2->ISR & USART_ISR_TXE_TXFNF ) )
	{
		;
	}
	USART2->TDR = 'A' ;
	config_my_tim16 ( MY_G031_SYSCLOCK ) ;
	start_my_tim16 ( (uint16_t) 1000 ) ;
/* Loop forever */
	while ( 1 )
	{
		if ( my_tim16_up == 1)
		{
			my_tim16_up = 0 ;
			if ( USART2->ISR & USART_ISR_TXE_TXFNF )
				USART2->TDR = 0x41 ;
		}
	}
}

void TIM16_IRQHandler ( void )
{
	my_tim16_up = 1 ;
	TIM16->SR &= ~TIM_SR_UIF ;		//Clean UIF Flag
}
