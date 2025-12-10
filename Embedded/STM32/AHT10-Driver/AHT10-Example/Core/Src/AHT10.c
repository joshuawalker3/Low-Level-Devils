/*
 * AHT10.c
 *
 *  Created on: Jan 17, 2025
 *      Author: Joshua Walker
 */

#include "aht10.h"
#include <stdlib.h>

const uint8_t MEASURE_PACKET[SEND_PACKET_SIZE] = {
		MEASURE_CMD,
		DATA0,
		DATA1
};

int16_t calc_temp(Aht10_HandleTypeDef* aht10) {
	uint32_t temp_raw = ((aht10->buffer[3] & 0x0F) << 16) |
						(aht10->buffer[4] << 8) |
						aht10->buffer[5];

	if (aht10->units == IMPERIAL) {
		return _CONVERT_TO_IMPERIAL(((temp_raw * 200) >> 20) - 50);
	}
	else {
		return ((temp_raw * 200) >> 20) - 50;
	}
}

uint8_t calc_humidity(Aht10_HandleTypeDef* aht10) {
	uint32_t humid_raw = (aht10->buffer[1] << 12) |
						(aht10->buffer[2] << 4) |
						((aht10->buffer[3] & 0xF0) >> 4);

	return (humid_raw * 100) >> 20;
}

HAL_StatusTypeDef aht10_open(Aht10_HandleTypeDef* aht10, I2C_HandleTypeDef* hi2c, Os_Mode mode){
	if (!hi2c) {
		return HAL_ERROR;
	}

	aht10->mode = mode;
	aht10->hi2c = hi2c;

	return HAL_OK;
}

HAL_StatusTypeDef aht10_init(Aht10_HandleTypeDef* aht10, GPIO_TypeDef* power_pin_port, uint16_t power_pin, Temp_Unit units) {
	if (!aht10) {
		return HAL_ERROR;
	}

	aht10->power_pin_port = power_pin_port;
	aht10->power_pin = power_pin;
	aht10->units = units;

	return HAL_OK;
}

HAL_StatusTypeDef aht10_read(Aht10_HandleTypeDef* aht10, int16_t* temp, uint8_t* humid) {
	if (!aht10) {
		return HAL_ERROR;
	}

	HAL_StatusTypeDef status;

	status = aht10_ioctrl(aht10, POWER_ON);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(aht10->mode, START_DELAY_TIME);

	status = HAL_I2C_Master_Transmit(aht10->hi2c, AHT_ADDR, MEASURE_PACKET, SEND_PACKET_SIZE, MAX_TIMEOUT);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(aht10->mode, MEASURE_DELAY_TIME);

	status = HAL_I2C_Master_Receive(aht10->hi2c, AHT_ADDR, aht10->buffer, RECEIVE_PACKET_SIZE, MAX_TIMEOUT);
	if (status != HAL_OK) {
		return status;
	}

	*temp = calc_temp(aht10);
	*humid = calc_humidity(aht10);

	status = aht10_ioctrl(aht10, POWER_OFF);
	return status;
}

HAL_StatusTypeDef aht10_ioctrl(Aht10_HandleTypeDef* aht10, Aht10_Cmd cmd) {
	if (!aht10) {
		return HAL_ERROR;
	}

	switch (cmd) {
		case POWER_OFF:
			HAL_GPIO_WritePin(aht10->power_pin_port, aht10->power_pin, RESET);
			break;
		case POWER_ON:
			HAL_GPIO_WritePin(aht10->power_pin_port, aht10->power_pin, SET);
			_DELAY(aht10->mode, START_DELAY_TIME);
			break;
		case TEMP_UNIT_METRIC:
			aht10->units = METRIC;
			break;
		case TEMP_UNIT_IMPERIAL:
			aht10->units = IMPERIAL;
			break;
		default:
			return HAL_ERROR;
			break;
	}

	return HAL_OK;
}
