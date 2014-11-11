/*************************************************************************
 *
 *    File name   : buttons.h
 *    Description : Configures and Reads the buttons on the LPC2378 board
 *
 *    History :
 *    1. Date        : November 21, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/

#define BUT_1 0
#define BUT_2 1
#define JS_LEFT 2
#define JS_RIGHT 3
#define JS_UP 4
#define JS_DOWN 5
#define JS_CENTRE 6

/* Initialise the interface to the USB_LINK and USB_CONNECT LEDs
 */
void buttonsInit(void);

/* Read a button state
 */
int buttonRead( int Button );