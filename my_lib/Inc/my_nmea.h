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

int my_nmea_message ( uint8_t* , uint8_t* , uint8_t* ) ;
bool is_my_nmea_checksum_ok ( uint8_t* ) ;
uint8_t* nmea_format ( uint8_t* ) ;
uint8_t get_my_nmea_fixed_mode ( uint8_t* ) ;
double get_my_nmea_pdop ( const char* m ) ;

#endif /* MY_NMEA_H_ */
