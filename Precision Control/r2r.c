/*Lab 6 Precision Control - R2R DAC 

Jack Pedicone

Created - 11/18/17
Updated - 11/25/17

Credit to Nick Gorab for the code

*/

#include <msp430F5529.h>

int i = 0; //variable used for counting

void pinInit(void){
    P3DIR |= BIT0   // P3.0 for R2R
          |  BIT1   // P3.1 for R2R
          |  BIT2   // P3.2 for R2R
          |  BIT3   // P3.3 for R2R
          |  BIT4   // P3.4 for R2R
          |  BIT5   // P3.5 for R2R
          |  BIT6   // P3.6 for R2R
          |  BIT7;  // P3.7 for R2R
}

void main(void){
    WDTCTL = WDTPW + WDTHOLD;   // Disables Watchdog Timer
    pinInit(); //Pins 3.0 to 3.7 correspond to an 8-bit binary number from 0 (0x00) to 255 (0xFF)

    P3OUT = 0x00; //Initialize the number as 0x00, so all the pins are off

    while(1){
        while(i<255){
            P3OUT++;
            i++;
            __delay_cycles(1000);
        }
        while(i>0){
            P3OUT--;
            i--;
            __delay_cycles(1000);
        }
    }
	//Counts to 255, turning on the pins that correlate, then counts back down. The result is a staircase or triangular waveform.
}