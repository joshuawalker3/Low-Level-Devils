/*
 * float_sensor.c
 *
 *  Created on: Apr 26, 2025
 *      Author: walke
 */

#include "float_sensor.h"

HAL_StatusTypeDef float_sensor_init(FloatSensor_HandleTypeDef* sensor, GPIO_TypeDef* sensor_gpio_port, uint16_t sensor_signal_pin) {
	if (!sensor_gpio_port) {
		return HAL_ERROR;
	}

	sensor->sensor_gpio_port = sensor_gpio_port;
	sensor->sensor_signal_pin = sensor_signal_pin;

	return HAL_OK;
}

GPIO_PinState float_sensor_status(FloatSensor_HandleTypeDef* sensor) {
	if (!sensor) {
		return GPIO_PIN_RESET; //Failsafe
	}

	return HAL_GPIO_ReadPin(sensor->sensor_gpio_port, sensor->sensor_signal_pin);
}
