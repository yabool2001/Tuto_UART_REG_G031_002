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
#include <stdbool.h>
#include "stm32g031xx.h"
#include "my_tims.h"
#include "my_uart.h"

#include "../my_lib/Inc/my_nmea.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define MY_G031_SYSCLOCK	(uint32_t) 16000000
#define MY_UART1_BAUDRATE	(uint32_t) 9600
#define MY_UART2_BAUDRATE	(uint32_t) 115200
#define NMEA_3D_FIX			'3'

char* nmea_message_t = "$GNGSA,A,3,12,19,32,06,11,28,,,,,,,1.69,1.42,0.91,1*06" ;
char* nmea_message_p = "$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E" ;

uint8_t my_tim16_up ;
uint8_t rx_byte_uart1 ;
uint8_t nmea_message[250] ;
uint8_t nmea_latitude[12] ; // 11 + '\0'
uint8_t nmea_longitude[13] ; // 12 + '\0'
uint8_t i_nmea = 0 ;
uint8_t nmea_checksum ;
uint8_t nmea_3d_fix = 3 ;
char* 	nmea_gngsa_label = "GNGSA" ;
char* 	nmea_gngll_label = "GNGLL" ;
char	nmea_fixed_mode_s ;
double 	nmea_fixed_pdop_d = 0.0 ;

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
	rx_byte_uart1 = 0x00 ;
	my_tim16_up = 0 ;
	//config_my_tim16 ( MY_G031_SYSCLOCK ) ;
	//start_my_tim16 ( (uint16_t) 1000 ) ;
	/* Loop forever */
	while ( 1 )
	{
		/*rx_byte_my_uart1 ( &rx_byte_uart1 ) ;
		if ( rx_byte_uart1 )
		{
			if ( my_nmea_message ( &rx_byte_uart1 , nmea_message , &i_nmea ) == 2 )
			{*/
				//tx_byte_my_uart2 ( &rx_byte_uart1 ) ;
				if ( is_my_nmea_checksum_ok ( nmea_message_t ) )
				{
					if ( strstr ( (char*) nmea_message_t , nmea_gngsa_label ) )
					{
						nmea_fixed_mode_s = get_my_nmea_fixed_mode_s ( nmea_message_t ) ;
						nmea_fixed_pdop_d = get_my_nmea_pdop_d ( nmea_message_t ) ;
						if ( nmea_fixed_mode_s == NMEA_3D_FIX && nmea_fixed_pdop_d < 2 )
						{
							__NOP () ;
						}
					}
				}
				//tx_byte_my_uart2 ( &nmea_checksum ) ;
				//tx_string_my_uart2 ( nmea_message , i_nmea ) ;
			/*}
			//tx_byte_my_uart2 ( &rx_byte_uart1 ) ;
			rx_byte_uart1 = 0x00 ;
		}*/
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
