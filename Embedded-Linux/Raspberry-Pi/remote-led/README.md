# Remote LED

## Project Description
This Rust driver serves a webpage served by Axum for the user to control an LED remotely.

## Required Crates
- axum
- tokio
- tokio-gpiod
- anyhow
- futures

## Required Hardware
- Raspberry Pi 4B
- LED
- 2k ohm resistor
- 2n2222 Transistor
- 330 ohm resistor
- Breadboard
- Jumper wires

## Connections

### Pi
| Pi Physical GPIO Pin | Purpose | Connection |
| :------: | :------: | :------: |
| 2 | +5V | +5V Rail |
| 6 | GND | GND Rail |
| 11 | GPIO 17 Digital Signal | 2k ohm resistor -> Transistor base

### LED
| LED Pin | Connection |
| :------: | :------: |
| Anode | 330 ohm resistor -> +5V rail |
| Cathode | 2n2222 Transistor Collector |

### Transistor 
| Transistor Pin | Connection |
| :------: | :------: |
| Collector | LED Cathode |
| Emmitter | GND Rail |
| Base | 2k ohm resistor -> Pi Pin 11

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

### Control the LED
- Go to "localIPAddress:3000/" in any web browser