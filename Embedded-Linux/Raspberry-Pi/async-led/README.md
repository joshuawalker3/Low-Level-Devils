# Async-RGB-LED

## Project Description
This Rust driver works asyncronously to get button inputs and toggle different colors on a RGB LED

## Required Crates
- tokio
- tokio-gpiod
- anyhow
- futures

## Required Hardware
- Raspberry Pi 4B
- Common Cathode RGB LED
- 100 ohm resistor
- 330 ohm resistor x 2
- 74HC08 IC (Quad AND gate)
- Breadboard
- Jumper wires

## Connections

### Pi
| Pi Physical GPIO Pin | Purpose | Connection |
| :------: | :------: | :------: |
| 2 | +5V | +5V Rail |
| 6 | GND | GND Rail |
| 11 | GPIO 17 Digital Signal (RED) | 74HC08 Pin 12 |
| 13 | GPIO 27 Digital Signal (GREEN) | 74HC08 Pin 9 |
| 14 | GPIO 22 Digital Signal (BLUE) | 74HC08 Pin 5 |
| 16 | GPIO 23 Digital Signal (RED) | RED Button Rail 1 |
| 18 | GPIO 24 Digital Signal (GREEN) | GREEN Button Rail 1 |
| 22 | GPIO 25 Digital Signal (BLUE) | BLUE Button Rail 1 |

### RGB LED
| LED Pin | Connection |
| :------: | :------: |
| Cathode | GND Rail |
| RED Pin | 100 ohm -> 74HC08 Pin 11 |
| GREEN Pin | 330 ohm -> 74HC08 Pin 8 |
| BLUE Pin | 330 ohm -> 74HC08 Pin 6 |

### RED Button
| Rail | Connection |
| :------: | :------: |
| Rail 1 | Pi Pin 16 |
| Rail 2 | GND Rail |

### GREEN Button
| Rail | Connection |
| :------: | :------: |
| Rail 1 | Pi Pin 18 |
| Rail 2 | GND Rail |

### BLUE Button
| Rail | Connection |
| :------: | :------: |
| Rail 1 | Pi Pin 22 |
| Rail 2 | GND Rail |

### BLUE Button
| Rail | Connection |
| :------: | :------: |
| Pin 1 | GND Rail |
| Pin 2 | GND Rail |
| Pin 3 | Floating |
| Pin 4 | +5V DC Rail |
| Pin 5 | Pi Pin 14 |
| Pin 6 | RGB LED BLUE Pin |
| Pin 7 | GND Rail |
| Pin 8 | RGB LED GREEN Pin |
| Pin 9 | Pi Pin 13 |
| Pin 10 | +5V DC Rail |
| Pin 11 | RGB LED RED Pin |
| Pin 12 | Pi Pin 11 |
| Pin 13 | +5V DC Rail |
| Pin 14 | +5V DC Rail |

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