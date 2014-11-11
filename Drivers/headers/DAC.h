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
void DACInit();


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
int DACWrite( int VALUE, int BIAS );