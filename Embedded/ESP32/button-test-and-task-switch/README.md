# Button Test and Task Switching

## Project Description
This project utilizes FreeRTOS and button inputs to switch between lighting 3 LEDs

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- 3 LED with 220 ohm resistor or built in LED on a development board
- 3 Pushbutton configured to pull the appropriate pin high when pressed.
- 3 10k ohm pulldown resistors for the applicable pins

## Required Tools
- ESP-IDF environment variables must be exported into environment prior to compiling and flashing

## Build
1. Compile the application
```bash
idf.py build
```
2. Flash the application. Port variable must be updated for the port your microcontroller is on
```bash
idf.py -p $(port) flash
```
