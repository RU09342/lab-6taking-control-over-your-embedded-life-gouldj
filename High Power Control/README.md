# Lab 6: "High Power" Control
####  Joshua Gould and Jack Pedicone
##### Created - 11-25-2017
##### Updated - 11-25-2017

## Dependencies
* Relay
* MSP430G2553
* MOSFET (nMOS)
* Power Resistor
* LEDs (optional)

## Set Requirements
"For this part of the lab, you need to focus on the different types of switching circuits along with the differences in inductive and resistive loads. The idea behind this part of the lab is to learn how not only to drive things that may require a high voltage or high current, but how to then protect your microcontroller from them."
"Using the MSP430G2553, control the state of a relay to drive a power resistor with +12V. Your README for this part should include a screenshot of the output of your MSP and the voltage across the resistor. Try to figure out the switching speed limitations of the relay experimentally. Along with what was asked in each part, you will need to utilize the DMM to determine what the current draw from each switch is and if that falls into spec with the Microcontroller."
#### Tasks

* [ ] Protect MSP430G2553 from "High Voltage" (12V)
* [ ] Control the state of the relay to drive a power resistor
* [ ] Output voltage of the MSP430G2553 and voltage across power resistor for both switches
* [ ] Find switching speeds of relay and MOSFET switch experimentally

## Compatibility
* MSP430G2553

## Functionality Description
Create a safe, high power circuit enviroment to operate a MSP430 with a switch

### Relay Switching

## Relay Switch Circuit

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/Circuit_MSP430.jpg" width="600"/>

The relay was found to always switch while 12V ran through it, although when it was tested with 7V and it was found to still function. By hooking LEDS up to both the Normally Open and Normally Closed sides of the relay, the switching of the relay became easier to visualize.

## Relay Switch Schematic

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/relay_circuit_schematic.PNG">

The type N MOSFET used in this circuit was essentially used for driving the 12V through the relay. The gate of the MOSFET

## Relay Switch in Action

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/relay.gif">

Across the 5 Watt, 100Ω power resistor, the voltage was found to be 7.95V, and the current draw was found to be 4mΩ, which is below the 6mΩ limit that the MSP was able to handle.  

An oscilloscope was used to find the frequency where the square wave "breaks" for both the relay switch and the MOSFET Switch. This point was found by finding the point where the amplitude of the wave from the output of the MSP430 or the function generator was less than its original amplitude. For the relay, it was found that a frequency of 370 Hz is where the waveform begins to break.

[insert scope screenshots]

### MOSFET Switching

## MOSFET Switch Circuit

[insert circuit picture here]

## MOSFET Switch Schematic

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/mosfet_switch_schematic.png">

# MOSFET Switch

Voltage: 7.21V
Current draw: 72.1 mΩ

# MSP430G2553 Specifications

Output voltage: 1.79V


### Switching Speeds

MOSFET Switching speed: 25kHz




