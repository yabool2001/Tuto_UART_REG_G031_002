/*
 * my_nmea.h
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#ifndef MY_NMEA_H_
#define MY_NMEA_H_

#define GSA_PDOP_POSITION 15

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "my_conversions.h"

int 		my_nmea_message ( uint8_t* , uint8_t* , uint8_t* ) ;
bool 		is_my_nmea_checksum_ok ( const char* ) ;
uint8_t* 	nmea_format ( uint8_t* ) ;
uint8_t 	get_my_nmea_fixed_mode_d ( uint8_t* ) ;
const char	get_my_nmea_fixed_mode_s ( const char* ) ;
const char	get_my_nmea_pdop_s ( const char* m ) ;
double		get_my_nmea_pdop_d ( const char* m ) ;
double 		nmea2decimal ( const char* , char ) ;

#endif /* MY_NMEA_H_ */
