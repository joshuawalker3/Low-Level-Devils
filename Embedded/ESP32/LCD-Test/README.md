# LCD Test

## Project Description
This project tests various functions of an I2C based LCD

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- I2C LED

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
