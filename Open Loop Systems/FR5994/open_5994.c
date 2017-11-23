//******************************************************************************
//														+
//                 MSP430FR5994							|_____
//              ---------------								 |
//         /|\  |          VCC|- 3.3V						FAN
//          |   |             |							____ |
//          --  |GND      P1.5|--< adc temp		NMOS	|
//              |         P1.4|--> PWM	---------------[|
//              |			  |				|___>>>>____|
//              |             |					R1		ö GND
//				|		  P1.0|--> LED
//              -------------------
//  adc_value (P1.5) to LM35
//	PWM		  (P1.4) to FAN / NMOS
//
//  Filename : open_5994.c
//
//  Created on : November 15, 2017
//  Updated on : November 19, 2017
//  Author : Joshua Gould
//
//******************************************************************************
//
//Reference/Mad Help from Jessica Wozniak & Russell Trafford
//
//******************************************************************************

#include <msp430.h>

#define ADC12 BIT5
#define LED1 BIT0
#define RXD BIT4
#define TXD BIT3
#define OUTPUT BIT4		//Pin 1.4 is the TB0CCR1 output pin.

void TimerAInit(void);
void TimerBInit(void);
void ADC12Init(void);
void UARTInit(void);
void GPIOInit(void);
void PinInit(void);

unsigned volatile int adc_in = 0;
volatile float tempC = 0;
volatile float tempF = 0;
volatile float voltage = 0;

void GPIOInit()
{
	P1OUT &= ~BIT0;                         // Clear LED to start
	P1DIR |= BIT0;                          // P1.0 output
	P1SEL1 |= ADC12;                         // Configure P1.5 for ADC
	P1SEL0 |= ADC12;
}
void PinInit(void)
{
	//For pin 1.4, P1DIR = 1, P1SEL0 = 1, P1SEL1 = 0.
	P1DIR |= OUTPUT; //Pin 1.4
	P1SEL1 &= ~OUTPUT;
	P1SEL0 |= OUTPUT;
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	PM5CTL0 &= ~LOCKLPM5; //Disable HIGH Z mode

	PinInit();                    //Pin Init
	GPIOInit();
	TimerAInit();                  //Timer Function call
	TimerBInit();                  //Timer Function call
	UARTInit();                   //UART Function call


	while (REFCTL0 & REFGENBUSY);            // If ref generator busy, WAIT
	REFCTL0 |= REFVSEL_0 + REFON;           // Enable internal 1.2 reference

	ADC12Init();                  //ADC10 Function call

	while (!(REFCTL0 & REFGENRDY));          // Wait for reference generator
	__enable_interrupt(); //Enable interrupts.

	while (1)
	{

		__bis_SR_register(LPM0 + GIE); // Enter LPM0, interrupts enabled
		__no_operation(); // For debugger
	}
}
//ADC ISR
#pragma vector=EUSCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG))
	{
	case USCI_NONE: break;
	case USCI_UART_UCRXIFG:
		while (!(UCA0IFG&UCTXIFG));

		TB0CCR1 = 255 - UCA0RXBUF;      //duty cycle for FAN

		__no_operation();
		break;

	case USCI_UART_UCTXIFG: break;
	case USCI_UART_UCSTTIFG: break;
	case USCI_UART_UCTXCPTIFG: break;

	default:
		break;
	}
}



void TimerBInit(void)
{
	TB0CCTL1 = OUTMOD_3; //Set OUTMOD_3 (set/reset) for CCR1
						 //Set initial values for CCR1
	TB0CCR1 = 200;
	TB0CCR0 = 255 - 1; //Set CCR0 for a ~1kHz clock.
	TB0CTL = TBSSEL_2 + MC_1; //Enable Timer B0 with SMCLK and up mode.
}

void UARTInit(void)
{

	CSCTL0_H = CSKEY_H;                         // Unlock CS registers
	CSCTL1 = DCOFSEL_3 | DCORSEL;               // Set DCO to 8MHz
	CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;       // Set all dividers
	CSCTL0_H = 0;                               // Lock CS registers

	P2SEL0 &= ~(BIT0 | BIT1);                   //Configure pin 2.0 to RXD
	P2SEL1 |= BIT0 + BIT1;                        //Configure pin 2.1 to TXD

												  // Configure USCI_A0 for UART mode
	UCA0CTLW0 = UCSWRST;                        // Put eUSCI in reset
	UCA0CTLW0 |= UCSSEL__SMCLK;                 // CLK = SMCLK
	UCA0BRW = 52;                               // 8000000/16/9600
	UCA0MCTLW |= UCOS16 | UCBRF_1 | 0x4900;
	UCA0CTLW0 &= ~UCSWRST;                      // Initialize eUSCI
	UCA0IE |= UCRXIE;                           // Enable USCI_A0 RX interrupt
}
void ADC12Init(void)
{
	ADC12CTL0 = ADC12SHT0_2 + ADC12ON;      // Set sample time
	ADC12CTL1 = ADC12SHP;                   // Enable sample timer
	ADC12CTL2 |= ADC12RES_2;                // 12-bit conversion results
	ADC12MCTL0 = ADC12INCH_5 | ADC12VRSEL_1;// Vref+ = , Input
	ADC12IER0 |= ADC12IE0;                  // Enable ADC conv complete interrupt
	P1OUT = BIT0;

}

void TimerAInit(void) {
	TA0CCTL0 = CCIE;
	TA0CCTL1 = OUTMOD_3;
	TA0CCR1 = 256; //Red
	TA0CCR0 = 4096 - 1; //Set CCR0 for a ~1kHz clock.
	TA0CTL = TASSEL_1 + MC_1 + ID_3;
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	ADC12CTL0 |= ADC12SC | ADC12ENC;
}
//ADC ISR
#pragma vector=ADC12_B_VECTOR
__interrupt void ADC12ISR(void)
{
	adc_in = ADC12MEM0;
	voltage = in * 0.00029;        //converts ADC to voltage
	tempC = voltage / 0.01;           //converts voltage to Temp C
	tempF = ((9 * tempC) / 5) + 32;             //Temp C to Temp F
	while (!(UCA0IFG&UCTXIFG));
	UCA0TXBUF = tempF;
}
