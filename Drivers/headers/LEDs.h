/*************************************************************************
 *
 *    File name   : LEDs.h
 *    Description : Initialises and controls the LPC2378 on-board LEDs
 *
 *    History :
 *    1. Date        : November 21, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"

/* Values of LED state
 */
#define OFF 0
#define ON 1

/* Values of the two LEDs
 */
#define USB_LINK_LED 0
#define USB_CONNECT_LED 1

/* Initialise the interface to the USB_LINK and USB_CONNECT LEDs
 */
void LEDInit(void);

/* Change the state of the two on-board LEDs
 * LED in {USB_LINK,USB_CONNECT}
 * State in {ON,OFF}
 */
int LEDState( int LED, int State );