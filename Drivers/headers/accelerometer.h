/*************************************************************************
 *
 *    File name   : accelerometer.h
 *    Description : Configures and LPC2378 ADC to read accelerometer
 *                  values
 *
 *    History :
 *    1. Date        : November 24, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"


/* Initialise the ADC to read X, Y and X axis accelerometer values
 */
void accelerometerInit( void );



/* Read the ADC to determine an accelerometer channel value
 */
int accelerometerRead( int );