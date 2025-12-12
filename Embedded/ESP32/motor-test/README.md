# Motor Test

## Project Description
This project controls a DC motor with PWM signals. For this I used a pwm controlled PC chasis fan

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- PC Chasis fan (or any DC motor)
- External power supply if needed
- Transistors if external power supply used

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
