/*************************************************************************
 *
 *    File name   : potentiometer.c
 *    Description : Configures and LPC2378 ADC to read the Potentiometer
 *                  ADC value
 *
 *    History :
 *    1. Date        : November 24, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"

/*
 * Initialise the ADC associated with the pot on the LPC2378
 * Uses the LPC2378 AIN5 port
 */
void potentiometerInit( void ) {
   ADCInit(ANALOG_TRIM_CHANNEL);
}



/*
 * Read the ADC to determine a potentiometer position
 * Returns a 10-bit value using the LPC2378 AIN5 port
 */
int potentiometerRead( void ) {
   return (ADCRead(AIN5));
}