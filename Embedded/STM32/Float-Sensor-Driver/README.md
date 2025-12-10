# Float Sensor STM32 Driver

## Overview
This driver was designed monitoring a simple liquid float sensor using a STM32 microcontroller. Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

## Adding Driver to Project
- To core/Inc add:
    - float_sensor.h
- To core/Src add:
    - float_sensor.c

## How To Use This Driver
After the desired GPIO pin has been initialized:

- Initialize the peripheral with float_sensor_init
- Retrieve status of solenoid with float_sensor_status


## Structs
### FloatSensor_HandleTypeDef
#### Members
- `GPIO_TypeDef*` sensor_gpio_port;
- `uint16_t` sensor_signal_pin;

## Functions
### Function Name
`HAL_StatusTypeDef` float_sensor_init(FloatSensor_HandleTypeDef* sensor, GPIO_TypeDef* sensor_gpio_port, uint16_t sensor_signal_pin)
#### Function Description
Initializes the float sensor monitoring peripheral
#### Parameters
- `FloatSensor_HandleTypeDef*` sensor
    - The struct representing the sensor
- `GPIO_TypeDef*` sensor_gpio_port
    - The GPIO port for the sensing line
- `uint16_t` sensor_signal_pin
    - The GPIO pin for the sensing line
#### Return
- HAL_OK on success, other HALStatusTypeDef on failure

### Function Name
`GPIO_PinState` float_sensor_status(FloatSensor_HandleTypeDef* sensor)
#### Function Description
Updates the state of the solenoid control signal
#### Parameters
- `FloatSensor_HandleTypeDef*` sensor
    - The struct representing the sensor
#### Return
- The status of the pin that is sensing the signal from the float sensor
