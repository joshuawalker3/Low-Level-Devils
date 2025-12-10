/*
 * ILI9341.h
 *
 *  Created on: Mar 22, 2025
 *      Author: walke
 */

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_

#include "main.h"

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

#ifndef OS_MODE_H
	#define OS_MODE_H

	typedef enum {
		NO_RTOS,
		RTOS_MODE
	} Os_Mode;
#endif

typedef enum {
	SCREEN_OFF,
	SCREEN_ON
} Screen_Status;

typedef struct {
	SPI_HandleTypeDef* hspi;
	uint16_t cs_pin;
	uint16_t dc_pin;
	uint16_t screen_reset_pin;
	GPIO_TypeDef* cs_gpio_port;
	GPIO_TypeDef* dc_gpio_port;
	GPIO_TypeDef* screen_reset_gpio_port;
	Os_Mode mode;
} Ili9341_HandleTypeDef;

typedef struct {
	uint16_t x_pos;
	uint16_t y_pos;
	uint16_t width;
	uint16_t height;
	uint16_t* buffer;
} Ili9341_AreaTypeDef;

typedef struct {
	Ili9341_AreaTypeDef* area;
	uint16_t pri_color;
	uint16_t bkgd_color;
	uint16_t* pixels;
} Ili9341_CharacterTypeDef;

#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320
#define ILI9341_ROTATION (ILI9341_MADCTL_MX | ILI9341_MADCTL_BGR)
#define ILI9341_MAX_DELAY 3000
#define ILI9341_MAX_BUFF_SIZE 32768

//Commands
#define SOFTWARE_RESET 0x01
#define PWR_CTL_1 0xC0
#define PWR_CTL_2 0xC1
#define VCOM_CTL_1 0xC5
#define VCOM_CTL_2 0xC7
#define MEM_ACC_CTL 0x36
#define PIXEL_FMT_SET 0x3A
#define FRAME_CTL 0xB1
#define DISP_FUNC_CTL 0xB6
#define GAMMA_SET 0x26
#define POS_GAMMA_CORR 0xE0
#define NEG_GAMMA_CORR 0xE1
#define EXIT_SLEEP 0x11
#define COL_ADDR_SET 0x2A
#define PAGE_ADDR_SET 0x2B
#define MEM_WRITE 0x2C
#define SCREEN_ON 0x29
#define SCREEN_OFF 0x28



HAL_StatusTypeDef ili9341_init(Ili9341_HandleTypeDef* ili9341);
void ili9341_reset(Ili9341_HandleTypeDef* ili9341);
void ili9341_select(Ili9341_HandleTypeDef* ili9341);
void ili9341_unselect(Ili9341_HandleTypeDef* ili9341);
HAL_StatusTypeDef ili9341_write_cmd(Ili9341_HandleTypeDef* ili9341, uint8_t cmd);
HAL_StatusTypeDef ili9341_write_data(Ili9341_HandleTypeDef* ili9341, uint8_t* data, size_t data_size);
HAL_StatusTypeDef ili9341_set_address_window(Ili9341_HandleTypeDef* ili9341, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
HAL_StatusTypeDef ili9341_draw_pixel(Ili9341_HandleTypeDef* ili9341, uint16_t x, uint16_t y, uint16_t color);
HAL_StatusTypeDef ili9341_draw_area(Ili9341_HandleTypeDef* ili9341, Ili9341_AreaTypeDef* area);
HAL_StatusTypeDef ili9341_screen_control(Ili9341_HandleTypeDef* ili9341, Screen_Status status);
HAL_StatusTypeDef ili9341_draw_character(Ili9341_HandleTypeDef* ili9341, Ili9341_CharacterTypeDef* character, uint16_t scale);


#endif /* INC_ILI9341_H_ */
