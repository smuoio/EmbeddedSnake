#include "includes.h"

/*************************************************************************
 * Function Name: fiq_handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: FIQ handler
 *
 *************************************************************************/
__fiq __arm void FIQ_Handler (void)
{
  while(1);
}

/*************************************************************************
 * Function Name: irq_handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: IRQ handler
 *
 *************************************************************************/
__irq __arm void IRQ_Handler (void)
{
void (*interrupt_function)();
unsigned int vector;

  vector = VICADDRESS;     // Get interrupt vector.
  interrupt_function = (void(*)())vector;
  if(interrupt_function != NULL)
  {
    interrupt_function();  // Call vectored interrupt function.
  }
  else
  {
    VICADDRESS = 0;      // Clear interrupt in VIC.
  }
}

/*************************************************************************
 * Function Name: VIC_Init
 * Parameters: void
 * Return: void
 *
 * Description: Initialize VIC
 *
 *************************************************************************/
void VIC_Init(void)
{
volatile unsigned long * pVecAdd, *pVecCntl;
int i;
  // Assign all interrupt channels to IRQ
  VICINTSELECT  =  0;
  // Disable all interrupts
  VICINTENCLEAR = 0xFFFFFFFF;
  // Clear all software interrupts
  VICSOFTINTCLEAR = 0xFFFFFFFF;
  // VIC registers can be accessed in User or privileged mode
  VICPROTECTION = 0;
  // Clear interrupt
  VICADDRESS = 0;

  // Clear address of the Interrupt Service routine (ISR) for vectored IRQs
  // and disable all vectored IRQ slots
  for(i = 0,  pVecCntl = &VICVECTPRIORITY0, pVecAdd = &VICVECTADDR0; i < 32; ++i)
  {
    *pVecCntl++ = *pVecAdd++ = 0;
  }
}




/*************************************************************************
 * Function Name: InitClock
 * Parameters: void
 * Return: void
 *
 * Description: Initialize PLL and clocks' dividers. Hclk - 288MHz,
 * Usbclk - 48MHz
 *
 *************************************************************************/
void InitClock(void)
{
  // 1. Init OSC
  SCS_bit.OSCRANGE = 0;
  SCS_bit.OSCEN = 1;
  // 2.  Wait for OSC ready
  while(!SCS_bit.OSCSTAT);
  // 3. Disconnect PLL
  PLLCON_bit.PLLC = 0;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  // 4. Disable PLL
  PLLCON_bit.PLLE = 0;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  // 5. Select source clock for PLL
  CLKSRCSEL_bit.CLKSRC = 1; // Selects the main oscillator as a PLL clock source.
  // 6. Set PLL settings 288 MHz
  PLLCFG_bit.MSEL = 24-1;
  PLLCFG_bit.NSEL = 2-1;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  // 7. Enable PLL
  PLLCON_bit.PLLE = 1;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
  // 8. Wait for the PLL to achieve lock
  while(!PLLSTAT_bit.PLOCK);
  // 9. Set clk divider settings
  CCLKCFG   = 6-1;            // 1/6 Fpll
  USBCLKCFG = 6-1;            // 1/6 Fpll - 48 MHz
  PCLKSEL0 = PCLKSEL1 = 0;    // other peripherals
  // 10. Connect the PLL
  PLLCON_bit.PLLC = 1;
  PLLFEED = 0xAA;
  PLLFEED = 0x55;
}


/*************************************************************************
 * Function Name: SYS_GetFsclk
 * Parameters: none
 * Return: Int32U
 *
 * Description: return Sclk [Hz]
 *
 *************************************************************************/
Int32U SYS_GetFsclk(void)
{
Int32U Mul = 1, Div = 1, Osc, Fsclk;
  if(PLLSTAT_bit.PLLC)
  {
    // when PLL is connected
    Mul = PLLSTAT_bit.MSEL + 1;
    Div = PLLSTAT_bit.NSEL + 1;
  }

  // Find clk source
  switch(CLKSRCSEL_bit.CLKSRC)
  {
  case 0:
    Osc = I_RC_OSC_FREQ;
    break;
  case 1:
    Osc = MAIN_OSC_FREQ;
    break;
  case 2:
    Osc = RTC_OSC_FREQ;
    break;
  default:
    Osc = 0;
  }
  // Calculate system frequency
  Fsclk = Osc*Mul*2;
  Fsclk /= Div*(CCLKCFG+1);
  return(Fsclk);
}

/*************************************************************************
 * Function Name: SYS_GetFpclk
 * Parameters: Int32U Periphery
 * Return: Int32U
 *
 * Description: return Pclk [Hz]
 *
 *************************************************************************/
Int32U SYS_GetFpclk(Int32U Periphery)
{
Int32U Fpclk;
pInt32U pReg = (pInt32U)((Periphery < 32)?&PCLKSEL0:&PCLKSEL1);

  Periphery  &= 0x1F;   // %32
  Fpclk = SYS_GetFsclk();
  // find peripheral appropriate periphery divider
  switch((*pReg >> Periphery) & 3)
  {
  case 0:
    Fpclk /= 4;
    break;
  case 1:
    break;
  case 2:
    Fpclk /= 2;
    break;
  default:
    Fpclk /= 8;
  }
  return(Fpclk);
}



void InitMAM() {
   MAMCR_bit.MODECTRL = 0;
   MAMTIM_bit.CYCLES = 3;    // FCLK > 40 MHz
   MAMCR_bit.MODECTRL = 2;   // MAM functions fully enabled
}
