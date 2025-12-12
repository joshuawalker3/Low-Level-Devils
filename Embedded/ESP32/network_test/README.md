# Network Test

## Project Description
This project connects to a simple TCP server via WiFi

## Required Toolchain
- ESP-IDF Toolchain

## Required Components
- ESP32 Microcontroller
- Host on the local network running a simple TCP server that responds "Hello" when client connects

## Required Tools
- ESP-IDF environment variables must be exported into environment prior to compiling and flashing
- network name and password must be configured using 
```bash
idf.py menuconfig
```

## Build
1. Compile the application
```bash
idf.py build
```
2. Flash the application. Port variable must be updated for the port your microcontroller is on
```bash
idf.py -p $(port) flash
```
3. To monitor serial output
```bash
idf.py -p $(port) monitor