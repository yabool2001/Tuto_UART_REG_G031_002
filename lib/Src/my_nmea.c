/*
 * my_nmea.c
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NMEA_BUFFER_SIZE 255

char my_nmea_buffer[NMEA_BUFFER_SIZE];
uint8_t my_nmea_buffer_index = 0;


double nmea_to_decimal ( double nmeaCoord ) {
    int degrees = (int)(nmeaCoord / 100);
    double minutes = nmeaCoord - degrees * 100;
    return degrees + minutes / 60;
}

int main()
{
    // Przykład współrzędnych NMEA
    double latitude_nmea = 5216.7071 ; // Przykład szerokości geograficznej
    double longitude_nmea = 2048.5512 ; // Przykład długości geograficznej

    // Przekształcenie na stopnie dziesiętne
    double latitude_decimal = nmea_to_decimal ( latitude_nmea ) ;
    double longitude_decimal = nmea_to_decimal ( longitude_nmea ) ;

    printf ( "Szerokość geograficzna w stopniach dziesiętnych: %.7lf\n" , latitude_decimal ) ;
    printf ( "Długość geograficzna w stopniach dziesiętnych: %.7lf\n" , longitude_decimal ) ;

    return 0;
}


void my_nmea_message ( uint8_t* c , uint8_t* i , uint8_t* m )
{
	if ( *c == '$')
	{
		*i = 0 ;
		m[*i] = *c ;
		m[(*i)++] = '\0' ;
	}
	if ( *c >= ' ' && *c <= '~' && *i > 0 )
	{
		m[*i] = *c ;
		(*i)++ ;
	}


		// Jeśli otrzymany znak to znak końca linii (np. '\n'), zakończ budowanie sekwencji
		if ( c == '\n')
		{
			my_nmea_buffer [my_nmea_buffer_index] = '\0' ;
			//ParseGNGLL ( my_nmea_buffer ) ;
			my_nmea_buffer_index = 0 ;
		}
		else
		{
			my_nmea_buffer[nmea_buffer_index] = c ;
			my_nmea_buffer_index++;
			if ( my_nmea_buffer_index >= NMEA_BUFFER_SIZE )
			{
				my_nmea_buffer_index = 0;
			}
		}
	}
}
