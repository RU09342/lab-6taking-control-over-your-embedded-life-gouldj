# Lab 6: Open Loop Systems
#### Joshua Gould
##### Created - 11-25-2017
##### Updated - 11-25-2017

## Library Used
msp430.h - default library

## Dependencies
* MSP430
* Power Reistor
* 5V Regulator
* PWM Fan
* Phototransistor
* Multimeter and oscilloscope

## Set Requirements
"Focus on system modeling getting a system to a desirable state. For this lab, you will be attempting to keep a voltage regulator within a specific temperature range using a DC fan which you will have control over. For this part to be a success, you need to figure out what is the minimum fan speed you need to cool off the regulator so that is stays operational. You will need to take a 5V regulator from the back of the lab and drop the output across a 100 ohm power resistor (1 watt should do the trick). The input to the voltage regulator will be between 15-20V. It would be really useful to see what the temperature of your system is so you can determine the performance of your system. This can be done either by displaying the current temperature over a display, passing the information over UART, or other ways as well. Remember that UART is Asynchronous, meaning that you can send information whenever you would like from your controller back to a PC, it doesn't have to be reactionary."
"Your README needs to contain schematics of your system, the plot of the plot of the temperature and input voltages at the 5C steps, and a brief talk about why you chose the processor you did along with the control technique for the fan. As always, you should include a brief description of the code. You need to also include information on how to use your control software, including what inputs it is expecting and what range of values you are expecting."

### System Modelling
"For starters, you need to figure out with your fan at MAX what the temperature that the voltage regulator reaches. Your thermistors/PTATs/Whatever else you want to use to measure temperature may not be calibrated, so your results may be consistently off with reality, but for now that is ok. After figuring this out, in increments of about 5C, see what fan speed you need to have to maintain that temperature. Do this until your regulator gets down to about 30C-40C, keeping a record of what your applied Duty Cycles or voltages were. Then using this information, attempt to find a transfer function between the applied input and the resulting temperature to model the system behavior. A simple way to do this is in MATLAB or Excel to plot your applied input on the x-axis, and your steady state temperature on your y-axis and attempt a line fit."

### Open Loop Control System
"You then need to use this information to make a final open loop control system where a user can state what temperature they want the regulator to be maintained at, and the microcontroller will basically calculate/look up what it needs to set the fan to. Do not over complicate this and make it some elaborate system. All this needs to do is some math and set a duty cycle or voltage, and display in some capacity the current temperature of the system as you are measuring it."

#### Tasks
* [x] Create circuit for heating/cooling
* [x] Read tempeture of system over UART using ADC
* [ ] System temperature plot (5C steps)
* [ ] Reason for processor choice
* [ ] Control technique for fan
* [ ] Code description
* [ ] Model max tempeture
* [ ] Plot System
* [ ] User can control tempeture

## Circuit 
#### Picture
![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Open%20Loop%20Systems/Open%20Loop%20Ciruit/Circuit%20Pictures/Circuit_top.jpg)
#### Tempeture Sense System
![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Open%20Loop%20Systems/Open%20Loop%20Ciruit/Circuit%20Pictures/temp-system.jpg)
#### Fan PWM System
![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Open%20Loop%20Systems/Open%20Loop%20Ciruit/Circuit%20Pictures/pwm-system.jpg)
#### Schematic
![alt text](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Open%20Loop%20Systems/Open%20Loop%20Ciruit/OpenLoopCircuit.PNG)

## System Table

| Hex 	| PWM (%) | TempC |
| :---: |:-------:| :----:|
| 0     | 0	      | >100	|
| 1A    | 10	    | 51	  |
| 33    | 20	    | 43	  |
| 4D    | 30	    | 40	  |
| 66    | 40	    | 38	  |
| 80    | 50	    | 37.5	|
| 99    | 60	    | 36.5	|
| B2    | 70	    | 35.7	|
| CC    | 80	    | 35.3	|
| E6    | 90	    | 35.1	|
| FF    | 100	    | 35	  |

## System Plot

![Alt Text}(https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/Open%20Loop%20Systems/Open%20Loop%20Ciruit/TempvsPWMchart.PNG)

## Code Functionality
### MSP430FR5994
The MSP430FR5994 was chosen for its 12-Bit Analog-to-Digital Converter (ADC), Six 16-Bit Timers With up to Seven Capture/Compare Registers Each, and its ability to hold up to 20 External Input Channels. The integrated capacitor for offline power is not necessary in this lab, however it is useful for when your laptop dies and you miss some temperature measurements. Additionally, this MSP430 was experimented with in  the pevious milestone.
### 
