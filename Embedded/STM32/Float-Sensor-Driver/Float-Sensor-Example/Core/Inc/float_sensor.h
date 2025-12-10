/*
 * float_sensor.h
 *
 *  Created on: Apr 26, 2025
 *      Author: walke
 */

#ifndef INC_FLOAT_SENSOR_H_
#define INC_FLOAT_SENSOR_H_

#include "main.h"

typedef struct {
	GPIO_TypeDef* sensor_gpio_port;
	uint16_t sensor_signal_pin;
} FloatSensor_HandleTypeDef;

HAL_StatusTypeDef float_sensor_init(FloatSensor_HandleTypeDef* sensor, GPIO_TypeDef* sensor_gpio_port, uint16_t sensor_signal_pin);
GPIO_PinState float_sensor_status(FloatSensor_HandleTypeDef* sensor);


#endif /* INC_FLOAT_SENSOR_H_ */
