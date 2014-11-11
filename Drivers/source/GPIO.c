#include "includes.h"

/*************************************************************************
 * Function Name: GPIOInit
 * Parameters: void
 * Return: void
 *
 * Description: Reset all GPIO pins to default: primary function
 *
 *************************************************************************/
void GPIOInit(void) {

// Set to inputs
  IO0DIR  = \
  IO1DIR  = \
  FIO0DIR = \
  FIO1DIR = \
  FIO2DIR = \
  FIO3DIR = \
  FIO4DIR = 0;
  
// enable fast GPIOs
  SCS_bit.GPIOM = 1;	

// clear mask registers
  FIO0MASK =\
  FIO1MASK =\
  FIO2MASK =\
  FIO3MASK =\
  FIO4MASK = 0;

// Reset all GPIO pins to default primary function
  PINSEL0 =\
  PINSEL1 =\
  PINSEL2 =\
  PINSEL3 =\
  PINSEL4 =\
  PINSEL5 =\
  PINSEL6 =\
  PINSEL7 =\
  PINSEL8 =\
  PINSEL9 =\
  PINSEL10= 0;
}