/*
 * solenoid.h
 *
 *  Created on: Apr 25, 2025
 *      Author: walke
 */

#ifndef INC_SOLENOID_H_
#define INC_SOLENOID_H_

#include "main.h"

typedef enum {
	SOL_OFF,
	SOL_ON
} Solenoid_Status;

typedef struct {
	GPIO_TypeDef* sol_gpio_port;
	uint16_t sol_signal_pin;
	Solenoid_Status status;
} Solenoid_HandleTypeDef;


HAL_StatusTypeDef solenoid_init(Solenoid_HandleTypeDef* sol, GPIO_TypeDef* sol_gpio_port, uint16_t sol_signal_pin, Solenoid_Status status);
void solenoid_control(Solenoid_HandleTypeDef* sol, Solenoid_Status status);

#endif /* INC_SOLENOID_H_ */
