# ATMega328P Blinky

## Project Description
Standard Blinky project

## Required Toolchain
- AVR Toolchain

## Required Components
- ATMega328P Microcontroller
- LED with 220 ohm resistor or built in LED on a development board

## Required Tools
- Make

## Build
1. Compile the application
```bash
make
```
2. Flash the application. Port variable must be updated in the makefile for the port your microcontroller is on
```bash
make upload
```
