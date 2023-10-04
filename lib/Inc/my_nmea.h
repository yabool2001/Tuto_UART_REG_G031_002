/*
 * my_nmea.h
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#ifndef MY_NMEA_H_
#define MY_NMEA_H_

int my_nmea_message ( uint8_t* , uint8_t* , uint8_t* ) ;
uint8_t my_nmea_checksum ( uint8_t* ) ;

#endif /* MY_NMEA_H_ */
