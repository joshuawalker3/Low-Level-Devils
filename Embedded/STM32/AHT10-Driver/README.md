# AHT10 Temperature and Humidity Sensor STM32 Driver

## Overview
This driver was designed for a AHT10 sensor that is connected to a STM32 microcontroller as a peripheral. Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

The reference manual used can be found [here](https://server4.eca.ir/eshop/AHT10/Aosong_AHT10_en_draft_0c.pdf).

## Adding Driver to Project
Add AHT10.h and AHT10.c to the projects Inc and Src directories respectively.

## How To Use This Driver
After the desired I2C bus has been initialized, perform the following operations:

- Add the sensor to the I2C bus and initialze the handle with aht_open
- Initialize the sensor with aht_init
- read data from sensor using aht10_read
- Send commands to the sensor using aht10_ioctrl
- Free memory allocated for the aht10 handle using aht10_close when operations are completed

## Driver Defines

### Macros
_DELAY(os_mode, x) 
- Delays x microseconds. Uses either HAL_Delay or osDelay based upon os_mode.

_CONVERT_TO_IMPERIAL(x)
- Converts celsius to fahrenheit

### Address 
- AHT_ADDR (note: this cannot be changed)

### Timing
- START_DELAY_TIME
- MEASURE_DELAY_TIME

### Command for Reading Data
- MEASURE_COMMAND
- DATA0
- DATA1

### Communication
- SEND_PACKET_SIZE 
- RECEIVE_PACKET_SIZE
- MAX_TIMEOUT

## Enums
### Os_Mode
- NO_RTOS
- RTOS_MODE

### Aht10_Cmd
- POWER_OFF
- POWER_ON
- TEMP_UNIT_METRIC,
- TEMP_UNIT_IMPERIAL

### Temp_Unit
- METRIC
- IMPERIAL

## Structs
### Aht10_HandleTypeDef
#### Members
- I2C_HandleTypeDef* hi2c;
- GPIO_TypeDef* power_pin_port;
- uint16_t power_pin;
- Os_Mode mode;
- Temp_Unit units;
- uint8_t buffer[6];

## Functions
### Function Name
HAL_StatusTypeDef aht10_open(Aht10_HandleTypeDef* aht10, I2C_HandleTypeDef* hi2c, Os_Mode mode)
### Function Description
Attaches sensor to I2C bus and initializes the AHT10 handle
### Parameters
- Aht10_HandleTypeDef* aht10
    - Struct representing AHT10 temperature sensor
- I2C_HandleTypeDef* hi2c
    -  handle to module that contains the I2C configuration
- Os_Mode mode
    - Mode that the sensor will be used in. Must be updated programmatically if conditions change
### Return
- HAL_OK on success, HAL_ERROR otherwise

### Function Name
HAL_StatusTypeDef aht10_init(Aht10_HandleTypeDef* aht10, GPIO_TypeDef* power_pin_port, uint16_t power_pin, Temp_Unit units)
### Function Description
Initializes the AHT10 sensor. Power is supplied to the sensor via GPIO pin. This is due to having to hard reset the sensor after reading data because it will not release the I2C bus. This is a known issue with AHT10 probes. 
### Parameters
- Aht10_HandleTypeDef* aht10
    -  Pointer to the handle for the sensor
- GPIO_TypeDef* power_pin_port
    - GPIO port for the STM32 pin that controls power to the sensor
- uint16_t power_pin 
    - GPIO pin used to power the sensor
- Temp_Unit units
    - Units for temperature
### Return
- HAL_OK if sucessful, HAL_ERROR otherwise

### Function Name
HAL_StatusTypeDef aht10_read(Aht10_HandleTypeDef* aht10, int16_t* temp, uint8_t* humid);
### Function Description
Writes data to LCD to display
### Parameters
- Aht10_HandleTypeDef* aht10
    -  Pointer to the handle for the sensor
- int16_t* temp
    - Pointer to variable to store temperature value
- uint8_t* humid
    - Pointer to variable to store humidity value
### Return
- Status of transmissions

### Function Name
HAL_StatusTypeDef aht10_ioctrl(Aht10_HandleTypeDef* aht10, Aht10_Cmd cmd)
### Function Description
Sends command to LCD
### Parameters
- Aht10_HandleTypeDef* aht10
    -  Pointer to the handle for the sensor
- Aht10_Cmd cmd
    - Command to be performed
### Return
- HAL_OK if sucessful, HAL_ERROR otherwise

### Function Name
HAL_StatusTypeDef aht10_close(Aht10_HandleTypeDef* aht10)
### Function Description
Closes LCD stream and frees allocated memory
### Parameters
- Aht10_HandleTypeDef* aht10
    -  Pointer to the handle for the sensor
### Return
- HAL_OK if sucessful, HAL_ERROR otherwise