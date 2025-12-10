#include "i2c-lcd.h"
#include <stdio.h>
#include <stdlib.h>

const char CUSTOM_CHAR_01 = 0x00;
const char CUSTOM_CHAR_02 = 0x01;
const char CUSTOM_CHAR_03 = 0x02;
const char CUSTOM_CHAR_04 = 0x03;
const char CUSTOM_CHAR_05 = 0x04;
const char CUSTOM_CHAR_06 = 0x05;
const char CUSTOM_CHAR_07 = 0x06;
const char CUSTOM_CHAR_08 = 0x07;

HAL_StatusTypeDef lcd_open(Lcd_HandleTypeDef* lcd, I2C_HandleTypeDef* hi2c, uint16_t addr, Os_Mode mode) {
	if (!hi2c) {
		return HAL_ERROR;
	}

	lcd->hi2c = hi2c;
	lcd->addr = addr<<1;
	lcd->mode = mode;

	return HAL_OK;
}

HAL_StatusTypeDef lcd_init(Lcd_HandleTypeDef* lcd) {
	if (!lcd) {
		return HAL_ERROR;
	}

	HAL_StatusTypeDef status;

	_DELAY(lcd->mode, 50);

	status = lcd_ioctrl(lcd, FUNCTION_SET|BIT_MODE_8);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 5);

	status = lcd_ioctrl(lcd, FUNCTION_SET|BIT_MODE_8);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 1);

	status = lcd_ioctrl(lcd, FUNCTION_SET|BIT_MODE_8);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 10);

	status = lcd_ioctrl(lcd, FUNCTION_SET|BIT_MODE_4);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 10);

	status = lcd_ioctrl(lcd, FUNCTION_SET|LINES_2|FONT_5x8);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 1);

	status = lcd_ioctrl(lcd, DISP_CTRL|DISP_OFF|CURS_OFF|CURS_SOLID);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 1);

	status = lcd_ioctrl(lcd, CLEAR_DISPLAY);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 2);

	status = lcd_ioctrl(lcd, ENTRY_MODE_SET|CURS_INCR|SCREEN_SHIFT_DIS);
	if (status != HAL_OK) {
		return status;
	}

	_DELAY(lcd->mode, 1);

	return lcd_ioctrl(lcd, DISP_CTRL|DISP_ON|CURS_ON|CURS_BLINK);
}

HAL_StatusTypeDef lcd_write_char(Lcd_HandleTypeDef* lcd, char* data) {
	char data_u, data_l;
	uint8_t data_t[PACKET_SIZE];
	data_u = (*data & BIT_COMP);
	data_l = (_GET_LOWER_NIBBLE(*data) & BIT_COMP);

	data_t[0] = data_u | LIGHT_HI | EN_HI | RW_LO | RS_HI;
	data_t[1] = data_u | LIGHT_HI | EN_LO | RW_LO | RS_HI;
	data_t[2] = data_l | LIGHT_HI | EN_HI | RW_LO | RS_HI;
	data_t[3] = data_l | LIGHT_HI | EN_LO | RW_LO | RS_HI;

	return HAL_I2C_Master_Transmit(lcd->hi2c, lcd->addr, data_t, PACKET_SIZE, MAX_TIMEOUT);
}

HAL_StatusTypeDef lcd_write_string(Lcd_HandleTypeDef* lcd, void* void_str) {
	char* str = (char*)void_str;

	HAL_StatusTypeDef status;

	while (*str) {
		status = lcd_write_char(lcd, str++);
		if (status != HAL_OK) {
			return status;
		}
	}

	return status;
}

HAL_StatusTypeDef lcd_write_integer(Lcd_HandleTypeDef* lcd, void* void_num) {
	int* num = (int*)void_num;

	uint8_t chars;
	char str[20];

	chars = sprintf(str, "%d", *num);
	if (chars == 0) {
		return HAL_ERROR;
	}

	return lcd_write_string(lcd, str);
}

HAL_StatusTypeDef lcd_write_float(Lcd_HandleTypeDef* lcd, void* void_num) {
	float* num = (float*)void_num;

	uint8_t chars;
	char str[20];

	chars = sprintf(str, "%f", *num);
	if (chars == 0) {
		return HAL_ERROR;
	}

	return lcd_write_string(lcd, str);
}

HAL_StatusTypeDef lcd_create_char(Lcd_HandleTypeDef* lcd, void* char_bytes) {
	char* array = (char*)char_bytes;

	HAL_StatusTypeDef status;

	status = lcd_ioctrl(lcd, CGRAM_SET | *array++);
	if (status != HAL_OK) {
		return status;
	}

	for (int i = 0; i < 8; i++) {
		status = lcd_write_char(lcd, array++);
		if (status != HAL_OK) {
			return status;
		}
	}

	lcd_ioctrl(lcd, CLEAR_DISPLAY);

	return status;
}

HAL_StatusTypeDef lcd_write(Lcd_HandleTypeDef* lcd, void* data, Write_Type type) {
	if (!lcd) {
			return HAL_ERROR;
	}

	HAL_StatusTypeDef status;

	switch(type) {
		case WRITE_STRING:
			status = lcd_write_string(lcd, data);
			break;
		case WRITE_INT:
			status = lcd_write_integer(lcd, data);
			break;
		case WRITE_FLOAT:
			status = lcd_write_float(lcd, data);
			break;
		case WRITE_CUSTOM:
			status = lcd_write_char(lcd, data);
			break;
		case CREATE_CHAR:
			status = lcd_create_char(lcd, data);
			break;
		default:
			return HAL_ERROR;
	}

	return status;
}

HAL_StatusTypeDef lcd_ioctrl(Lcd_HandleTypeDef* lcd, char cmd) {
	if (!lcd) {
		return HAL_ERROR;
	}

	char data_u, data_l;
	uint8_t data_t[PACKET_SIZE];
	data_u = (cmd & BIT_COMP);
	data_l = (_GET_LOWER_NIBBLE(cmd) & BIT_COMP);

	data_t[0] = data_u | LIGHT_HI | EN_HI | RW_LO | RS_LO;
	data_t[1] = data_u | LIGHT_HI | EN_LO | RW_LO | RS_LO;
	data_t[2] = data_l | LIGHT_HI | EN_HI | RW_LO | RS_LO;
	data_t[3] = data_l | LIGHT_HI | EN_LO | RW_LO | RS_LO;

	HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(lcd->hi2c, lcd->addr, data_t, PACKET_SIZE, MAX_TIMEOUT);

	_DELAY(lcd->mode, 1);

	return status;
}
