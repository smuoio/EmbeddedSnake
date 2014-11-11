/**************************************************************************
 * ADC Interface to LPC2378 board
 *
 * ADC.h
 *
 * There are three analogue devices on the LPC2378 board:
 *    One trim potentiometer on ANALOG_TRIP_CHANNEL
 *    Three Accelerometer inputs on X_CHANNEL, Y_CHANNEL and Z_CHANNEL
 *
 * This interface supports Potentiometer and Accelerometer initialisation
 * and read functions
 *
 * WDHenderson
 * November 25th, 2009
 **************************************************************************/
#include "includes.h"

#define AIN0 0
#define AIN1 1
#define AIN2 2
#define AIN3 3
#define AIN4 4
#define AIN5 5
#define AIN6 6
/*
 * Initialise a single ADC channel for polling
 *
 * Parameter in {AIN0, AIN1, AIN5, AIN6}
 *
 * Returns -1 for a parameter error or otherwise 0
 *
 */
int ADCInit( int Channel );


/*
 * Reads a single ADC channel
 * Parameter in {AIN0, AIN1, AIN5, AIN6}
 *
 * Returns -1 for a parameter error or the 10-bit ADC conversion
 * value
 *
 */
int ADCRead( int Channel );