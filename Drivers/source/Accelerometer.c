/*************************************************************************
 *
 *    File name   : accelerometer.c
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


/* accelerometerInit()
 *
 * Initialise the ADC associated with the accelerometer on the LPC2378
 *
 * Must be called prior to accelerometerRead()
 */
void accelerometerInit( void ) {
   ADCInit(X_CHANNEL);
   ADCInit(Y_CHANNEL);
   ADCInit(Z_CHANNEL);
}



/* Read the ADC to determine an accelerometer X-axis value
 * Returns a 10-bit value in {0..1023} or -1 for a parameter error
 */
int accelerometerRead( int channel ) {
   if ( ( channel != X_CHANNEL ) &&
        ( channel != Y_CHANNEL ) &&
        ( channel != Z_CHANNEL ) )
      return -1;
   
   switch ( channel ) {
   case X_CHANNEL:
     return (ADCRead(AIN1));
   case Y_CHANNEL:
     return (ADCRead(AIN0));
   case Z_CHANNEL:
     return (ADCRead(AIN6));
   }
   return 1; /* Required by the compiler! */
}
