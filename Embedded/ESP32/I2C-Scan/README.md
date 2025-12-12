# I2C Scan

## Project Description
This project scans a connected I2C bus for available addresses and prints them to the serial monitor

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- 1 or more I2C devices

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
3. View serial data
```bash
idf.py -p $(port) monitor
```
