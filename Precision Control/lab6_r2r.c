/*
Credit goes to Matt Mammarelli for this code
*/

//MSP430F5529 R2R Ladder

#include <msp430f5529.h>

void main(void)
{
  //Stop Watchdog Timer
  WDTCTL = WDTPW + WDTHOLD;

  // Set P1.2 , P1.3, P1.4, P1.5, P2.0, and P7.4 as outputs (PWM)
  P1DIR |= BIT2+BIT3+BIT4+BIT5;
  P7DIR |= BIT4;
  P2DIR |= BIT0;

  P1SEL |= BIT2+BIT3+BIT4+BIT5;
  P7SEL |= BIT4;
  P2SEL |= BIT0;

  //For Pin 7.4
  TB0CCR0 = 1024;
  TB0CCTL2 = OUTMOD_7;
  TB0CCR2 = 640;

  //For Pin 2.0
  TA1CCR0 = 1024;
  TA1CCTL1 = OUTMOD_7;
  TA1CCR1 = 768;

  // PWM Period about 1khz
  TA0CCR0 = 1024;

  // CCR1-4 set to Reset/Set
  TA0CCTL1 = OUTMOD_7;
  TA0CCR1 = 128;

  TA0CCTL2 = OUTMOD_7;
  TA0CCR2 = 256;

  TA0CCTL3 = OUTMOD_7;
  TA0CCR3 = 384;

  TA0CCTL4 = OUTMOD_7;
  TA0CCR4 = 512;

  // SMCLK, up mode, clear TAR for TA0-2CTL
  TA0CTL = TASSEL_2 + MC_1 + TACLR;
  TA1CTL = TASSEL_2 + MC_1 + TACLR;
  TB0CTL = TBSSEL_2 + MC_1 + TBCLR;

  //Low power mode and general interrupt enable
  __bis_SR_register(LPM0_bits + GIE);

  //Debug
  __no_operation();
}
