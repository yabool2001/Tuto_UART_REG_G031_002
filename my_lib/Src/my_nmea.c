/*
 * my_nmea.c
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#include "my_nmea.h"


int my_nmea_message ( uint8_t* c , uint8_t* m , uint8_t* i )
{
    if ( *c == '$' )
    {
        *i = 0 ;
        m[(*i)++] = *c ;
        m[*i] = '\0' ;
        return 0 ;
    }
    if ( ( *c >= ' ' && *c <= '~' && *i > 0 ) || *c == '\r' )
    {
        m[(*i)++] = *c ;
        m[*i] = '\0' ;
        return 1 ;
    }
    if ( *c == '\n' && *i > 1 )
    {
        if ( m[--(*i)] == '\r' )
        {
            m[*i] = '\0' ;
            return 2 ;
        }
    }
    return -1 ;
}

const char get_my_nmea_fixed_mode_s ( const char* m )
{
	return m[9] ;
}

double get_my_nmea_pdop_d ( const char* m )
{
	uint8_t p_start = my_find_position ( m , GSA_PDOP_POSITION ) ;
	uint8_t p_stop = my_find_position ( m , GSA_PDOP_POSITION + 1 ) ;
	p_start++ ;
	uint8_t l = p_stop - p_start ;
	char* pdop_string = (char*) malloc ( ( l +1 ) * sizeof ( char ) ) ;
	strncpy ( pdop_string , m + p_start , l ) ; // Kopiowanie fragmentu łańcucha
	pdop_string[l] = '\0';
	double pdop = my_string2double_conv ( pdop_string ) ;
	free ( pdop_string ) ;
	return pdop ; // przed zwróceniem zaokrąglij do 2 miejsc po przecinku
}

bool is_my_nmea_checksum_ok ( const char* s )
{
    uint8_t cs = 0 ;
    uint8_t i = 1 ; // Start from index 1 to skip the '$' character
    while ( s[i] != '*' && s[i] != '\0' && i != 0 )
        cs ^= s[i++] ;
    //uint8_t* b = &s[++i] ;
    //uint8_t* c = strtol ( b , NULL, 16 ) ;
    return ( cs == strtol ( (char*) &s[++i] , NULL, 16 ) ) ? true : false ;
}

double nmea2decimal ( const char *coord , char dir )
{
    double deg , min ;
    sscanf ( coord , "%lf" , &deg ) ;
    min = deg / 100 ;
    deg = (int) min ;
    min = min - deg ;
    return deg + min / 0.6 * ( ( dir == 'S' || dir == 'W' ) ? -1 : 1 ) ;
}
