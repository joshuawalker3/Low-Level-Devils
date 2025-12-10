/*
 * solenoid.c
 *
 *  Created on: Apr 25, 2025
 *      Author: walke
 */

#include "solenoid.h"


HAL_StatusTypeDef solenoid_init(Solenoid_HandleTypeDef* sol, GPIO_TypeDef* sol_gpio_port, uint16_t sol_signal_pin, Solenoid_Status status) {
	if (!sol_gpio_port) {
		return HAL_ERROR;
	}

	sol->sol_gpio_port = sol_gpio_port;
	sol->sol_signal_pin = sol_signal_pin;
	sol->status = status;

	switch (sol->status) {
		case SOL_OFF:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_RESET);
			break;
		case SOL_ON:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_RESET); //fail safe
			sol->status = SOL_OFF;
			break;
	}

	return HAL_OK;
}

void solenoid_control(Solenoid_HandleTypeDef* sol, Solenoid_Status status) {
	if (sol->status == status) {
		return;
	}

	sol->status = status;

	switch (sol->status) {
		case SOL_OFF:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_RESET);
			break;
		case SOL_ON:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(sol->sol_gpio_port, sol->sol_signal_pin, GPIO_PIN_RESET); //fail safe
			sol->status = SOL_OFF;
			break;
	}
}

