# Lab 6: Precision Control
Some applications require large amounts of voltage or current, so switching techniques must be used in order to provide the desired output. Other cases however require a finer control over the voltage or current going into them (some even require a control over resistance). So far you have looked at PWM to control the brightness of an LED, is there a way to use this to output a specified voltage or current, or even a specific waveform?

## PWM Part 2
Since you already have the code to perform PWM, then really, the software side of this part of the lab is fairly easy. You need to design a system which can take in a PWM duty cycle over something like UART (or you could have your system read in the position of a potentiometer), and produce that signal on a GPIO. The interesting part comes in when I want the output of your system to be an Analog voltage. In this case, a PWM with a 50% duty cycle should produce roughly Vcc/2 volts. This part of the lab should be done with the MSP430F5529 and the physical circuit should be constructed of an active Low-Pass Filter.

![Alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/Scopes/scope_pwm.png "Scope reading of the PWM with a 100 Ohm Load")

## R2R DAC
*What if your system is noise sensitive or possibly needs more precision than just a PWM signal, you might need to look into using an actual Digital-to-Analog converter. One of the simplest DAC architectures is a R2R ladder. Using the MSP430F5529, you need to generate an 8-bit R2R ladder circuit that can produce "255" voltages between 0V and Vcc. Now how are you actually going to test this, cause I am sure you aren't going to measure 255 voltages on the DMM. You should set up your F5529 so it generates a staircase using a binary counter and then record on the oscilloscope the resulting waveform.*

One thing to note about the MSP430F5529 is the fact that it includes each pin for bit 3 from 0 to 7. Because of that, it becomes simple to traverse across each of these pins by simply incrementing. In order to create a functional DAC that could be read on an oscilloscope, the circuit below had to be built.

![alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/setup.jpg "Circuit built for the R2R DAC.")

![alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/R@R_schematic.png "The circuit in schematic form.")

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

The result of this is an output voltage that starts at 0V and rises in steps after each delay until it reaches 0xFF, about 1.8V, and then begins stepping back down to 0. The resulting waveform is a triangle wave.

![alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/Scopes/R2R_100Load.png "Scope reading of the R2R with a 100 Ohm Load.")

## Loading Effects
Obviously you are going to be making this type of circuitry to drive something. This introduces the idea of loading effect, wherein your circuit will perform differently based on what is going to be attached to it. For each of these implementations, try placing a variety of resistors from 100 ohms up to see what happens to your output signal and comment on what is happening.

![alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/Scopes/R2R_510Load.png "Scope reading of the R2R with a 510 Ohm Load")

![Alt text](lab-6taking-control-over-your-embedded-life-gouldj/Precision Control/Pictures/Scopes/R2R_2kLoad.png "Scope reading of the R2R with a 2k Ohm Load")

## Deliverables
Along with what was asked in each of the parts above, for each implementation, you need to generate at least one triangle wave from your microntroller. This can be done by simply incrementing and decrementing values that are being sent to your circuit. You need to measure the output of each one of these along with taking the FFT on the scope of each one. The span on the FFT will need to go from 1kHz to about 50kHz if possible. You then need to compare the integrity of each signal by analyzing the difference in frequency components.

The README for this part is going to be mainly about the results of your measurement along with information on the implementation. You need to also talk about how you generated the triangle wave, but do not give me a dissertation on it. Since this is going to be talking about hardware, you need to place in the README a Bill Of Materials listing all hardware used as well as link to a Digikey cart which contains the parts needed in the right quantity. You do not need to include things like your F5529 or the breadboard or wires.