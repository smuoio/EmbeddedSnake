/*************************************************************************
 *
 *    File name   : LEDs.c
 *    Description : Initialises and controls the LPC2378 on-board LEDs
 *
 *    History :
 *    1. Date        : November 21, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"

/* Initialise the interface to the USB_LINK_LED and USB_CONNECT_LED LEDs
 */
void LEDInit( void ) {

/* Assign output to P0.13 and P0.14 */
   USB_LINK_LED_FDIR |= USB_LINK_LED_MASK;
   USB_CONNECT_LED_FDIR |= USB_CONNECT_LED_MASK;
}


/* Change the state of the two on-board LEDs
 * LED in { USB_LINK_LED, USB_CONNECT_LED }
 * State in { ON, OFF }
 * Returns -1 for a parameter error, otherwise 1
 */
int LEDState( int LED, int State ) {

/* Check parameter */
   if ( ( LED != USB_LINK_LED ) &&
        ( LED != USB_CONNECT_LED ) )
      return -1;
   if ( ( State != ON ) &&
        ( State != OFF ) )
      return -1;

/* Set LED state */
   if ( LED == USB_LINK_LED )
     if ( State == ON )
       USB_LINK_LED_FCLR= USB_LINK_LED_MASK;
     else
       USB_LINK_LED_FSET= USB_LINK_LED_MASK;
   else
     if ( State == ON )
       USB_CONNECT_LED_FCLR= USB_CONNECT_LED_MASK;
     else
       USB_CONNECT_LED_FSET= USB_CONNECT_LED_MASK;    
   return 1;
}