/*
 * my_uart.c
 *
 *  Created on: Sep 30, 2023
 *      Author: mzeml
 *
 * USART2_TX = PA2
 * USART2_RX = PA3
 *
 * USART1_TX = PA9	PB6
 * USART1_RX = PA10	PB7
 *
 */

#include "my_uart.h"

void my_uart1_init ( void )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOBEN ;		// Activate clock in GPIOB
	GPIOB->MODER 	&= ~GPIO_MODER_MODE6_0 ; 	// Set Alternate Function (AF) for USART1_TX
	GPIOB->MODER 	&= ~GPIO_MODER_MODE7_0 ; 	// Set Alternate Function (AF) for USART1_RX
	//GPIOB->OTYPER	|= GPIO_OTYPER_OT7 ; 		// Choose Open_drain for RX to avoid P-MOS transistors problems and assuming push-pull expected on device
	GPIOB->PUPDR	|= GPIO_PUPDR_PUPD6_0 ;		// Tx Pull-up
	GPIOB->PUPDR	|= GPIO_PUPDR_PUPD7_0 ;		// Rx Pull-up
}

/*
// Version for PA9-10
void my_uart1_init ( void )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	GPIOA->MODER 	&= ~GPIO_MODER_MODE9_0 ; 	// Set Alternate Function (AF) for USART1_TX
	GPIOA->MODER 	&= ~GPIO_MODER_MODE10_0 ; 	// Set Alternate Function (AF) for USART1_RX
	GPIOA->AFR[1]	|= GPIO_AFRH_AFSEL9_0 ;  	// ALERT! AFRH is AFR[1]. Choose AF1
	GPIOA->AFR[1]	|= GPIO_AFRH_AFSEL10_0 ;  	// ALERT! AFRH is AFR[1]. Choose AF1
	GPIOA->OTYPER	|= GPIO_OTYPER_OT10 ; 		// Choose Open_drain for RX to avoid P-MOS transistors problems and assuming push-pull expected on device
	//GPIOA->PUPDR	|= GPIO_PUPDR_PUPD10_1 ;	// Rx Pull-up
}
*/
void my_uart2_init ( void )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	GPIOA->MODER 	&= ~GPIO_MODER_MODE2_0 ; 	// Set Alternate Function (AF) for USART2_TX
	GPIOA->MODER 	&= ~GPIO_MODER_MODE3_0 ; 	// Set Alternate Function (AF) for USART2_RX
	GPIOA->AFR[0]	|= GPIO_AFRL_AFSEL2_0 ;  	// ALERT! AFRL is AFR[0]. Choose AF1
	GPIOA->AFR[0]	|= GPIO_AFRL_AFSEL3_0 ;  	// ALERT! AFRL is AFR[0]. Choose AF1
	//GPIOA->OTYPER	|= GPIO_OTYPER_OT3 ; 		// Choose Open_drain for RX to avoid P-MOS transistors problems and assuming push-pull expected on device
	GPIOA->PUPDR	|= GPIO_PUPDR_PUPD2_0 ;		// Tx Pull-up
	GPIOA->PUPDR	|= GPIO_PUPDR_PUPD3_0 ;		// Rx Pull-up
}

void rx_byte_my_uart1 ( uint8_t* rx_byte )
{
	if ( USART1->ISR & USART_ISR_RXNE_RXFNE )
	{
		rx_byte[0] = USART1->RDR ;
	}
	else
	{
		__NOP() ;
	}
}

void rx_byte_my_uart2 ( uint8_t* rx_byte )
{
	if ( USART2->ISR & USART_ISR_RXNE_RXFNE )
	{
		rx_byte[0] = USART2->RDR ;
	}
}

void tx_byte_my_uart1 ( uint8_t* tx_byte )
{
	if ( USART1->ISR & USART_ISR_TXE_TXFNF )
	{
		USART1->TDR = tx_byte[0] ;
	}
}

void tx_byte_my_uart2 ( uint8_t* tx_byte )
{
	if ( USART2->ISR & USART_ISR_TXE_TXFNF )
	{
		USART2->TDR = tx_byte[0] ;
	}
}

void my_uart1_on ( uint32_t my_sysclock , uint32_t baudrate )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOBEN ;		// Activate clock in GPIOB
	RCC->APBENR2	|= RCC_APBENR2_USART1EN ;
	USART1->BRR 	=  (uint16_t) ( my_sysclock / baudrate ) ;			// Activate clock for UART
	USART1->CR1 	|=  USART_CR1_UE ;
	USART1->CR1 	|=  USART_CR1_TE ;
	USART1->CR1 	|=  USART_CR1_RE ;
}
/*
// Version for PA9-10
void my_uart1_on ( uint32_t my_sysclock , uint32_t baudrate )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	RCC->APBENR2	|= RCC_APBENR2_USART1EN ;
	USART1->BRR 	=  (uint16_t) ( my_sysclock / baudrate ) ;			// Activate clock for UART
	USART1->CR1 	|=  USART_CR1_UE ;
	USART1->CR1 	|=  USART_CR1_TE ;
	USART1->CR1 	|=  USART_CR1_RE ;
}
*/
void my_uart2_on ( uint32_t my_sysclock , uint32_t baudrate )
{
	RCC->IOPENR 	|= RCC_IOPENR_GPIOAEN ;		// Activate clock in GPIOA
	RCC->APBENR1	|= RCC_APBENR1_USART2EN ;
	USART2->BRR 	= (uint16_t) ( my_sysclock / baudrate ) ;			// Activate clock for UART
	USART2->CR1 	|=  USART_CR1_UE ;
	USART2->CR1 	|=  USART_CR1_TE ;
	USART2->CR1 	|=  USART_CR1_RE ;
}
