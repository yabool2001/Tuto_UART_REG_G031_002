/*
 * my_nmea.h
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#ifndef MY_NMEA_H_
#define MY_NMEA_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int my_nmea_message ( uint8_t* , uint8_t* , uint8_t* ) ;
bool is_my_nmea_checksum_ok ( uint8_t* ) ;
uint8_t* nmea_format ( uint8_t* ) ;

#endif /* MY_NMEA_H_ */
