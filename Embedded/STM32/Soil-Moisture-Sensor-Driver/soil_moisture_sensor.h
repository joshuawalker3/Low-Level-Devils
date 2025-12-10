/*
 * soil_moisture_sensor.h
 *
 *  Created on: May 3, 2025
 *      Author: walke
 */

#ifndef INC_SOIL_MOISTURE_SENSOR_H_
#define INC_SOIL_MOISTURE_SENSOR_H_

#include "main.h"

#define DRY_BOUNDARY 2435
#define SATURATED_BOUNDARY 1810

typedef enum {
	SATURATED,
	OK,
	DRY
} Soil_Status;

typedef struct {
	ADC_HandleTypeDef* adc_handle;
	Soil_Status soil_status;
} SoilMoistSensor_HandleTypeDef;


HAL_StatusTypeDef soil_moisture_sensor_init(SoilMoistSensor_HandleTypeDef* sensor, ADC_HandleTypeDef* adc_handle);
Soil_Status soil_moisture_sensor_measure(SoilMoistSensor_HandleTypeDef* sensor);
Soil_Status soil_moisture_sensor_get_soil_status(SoilMoistSensor_HandleTypeDef* sensor);

#endif /* INC_SOIL_MOISTURE_SENSOR_H_ */
