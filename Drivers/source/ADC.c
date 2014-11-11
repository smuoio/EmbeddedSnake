#include "includes.h" 

/* Initialise ADC channel on MIC_IN - P0.25 - AD0.2
 **************************************************************************/
void InitADCSound() {

/* Assign P0.25 to AD0.2 */
   PINSEL1_bit.P0_25 = 1;

   PCONP_bit.PCAD = 1; // Enable ADC clk
   
/* Set ADC clk <4.5 MHz */
   AD0CR_bit.CLKDIV = (SYS_GetFpclk(24) / 45000000) + 1;
   
/* Select AD0.2 */
   AD0CR_bit.SEL = 1<<2;
   
/* Disable all interrupts */
   ADINTEN = 0;
   
/* Enable ADC */
   AD0CR_bit.PDN = 1;
   
/* Start conversion now */
   AD0CR_bit.START = 1;
}

/**************************************************************************
 * ADC Interface to LPC2378 board
 *
 * ADC.c
 *
 * There are three analogue devices on the LPC2378 board:
 *    One trim potentiometer on ANALOG_TRIP_CHANNEL and
 *    three Accelerometer inputs on X_CHANNEL, Y_CHANNEL and Z_CHANNEL
 *
 * This interface supports Potentiometer and Accelerometer initialisation
 * and read functions
 *
 * WDHenderson
 * November 25th, 2009
 **************************************************************************/

/*
 * Initialise a single ADC channel for polling
 *
 * Parameter in {AIN0, AIN1, AIN5, AIN6}
 *
 * Returns -1 for a parameter error or otherwise 0
 *
 */
int ADCInit( int Channel ) {

/* Check parameter in range */
   if ( ( Channel != AIN0 ) &&
        ( Channel != AIN1 ) &&
        ( Channel != AIN5 ) &&
        ( Channel != AIN6 ) )
      return -1;

/* Enable required ADC channel */
   switch ( Channel ) {
   case AIN5:
     PINSEL3_bit.P1_31 = 3;    /* Assign P1.31 to AIN5 */
     break;
   case AIN1:
     PINSEL1_bit.P0_24 = 1;    /* Assign P0.24 to AIN1 */
     break;
   case AIN0:
     PINSEL1_bit.P0_23 = 1;    /* Assign P0.23 to AIN0 */
     break;
   case AIN6:
     PINSEL0_bit.P0_12 = 3;    /* Assign P0.12 to AIN6 */
   }

/* Configure ADC clock */
   PCONP_bit.PCAD = 1; // Enable ADC clk
   
/* Set ADC clk <4.5 MHz */
   AD0CR_bit.CLKDIV = (SYS_GetFpclk(24) / 45000000) + 1;
   
/* Disable all interrupts - this is a polling service */
   ADINTEN = 0;
   
/* Enable ADC */
   AD0CR_bit.PDN = 1;
   
   return 1;
}



/*
 * Reads a single ADC channel
 * Parameter in {AIN0, AIN1, AIN5, AIN6}
 *
 * Returns -1 for a parameter error or the 10-bit ADC conversion
 * value
 *
 */
int ADCRead( int Channel ) {
   Int32U AdcData;     /* Value read from ADC */

/* Check parameter in range */
   if ( ( Channel != ANALOG_TRIM_CHANNEL ) &&
        ( Channel != X_CHANNEL ) &&
        ( Channel != Y_CHANNEL ) &&
        ( Channel != Z_CHANNEL ) )
      return -1;

   AD0CR_bit.SEL = 0x00;       /* Deselect previous ADC input */
   
/* Select ADC channel */
   switch ( Channel ) {
   case ANALOG_TRIM_CHANNEL:
     AD0CR_bit.SEL = 1<<5;     /* Select AIN5 - potentiometer */
     break;
   case X_CHANNEL:
     AD0CR_bit.SEL = 1<<1;     /* Select AIN1 - P0.24 - accelerometer X */
     break;
   case Y_CHANNEL:
     AD0CR_bit.SEL = 1<<0;     /* Select AIN0 - P0.23 - accelerometer Y */
     break;
   case Z_CHANNEL:
     AD0CR_bit.SEL = 1<<6;     /* Select AIN6 - P0.12 - accelerometer Z */
   }

   AD0CR_bit.PDN = 1;          /* Enable ADC */

/* Read and wait until conversion complete */
   AD0CR_bit.START = 1;        /* Start conversion */
   AdcData = AD0GDR;           /* Read value */
   while ( ! (AdcData & (1UL << 31) ) ) {
      AdcData = AD0GDR;        /* Read value */
   }

/* Shift 10-bit ADC value down and mask other bits */
   return ((AdcData >> 6) & 0x3FF);
}