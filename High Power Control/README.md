# Lab 6: "High Power" Control
####  Joshua Gould and Jack Pedicone
##### Created - 11-25-2017
##### Updated - 11-25-2017

## Dependencies
* Relay
* MSP430G2553
* MOSFET (nMOS)
* LEDs (optional)

## Set Requirements
"For this part of the lab, you need to focus on the different types of switching circuits along with the differences in inductive and resistive loads. The idea behind this part of the lab is to learn how not only to drive things that may require a high voltage or high current, but how to then protect your microcontroller from them."
"Using the MSP430G2553, control the state of a relay to drive a power resistor with +12V. Your README for this part should include a screenshot of the output of your MSP and the voltage across the resistor. Try to figure out the switching speed limitations of the relay experimentally. Along with what was asked in each part, you will need to utilize the DMM to determine what the current draw from each switch is and if that falls into spec with the Microcontroller."
#### Tasks
* [ ] Find differences in inductive and resistive loads
* [ ] Protect MSP430G2553 from "High Voltage" (12V)
* [ ] Control the state of the relay to drive a power resistor
* [ ] Output voltage of the MSP430G2553 and voltage across power resistor for both switches
* [ ] Find switching speeds of relay and MOSFET switch experimentally

## Compatibility
* MSP430G2553

## Functionality Description
Create a safe, high power circuit enviroment to operate a MSP430 with a switch

### Relay Switch Circuit

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/Circuit_MSP430.jpg" width="600"/>

### Relay Switch Schematic

<img src = "https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-gouldj/blob/master/High%20Power%20Control/Images/relay_circuit_schematic.PNG"

### Voltage Across Power Resistor

# Relay Switch

Voltage: 7.95V
Current Draw: 79.5 mΩ. 

# MOSFET Switch

Voltage: 7.21V
Current draw: 72.1 mΩ

### Switching Speeds






