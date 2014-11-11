/*************************************************************************
 *
 *    File name   : appBoard.h
 *    Description : Configures device interface to the applications board
 *                  and provides access to the ADC, Heater, Motor and LEDs
 *
 *    History :
 *    1. Date        : November 29, 2009
 *       Author      : WDH
 *       Description : Create
 *
 **************************************************************************/

/* LED and heater states */
#define OFF 0
#define ON 1

/* Motor states */
#define STOP 0
#define FWD 1
#define REV 2


void appBoardInit();

int appBoardReadADC();

int appBoardHeaterState( int heaterState );

int appBoardMotorState( int motorState );

void appBoardLEDState( int LEDState );