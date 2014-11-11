#include <intrinsics.h>
#include "includes.h"

/*
 * DACInit()
 *
 * Initialise DAC channel on AOUT - P0.26
 *
 * The DAC output is connected to an audio output circuit on the LPC2378 board
 * AOUT analogue signal is amplified, LP filtered and then made available via
 * the "HEADPHONE" jack.  Both jack rigs are common
 *
 * Assigns PCLK_DAT in the PCLK_SEL0 register
 * Selects AOUT via the PINSEL1 rgister
 */
void DACInit(){
  PCLKSEL0 &= ~(1UL<<20 | 1UL << 21); /* Select PCLK_DAC - 00 in bits 20:21 */
  PINSEL1_bit.P0_26= 2;               /* Select DAC */
}


/*
 * DACWrite()
 *
 * Output a 10-bit sample to the DAC
 *
 * Parameters:
 *       sample: 10-bit sample in bit 0..9
 *       bias: the bias selection in {0,1}
 *             a bias of 0 selects a max. settle time of 1us
 *             a bias value of 1 selects a settle time of 2.5us
 * 
 * Returns -1 for a parameter error and 1 otherwise
 */
int DACWrite( int VALUE, int BIAS ) {

/* Check the bias parameter */
   if ( ( BIAS != 0) && ( BIAS != 1 ) )
      return -1;

/* Output to the DA Converter register
 * bits 15:6 are value bits
 * bit 16 is the bias selection
 */
   DACR= (( VALUE & 0x3FF) << 6) | ( (BIAS & 0x1 << 16 ));
   return 1;
}