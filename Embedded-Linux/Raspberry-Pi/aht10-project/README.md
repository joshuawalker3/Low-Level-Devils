# Async AHT10 Sensor

## Project Description
This Rust crate allows a user to get data from an AHT10 Temp/Humidity Sensor asynchronously.

## Required Crates
- tokio
- tokio-gpiod
- anyhow
- futures
- i2cdev
- byteorder

## Required Hardware
- Raspberry Pi 4B
- AHT10 Module
- Breadboard
- Jumper wires

## Connections

### Connection Note
The AHT10 module will hold the I2C bus after it is addressed. To remedy this I power cycle the unit as needed via a GPIO Pin.

### Pi
| Pi Physical GPIO Pin | Purpose | Connection |
| :------: | :------: | :------: |
| 3 | SDA | AHT10 SDA |
| 5 | SCL | AHT10 SCL | 
| 6 | GND | GND Rail |
| 11 | GPIO 17 Digital Signal | AHT10 Module Vcc|


### AHT10
| AHT10 Pin | Connection |
| :------: | :------: |
| Vcc | Pi Pin 11 |
| GND | GND Rail |
| SDA | Pi Pin 3 |
| SCL | Pi Pin 5 |

## Build and run
### Build on Pi
1. 
```bash
cargo build
```

2. 
```bash
./path/to/executable 
```

### Build on Host
1. (On Host)
```bash
cargo build --release --target aarch64-unknown-linux-gnu
```

2. (On Host)
```bash
scp target/aarch64-unknown-linux-gnu/release/blinky <user>@<ip>:/path/to/desired/dir
```
This transfers the executable to your pi. Replace user and ip with your equipments information.

3. (On Pi)
```bash
./path/to/executable 
```