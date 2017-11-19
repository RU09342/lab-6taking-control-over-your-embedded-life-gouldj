/*LAB 6 R2R 

**Josh Gould and Jack Pedicone**

Updated - 11/18/17

Credit to Nick Gorab for the code

*/

#include <msp430.h>

int i = 0;


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
    pinInit();

    P3OUT = 0x00;

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
}