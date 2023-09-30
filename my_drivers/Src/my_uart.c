/*
 * my_uart.c
 *
 *  Created on: Sep 30, 2023
 *      Author: mzeml
 *
 * USART2_TX = PA2
 * USART2_RX = PA3
 *
 * USART1_TX = PA9
 * USART1_RX = PA10
 *
 */

#include "my_uart.h"

void my_uart1_init ( void )
{
	GPIOA->MODER 	&= ~GPIO_MODER_MODE9_0 ; 	// Set Alternate Function (AF) for USART1_TX
	GPIOA->MODER 	&= ~GPIO_MODER_MODE10_0 ; 	// Set Alternate Function (AF) for USART1_RX
	GPIOA->AFR[1]	|= GPIO_AFRH_AFSEL9_0 ;  	// ALERT! AFRH is AFR[1]. Choose AF1
	GPIOA->AFR[1]	|= GPIO_AFRH_AFSEL10_0 ;  	// ALERT! AFRH is AFR[1]. Choose AF1
	GPIOA->OTYPER	|= GPIO_OTYPER_OT3 ; 		// Choose Open_drain for RX to avoid P-MOS transistors problems and assuming push-pull expected on device
}

void my_uart1_on ( uint16_t my_sysclock , uint16_t br )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	RCC->APBENR2	|= RCC_APBENR2_USART1EN ;
	USART1->BRR 	=  my_sysclock / br ;			// Activate clock for UART
	USART1->CR1 	|=  USART_CR1_UE ;
	USART1->CR1 	|=  USART_CR1_TE ;
	USART1->CR1 	|=  USART_CR1_RE ;
}

void my_uart2_init ( void )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	GPIOA->MODER 	&= ~GPIO_MODER_MODE2_0 ; 	// Set Alternate Function (AF) for USART2_TX
	GPIOA->MODER 	&= ~GPIO_MODER_MODE3_0 ; 	// Set Alternate Function (AF) for USART2_RX
	GPIOA->AFR[0]	|= GPIO_AFRL_AFSEL2_0 ;  	// ALERT! AFRL is AFR[0]. Choose AF1
	GPIOA->AFR[0]	|= GPIO_AFRL_AFSEL3_0 ;  	// ALERT! AFRL is AFR[0]. Choose AF1
	GPIOA->OTYPER	|= GPIO_OTYPER_OT3 ; 		// Choose Open_drain for RX to avoid P-MOS transistors problems and assuming push-pull expected on device
}

void my_uart2_on ( uint16_t my_sysclock , uint16_t br )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	RCC->APBENR1	|= RCC_APBENR1_USART2EN ;
	USART2->BRR 	= my_sysclock / br ;			// Activate clock for UART
	USART2->CR1 	|=  USART_CR1_UE ;
	USART2->CR1 	|=  USART_CR1_TE ;
	USART2->CR1 	|=  USART_CR1_RE ;
}
