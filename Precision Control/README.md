# Lab 6: Precision Control
#### Jack Pedicone
##### Created - 11-18-2017
##### Updated - 11-25-2017

## Dependencies
* MSP430F5529
* TL072

## Set Requirements
"Some applications require large amounts of voltage or current, so switching techniques must be used in order to provide the desired output. Other cases however require a finer control over the voltage or current going into them (some even require a control over resistance). So far you have looked at PWM to control the brightness of an LED, is there a way to use this to output a specified voltage or current, or even a specific waveform?"

#### Tasks
* [ ] Design a PWM with an analog output voltage 
* [ ] Generate an 8-bit R2R ladder circuit that can produce "255" voltages between 0V and Vcc
* [ ] Record triangle wave on oscilloscope
* [ ] Test DAC using a variety of load resistances
* [ ] Compare the integrity of each signal by analyzing the difference in frequency components

```c
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
```

The code above simply created a waveform from pin 1.2 of the MSP. This wave could become a triangle wave by using a third order low pass filter hooked up to a buffer.

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/PWM_circuit.jpg">

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/PWM_schematic.png">

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/Scopes/pwm-wave2.png">

### R2R DAC

One thing to note about the MSP430F5529 is the fact that it includes each pin for bit 3 from 0 to 7. Because of that, it becomes simple to traverse across each of these pins by simply incrementing. In order to create a functional DAC that could be read on an oscilloscope, the circuit below had to be built.

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/setup.jpg">

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/R2R_schematic.png">

The outputs of each pin from 3.0 to 3.7 correspond to the 8 bit binary number that needs to count from 0 (0x00) to 255 (0xFF), and then back down to zero. The output voltage of the F5529 would only leave one of the 2k resistors when its respective pin is turned on. 

```c
while(1){
        while(i < 255){
            P3OUT++;
            i++;
            __delay_cycles(1000);
        }
        while(i > 0){
            P3OUT--;
            i--;
            __delay_cycles(1000);
        }
   }
```

The result of this is an output voltage that starts at 0V and rises in steps after each delay until it reaches 0xFF, about 1.8V, and then begins stepping back down to 0. The resulting waveform is a "staircase" wave, or a triangle wave when zoomed out.

### Loading Effects
"Obviously you are going to be making this type of circuitry to drive something. This introduces the idea of loading effect, wherein your circuit will perform differently based on what is going to be attached to it. For each of these implementations, try placing a variety of resistors from 100 ohms up to see what happens to your output signal and comment on what is happening."

The load of both the PWM and the R2R DAC were tested with three different resistances: 100, 510, and 2k. Below are screenshots from the R2R DAC.

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/Scopes/R2R_100Load.png">

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/Scopes/R2R_510Load.png">

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Precision%20Control/Pictures/Scopes/R2R_2kLoad.png">

As expected, the value of the load resistance did not make a huge difference in the output voltage. Summing up the values of the resistances of the circuits would show that a very high resistance would be needed to make a noticable difference. For reference, the output voltage without a load is 3.33 V.

For the triangle waves above, the FFT was analyzed from a range of 1kHz to 50kHz. There were no major peaks or cliffs in the frequency overall.

### Bill of Materials

Part Number | Part Name | Quantity
------------ | ------------ | ------------
CFR-25JB-52-2K | 2k resistor | 9
CFR-25JB-52-1K | 1k resistor | 10
FK24X5R0J156M | 15uF capacitor | 3
TL072CDT | Op Amp | 1

