/*************************************************************************
 *
 *    File name   : buttons.c
 *    Description : Configures and Reads the buttons on the LPC2378 board
 *
 *    History :
 *    1. Date        : November 21, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"
#include "buttons.h"

/* Initialise the interface to the on-board LPC2378 board buttons
 *
 *                         JS_UP
 *                           |
 *   BUT_1    JS_LEFT -- JS_CENTRE -- JS_RIGHT    BUT_2
 *                           |
 *                        JS_DOWN
 */
void buttonsInit(void) {

/* Define inputs for buttons using Fast GPIO interface
 */
   B1_FDIR &= ~B1_MASK;
   B2_FDIR &= ~B2_MASK;
   JS_FDIR &= ~JS_LEFT_MASK;
   JS_FDIR &= ~JS_RIGHT_MASK;
   JS_FDIR &= ~JS_UP_MASK;
   JS_FDIR &= ~JS_DOWN_MASK;
   JS_FDIR &= ~JS_CENTER_MASK;
}


/* Reads the state of an on-board button
 * Button in { BUT_1, BUT_2, JS_LEFT, JS_RIGHT, JS_UP, JS_DOWN, JS_CENTRE }
 * Returns 1 if button is currently pressed and 0 otherwise
 * Returns -1 for a button parameter error 
 */
int buttonRead( int Button ) {

/* Check that the parameter is in range
 */
   if ( ( Button != BUT_1 ) && ( Button != BUT_2 ) &&
        ( Button != JS_LEFT ) && ( Button != JS_RIGHT ) &&
        ( Button != JS_UP ) && ( Button != JS_DOWN ) &&
        ( Button != JS_CENTRE ) )
      return -1;

/* Test the required button state
 */
   switch ( Button ) {
   case BUT_1 :
     return ((B1_FIO & B1_MASK )?0:1);
   case BUT_2 :
     return ((B2_FIO & B2_MASK )?0:1);
   case JS_LEFT :
     return ((JS_FIO & JS_LEFT_MASK)?0:1);
   case JS_RIGHT :
     return ((JS_FIO & JS_RIGHT_MASK)?0:1);
   case JS_UP :
     return ((JS_FIO & JS_UP_MASK )?0:1);
   case JS_DOWN :
     return ((JS_FIO & JS_DOWN_MASK)?0:1);
   case JS_CENTRE :
     return ((JS_FIO & JS_CENTER_MASK)?0:1);
   }
   return 1; /* Needs this to satisfy the compiler! */
}