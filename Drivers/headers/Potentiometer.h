/*************************************************************************
 *
 *    File name   : potentiometer.h
 *    Description : Configures and LPC2378 ADC to read the Potentiometer
 *                  value
 *
 *    History :
 *    1. Date        : November 24, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/

/* Initialise the potentiometer associated with the pot on the LPC2378
 */
void potentiometerInit( void );

/* Read the ADC to determine a potentiometer position
 */
int potentiometerRead( void );