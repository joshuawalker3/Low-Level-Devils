# Solenoid STM32 Driver

## Overview
This driver was designed for solenoid control using a STM32 microcontroller. It is assumed that the solenoid operates at a higher voltage than that produced by a STM32 microcontroller and thus a digital signal is used to activate or deactivate the soloenoid (througha transistor for example). Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

## Adding Driver to Project
- To core/Inc add:
    - solenoid.h
- To core/Src add:
    - solenoid.c

## How To Use This Driver
After the desired GPIO pin has been initialized:

- Initialize the signal with soleonid_init
- change status of solenoid with solenoid_control

## Enums
### Solenoid_Status
- SOL_OFF
- SOL_ON

## Structs
### Solenoid_HandleTypeDef
#### Members
- `GPIO_TypeDef*` sol_gpio_port;
- `uint16_t` sol_signal_pin;
- `Solenoid_Status` status;

## Functions
### Function Name
`HAL_StatusTypeDef` solenoid_init(Solenoid_HandleTypeDef* sol, GPIO_TypeDef* sol_gpio_port, uint16_t sol_signal_pin, Solenoid_Status status)
#### Function Description
Initializes the solenoid control signal
#### Parameters
- `Solenoid_HandleTypeDef*` sol
    - The struct representing the solenoid control signal
- `GPIO_TypeDef*` sol_gpio_port
    - The GPIO port for the control signal
- `uint16_t` sol_signal_pin
    - The GPIO pin for the signal
- `Solenoid_Status` status
    - The initial state for the solenoid
#### Return
- HAL_OK on success, other HALStatusTypeDef on failure

### Function Name
`void` solenoid_control(Solenoid_HandleTypeDef* sol, Solenoid_Status status)
#### Function Description
Updates the state of the solenoid control signal
#### Parameters
- `Solenoid_HandleTypeDef*` sol
    - The struct representing the solenoid control signal
- `Solenoid_Status` status
    - The requested state for the solenoid
#### Return
- None
