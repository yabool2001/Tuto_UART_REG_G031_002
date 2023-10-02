/*
 * parse_nmea.c
 *
 *  Created on: Oct 1, 2023
 *      Author: mzeml
 */
#include <stdio.h>
#include <string.h>

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

int foo() {
    char nmea[] = "$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E";
    double latitude, longitude;

    if (parseNMEA(nmea, &latitude, &longitude) == 0) {
        //printf("Szerokość geograficzna: %.6lf N\n", latitude);
        //printf("Długość geograficzna: %.6lf E\n", longitude);
    } else {
        //printf("Błąd parsowania danych NMEA.\n");
    }

    return 0;
}

