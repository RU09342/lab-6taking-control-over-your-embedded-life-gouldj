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

  // SMCLK, up mode, divide by 8
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
