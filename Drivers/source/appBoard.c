/*************************************************************************
 *
 *    File name   : applicationsBoard.c
 *    Description : Configures device interface to the applications board
 *                  and provides access to the ADC, Heater, Motor and LEDs
 *    Interface
 *                           111111
 *          FIO4Port         5432109876543210
 *                  --------------------------
 *                           <--ADC->MMTLLLLL|
 *                  --------------------------
 *
 *   M: Motor, H: Heater, L: LED
 * 
 *    History :
 *    1. Date        : November 21, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/
#include "includes.h"

/*
 * appBoardInit()
 *
 * Initialise GPIO for applications board interface
 * LEDs on FIO4.[0..4]
 * Heater on FIO4.[5]
 * Motor on FIO4.[66..7]
 * ADC(Temperature) on FIO4.[8..15]
 */
void appBoardInit() {
   FIO4DIR=  0x000000FF;  /* Outputs P4.0 .. P4.7 and inputs P4.7 .. P4.15 */
   FIO4MASK= 0x00000000;  /* All GPIO on P4 is enabled */
   FIO4CLR=  0x000000FF;  /* Clear all output bits */ 
}


/*
 * appBoardReadADC()
 * Reads the value of the applications board ADC
 *
 * Parameter: none
 * Value: low 8-bits of an int
 *
 */
int appBoardReadADC() {
    return ( ( FIO4PIN & 0xFF00 ) >> 8);
}

/*
 * appBoardHeaterState()
 * Controls the state of the applications board heater
 *
 * Parameter: motorState in {OFF,ON}
 * Returns -1 for a parameter error, otherwise 1
 */
int appBoardHeaterState( int heaterState ) {
  if ( ( heaterState != ON ) && ( heaterState != OFF ) )
    return -1;
  if ( heaterState == ON )
    FIO4SET= 0x20;
  else
    FIO4CLR= 0x20;
  return 1;
}

/*
 * appBoardMotorState()
 * Controls the state of the applications board motor
 *
 * Parameter: motorState in {OFF,FWD,REV}
 * Returns -1 for a parameter error, otherwise 1
 */
int appBoardMotorState( int motorState ){
  if ( ( motorState != OFF ) && ( motorState != FWD ) && ( motorState != REV ) )
    return -1;  
  if ( motorState == OFF ) {
    FIO4CLR= 0xc0;
  } else if ( motorState == FWD ) {
    FIO4CLR= 0xc0;
    FIO4SET= 0x80;
  } else {
    FIO4CLR= 0xc0;
    FIO4SET= 0x40;
  }
  return 1;
}



/*
 * appBoardLEDState()
 * Outputs to the low significant 5 bits of the LED interface
 *
 * Parameter: LEDstate in {0..31}
 *
 */
void appBoardLEDState( int LEDState ) {
  int temp;
  temp= FIO4PIN;              /* Get current FIO4 pins */
  temp &= 0xFFC0;             /* Clear bits 0..4 */
  temp |= (LEDState & 0x1F);  /* Set required LEDs */
  FIO4PIN= temp;              /* Output to FIO4 port */
}