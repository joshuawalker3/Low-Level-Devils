/*
 * soil_moisture_sensor.c
 *
 *  Created on: May 3, 2025
 *      Author: walke
 */

#include "soil_moisture_sensor.h"

HAL_StatusTypeDef soil_moisture_sensor_init(SoilMoistSensor_HandleTypeDef* sensor, ADC_HandleTypeDef* adc_handle) {
	if (!adc_handle) {
		return HAL_ERROR;
	}

	sensor->adc_handle = adc_handle;

	soil_moisture_sensor_measure(sensor);

	return HAL_OK;
}

Soil_Status soil_moisture_sensor_measure(SoilMoistSensor_HandleTypeDef* sensor) {
	  HAL_ADC_Start(sensor->adc_handle);

	  HAL_ADC_PollForConversion(sensor->adc_handle, HAL_MAX_DELAY);

	  uint32_t moisture_raw = HAL_ADC_GetValue(sensor->adc_handle);

	  if (moisture_raw > DRY_BOUNDARY) {
		  sensor->soil_status = DRY;
		  return DRY;
	  } else if (moisture_raw > SATURATED_BOUNDARY) {
		  sensor->soil_status = OK;
		  return OK;
	  } else {
		  sensor->soil_status = SATURATED;
		  return SATURATED;
	  }
}

Soil_Status soil_moisture_sensor_get_soil_status(SoilMoistSensor_HandleTypeDef* sensor) {
	return sensor->soil_status;
}
