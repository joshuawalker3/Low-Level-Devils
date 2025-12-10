/*
 * AHT10.h
 *
 *  Created on: Jan 17, 2025
 *      Author: Joshua Walker
 */

#ifndef INC_AHT10_H_
#define INC_AHT10_H_

#include "main.h"

#define AHT_ADDR 0x38<<1 //can't be changed apparently

#define START_DELAY_TIME 20
#define MEASURE_DELAY_TIME 100

#define MEASURE_CMD 0xAC
#define DATA0 0x33 //from data sheet sequence
#define DATA1 0x00 //from data sheet sequence

#define SEND_PACKET_SIZE 3
#define RECEIVE_PACKET_SIZE 6
#define MAX_TIMEOUT 100

#ifndef _DELAY
	#ifdef CMSIS_OS_H_
		#define _DELAY(os_mode, x) \
			if (os_mode == NO_RTOS) { \
				HAL_Delay(x); \
			} \
			else { \
				osDelay(x); \
			}
	#else
		#define _DELAY(os_mode, x) HAL_Delay(x)
	#endif
#endif

#define _CONVERT_TO_IMPERIAL(x) (9 * (x)) / 5 + 32

#ifndef OS_MODE_H
	#define OS_MODE_H

	typedef enum {
		NO_RTOS,
		RTOS_MODE
	} Os_Mode;
#endif

typedef enum {
	POWER_OFF,
	POWER_ON,
	TEMP_UNIT_METRIC,
	TEMP_UNIT_IMPERIAL
} Aht10_Cmd;

typedef enum {
	METRIC,
	IMPERIAL
} Temp_Unit;

typedef struct {
	I2C_HandleTypeDef* hi2c;
	GPIO_TypeDef* power_pin_port;
	uint16_t power_pin;
	Os_Mode mode;
	Temp_Unit units;
	uint8_t buffer[6];
} Aht10_HandleTypeDef;

HAL_StatusTypeDef aht10_open(Aht10_HandleTypeDef* aht10, I2C_HandleTypeDef* hi2c, Os_Mode mode);

HAL_StatusTypeDef aht10_init(Aht10_HandleTypeDef* aht10, GPIO_TypeDef* power_pin_port, uint16_t power_pin, Temp_Unit units);

HAL_StatusTypeDef aht10_read(Aht10_HandleTypeDef* aht10, int16_t* temp, uint8_t* humid);

HAL_StatusTypeDef aht10_ioctrl(Aht10_HandleTypeDef* aht10, Aht10_Cmd cmd);


#endif /* INC_AHT10_H_ */
