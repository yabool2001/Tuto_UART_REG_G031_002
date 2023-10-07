/*
 * my_nmea.c
 *
 *  Created on: Oct 2, 2023
 *      Author: mzeml
 */

#include "my_nmea.h"

/*
// Funkcja do przekształcania ciągu znaków NMEA na współrzędne
int parseNMEA(char *nmea, double *latitude, double *longitude) {
    char *token = strtok(nmea, ",");
    int i = 1;

    while (token != NULL) {
        if (i == 3 && strcmp(token, "N") == 0) {
            // Szerokość geograficzna na półkuli północnej
            *latitude = atof(strtok(NULL, ",")) / 100;
        } else if (i == 5 && strcmp(token, "E") == 0) {
            // Długość geograficzna na półkuli wschodniej
            *longitude = atof(strtok(NULL, ",")) / 100;
        }
        token = strtok(NULL, ",");
        i++;
    }

    return 0;
}

double nmea_to_decimal ( double nmeaCoord ) {
    int degrees = (int)(nmeaCoord / 100) ;
    double minutes = nmeaCoord - degrees * 100 ;
    return degrees + minutes / 60 ;
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
*/

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

uint8_t get_my_nmea_fixed_mode ( uint8_t* m )
{
	return ( ( m[9] - 48 ) > 0 ) ? ( m[9] - 48 ) : 0 ;
}

double get_my_nmea_pdop ( const char* m )
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
	return ( pdop * 100 ) / 100 ; // przed zwróceniem zaokrąglij do 2 miejsc po przecinku
}

bool is_my_nmea_checksum_ok ( uint8_t* s )
{
    uint8_t cs = 0 ;
    uint8_t i = 1 ; // Start from index 1 to skip the '$' character
    while ( s[i] != '*' && s[i] != '\0' && i != 0 )
        cs ^= s[i++] ;
    //uint8_t* b = &s[++i] ;
    //uint8_t* c = strtol ( b , NULL, 16 ) ;
    return ( cs == strtol ( (char*) &s[++i] , NULL, 16 ) ) ? true : false ;
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


    if (parseGNGLL(nmea, &latitude, &longitude) == 0) {
        printf("Szerokość geograficzna: %.4lf\n", latitude);
        printf("Długość geograficzna: %.4lf\n", longitude);
        printf("Wprowadź te dane do Google Maps: %.4lf, %.4lf\n", latitude, longitude);
    } else {
        printf("Błąd parsowania wiadomości NMEA.\n");
    }

    return 0;
}
*/
