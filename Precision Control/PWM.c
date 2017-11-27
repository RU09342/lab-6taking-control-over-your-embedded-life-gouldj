/*
Lab 6 Precision Control - PWM
Jack Pedicone
Created 11-18-17
Updated 11-25-17
*/

// Software PWM for the MSP430G2553

#include <msp430f5529.h>

void main(void)
{
  //stop watchdog timer
  WDTCTL = WDTPW + WDTHOLD;

  // P1.2  output
  P1DIR |= BIT2;
  P1SEL |= BIT2;

  // PWM Period
  TA0CCTL0 = CCIE;
  TA0CCR0 = 60000;
  TA0CCR1 = 0;
  TA0CCTL1 = OUTMOD_7;

  // SMCLK, up mode
  TA0CTL = TASSEL_2 + MC_1 + TACLR;
  TA0CTL |= (BIT6 + BIT7);

  // Low power mode
  __bis_SR_register(LPM0_bits + GIE);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void debounce(void)
{
    TA0CCR1 = TA0CCR1 + 100;
}
