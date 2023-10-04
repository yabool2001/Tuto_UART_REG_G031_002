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


int my_nmea_message ( char* c , char* m , int* i )
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

/*
int main ()
{
    char nmea_stream[] = "$GNCGA,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n$GPGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E\r\n";
    int i ;
    int l = strlen ( nmea_stream ) ;
    int r ;
    for ( i = 0 ; i < l ; i++ )
    {
        r = my_nmea_message ( &nmea_stream[i] , nmea_gngll_message , &n ) ;
        if ( r == 2 && !strncmp ( nmea_gngll_message , gngll , 6 ) )
        {
            printf ( nmea_gngll_message ) ;
        }
    }

    /*
    if (parseGNGLL(nmea, &latitude, &longitude) == 0) {
        printf("Szerokość geograficzna: %.4lf\n", latitude);
        printf("Długość geograficzna: %.4lf\n", longitude);
        printf("Wprowadź te dane do Google Maps: %.4lf, %.4lf\n", latitude, longitude);
    } else {
        printf("Błąd parsowania wiadomości NMEA.\n");
    }
    */
    return 0;
}
*/
 */
