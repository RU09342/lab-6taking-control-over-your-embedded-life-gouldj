#include<msp430g2553.h>
long tempInDeg;
long prevTemp = 0;
long currTemp = 0;

//MAIN PROGRAM
void main(void)
{
	// Stop Watch Dog Timer
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

											  // select the P1.6 as the PWM output
	P1DIR |= BIT6;
	P1SEL |= BIT6;
	P1OUT = 0x00;


	// ADC initialization

	ADC10CTL0 = ADC10SHT_3 + SREF_1 + REFON + ADC10ON;

	ADC10CTL1 = INCH_10 + ADC10DIV_3;

	_delay_cycles(30);

	// PWM initialization
	TACTL = TASSEL_1 + MC_1;
	TACCR0 = 1000 - 1;
	TACCTL1 = OUTMOD_7;
	TACCR1 = 500 - 1;

	while (1)
	{
		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
		while (ADC10CTL1 & ADC10BUSY);          // check for ADC conversion is completed

		tempInDeg = (((ADC10MEM - 673) * 423) / 1024) - 10;
		currTemp = tempInDeg;
		if (currTemp > prevTemp + 2)
		{
			TACCR1 = tempInDeg * 20 - 1;
			prevTemp = currTemp;
		}
		if (currTemp < prevTemp + 2)
		{
			TACCR1 = tempInDeg * 20 - 1;
			prevTemp = currTemp;

		}

		_delay_cycles(1000);

	}

}