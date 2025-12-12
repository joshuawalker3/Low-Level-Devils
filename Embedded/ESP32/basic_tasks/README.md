# Basic FreeRTOS Tasks ESP32

## Project Description
This project utilizes FreeRTOS and 3 Tasks to blink 3 LEDs at different frequencies.

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- 3 LED with 220 ohm resistor or built in LED on a development board

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
