# Soil Moisture Sensor STM32 Driver

## Overview
This driver was designed to monitor a soil moisture sensor using a STM32 microcontroller. Since the vendor HAL was used for implementation, this driver should be able to be used with any STM32 microcontrtoller. This driver can be used both with and without and RTOS with no changes to the code.

## Adding Driver to Project
- To core/Inc add:
    - soil_moisture_sensor.h
- To core/Src add:
    - soil_moisture_sensor.c

## How To Use This Driver
After the desired ADC header has been initialized:

- Initialize the sensor with soil_moisture_sensor_init
- Measure and read status using soil_moisture_sensor_measure
- Read status without obtaining new measurement using soil_moisture_sensor_get_soil_status

## Enums
### SOIL_STATUS
- SATURATED
- OK
- DRY

## Structs
### SoilMoistSensor_HandleTypeDef
#### Members
- `ADC_HandleTypeDef*` adc_handle;
- `Soil_Status` soil_status;

## Functions
### Function Name
`HAL_StatusTypeDef` soil_moisture_sensor_init(SoilMoistSensor_HandleTypeDef* sensor, ADC_HandleTypeDef* adc_handle)
#### Function Description
Initializes the soil moisture sensor
#### Parameters
- `SoilMoistSensor_HandleTypeDef*` sensor
    - The struct representing the soil moisture sensor
- `ADC_HandleTypeDef*` adc_handle
    - The adc handle for the adc port connected to the soil moisture sensor 
#### Return
- HAL_OK on success, other HALStatusTypeDef on failure

### Function Name
`Soil_Status` soil_moisture_sensor_measure(SoilMoistSensor_HandleTypeDef* sensor)
#### Function Description
Obtains a measurement of soil moisture
#### Parameters
- `SoilMoistSensor_HandleTypeDef*` sensor
    - The struct representing the soil moisture sensor
#### Return
- Status of the soil moisture level determined from the current reading

### Function Name
`Soil_Status` soil_moisture_sensor_get_soil_status(SoilMoistSensor_HandleTypeDef* sensor)
#### Function Description
Get status of soil moisture determined by the last call to soil_moisture_sensor_measure
#### Parameters
- `SoilMoistSensor_HandleTypeDef*` sensor
    - The struct representing the soil moisture sensor
#### Return
- Status of the soil moisture level determined by the last call to soil_moisture_sensor_measure