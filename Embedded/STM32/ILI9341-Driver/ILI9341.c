/*
 * ILI9341.c
 *
 *  Created on: Mar 22, 2025
 *      Author: walke
 */

#include "ILI9341.h"
#include "font.h"

HAL_StatusTypeDef ili9341_init(Ili9341_HandleTypeDef* ili9341) {
	HAL_StatusTypeDef status;

    ili9341_select(ili9341);

    ili9341_reset(ili9341);

    //ili9341_unselect(ili9341);

    // command list is based on https://github.com/martnak/STM32-ILI9341

    // SOFTWARE RESET
    status = ili9341_write_cmd(ili9341, SOFTWARE_RESET);
    if (status != HAL_OK) {
    	return status;
    }

    _DELAY(ili9341->mode, 1000);

    // POWER CONTROL,VRH[5:0]
    status = ili9341_write_cmd(ili9341, PWR_CTL_1);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x23 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // POWER CONTROL,SAP[2:0];BT[3:0]
    status = ili9341_write_cmd(ili9341, PWR_CTL_2);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x10 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // VCM CONTROL
    status = ili9341_write_cmd(ili9341, VCOM_CTL_1);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x3E, 0x28 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // VCM CONTROL 2
    status = ili9341_write_cmd(ili9341, VCOM_CTL_2);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x86 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // MEMORY ACCESS CONTROL
    status = ili9341_write_cmd(ili9341, MEM_ACC_CTL);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x48 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // PIXEL FORMAT
    status = ili9341_write_cmd(ili9341, PIXEL_FMT_SET);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x55 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // FRAME RATIO CONTROL, STANDARD RGB COLOR
    status = ili9341_write_cmd(ili9341, FRAME_CTL);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x00, 0x18 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // DISPLAY FUNCTION CONTROL
    status = ili9341_write_cmd(ili9341, DISP_FUNC_CTL);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x08, 0x82, 0x27 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // GAMMA CURVE SELECTED
    status = ili9341_write_cmd(ili9341, GAMMA_SET);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x01 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // POSITIVE GAMMA CORRECTION
    status = ili9341_write_cmd(ili9341, POS_GAMMA_CORR);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1,
                           0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // NEGATIVE GAMMA CORRECTION
    status = ili9341_write_cmd(ili9341, NEG_GAMMA_CORR);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1,
                           0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    // EXIT SLEEP
    status = ili9341_write_cmd(ili9341, EXIT_SLEEP);
    if (status != HAL_OK) {
    	return status;
    }

    _DELAY(ili9341->mode, 120);

    // MADCTL
    status = ili9341_write_cmd(ili9341, MEM_ACC_CTL);
    if (status != HAL_OK) {
    	return status;
    }

    {
        uint8_t data[] = { ILI9341_ROTATION };
        status = ili9341_write_data(ili9341, data, sizeof(data));
        if (status != HAL_OK) {
        	return status;
        }
    }

    ili9341_unselect(ili9341);

    return status;
}

void ili9341_reset(Ili9341_HandleTypeDef* ili9341) {
	HAL_GPIO_WritePin(ili9341->screen_reset_gpio_port, ili9341->screen_reset_pin, GPIO_PIN_RESET);

	_DELAY(ili9341->mode, 200);

	HAL_GPIO_WritePin(ili9341->screen_reset_gpio_port, ili9341->screen_reset_pin, GPIO_PIN_SET);
}

void ili9341_select(Ili9341_HandleTypeDef* ili9341) {
	HAL_GPIO_WritePin(ili9341->cs_gpio_port, ili9341->cs_pin, GPIO_PIN_RESET);
}

void ili9341_unselect(Ili9341_HandleTypeDef* ili9341) {
	HAL_GPIO_WritePin(ili9341->cs_gpio_port, ili9341->cs_pin, GPIO_PIN_SET);
}

HAL_StatusTypeDef ili9341_write_cmd(Ili9341_HandleTypeDef* ili9341, uint8_t cmd) {
	HAL_GPIO_WritePin(ili9341->dc_gpio_port, ili9341->dc_pin, GPIO_PIN_RESET);

	HAL_StatusTypeDef status = HAL_SPI_Transmit(ili9341->hspi, &cmd, sizeof(cmd), ILI9341_MAX_DELAY);
	if (status != HAL_OK) {
		return status;
	}

	return status;
}

HAL_StatusTypeDef ili9341_write_data(Ili9341_HandleTypeDef* ili9341, uint8_t* data, size_t data_size) {
	HAL_GPIO_WritePin(ili9341->dc_gpio_port, ili9341->dc_pin, GPIO_PIN_SET);

	HAL_StatusTypeDef status;

    // split data in small chunks
    while(data_size > 0) {
        uint16_t chunk_size;

        if (data_size > ILI9341_MAX_BUFF_SIZE) {
        	chunk_size = 32768;
        } else {
        	chunk_size = data_size;
        }

        status = HAL_SPI_Transmit(ili9341->hspi, data, chunk_size, ILI9341_MAX_DELAY);
    	if (status != HAL_OK) {
    		return status;
    	}

        data += chunk_size;
        data_size -= chunk_size;
    }

	return status;
}

HAL_StatusTypeDef ili9341_set_address_window(Ili9341_HandleTypeDef* ili9341, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    // column address set
    HAL_StatusTypeDef status = ili9341_write_cmd(ili9341, COL_ADDR_SET); // CASET
	if (status != HAL_OK) {
		return status;
	}

    {
        uint8_t data[] = { (x0 >> 8) & 0xFF, x0 & 0xFF, (x1 >> 8) & 0xFF, x1 & 0xFF };
        status = ili9341_write_data(ili9341, data, sizeof(data));
    	if (status != HAL_OK) {
    		return status;
    	}
    }

    // row address set
    status = ili9341_write_cmd(ili9341, PAGE_ADDR_SET); // RASET
	if (status != HAL_OK) {
		return status;
	}

    {
        uint8_t data[] = { (y0 >> 8) & 0xFF, y0 & 0xFF, (y1 >> 8) & 0xFF, y1 & 0xFF };
        status = ili9341_write_data(ili9341, data, sizeof(data));
    	if (status != HAL_OK) {
    		return status;
    	}
    }

    // write to RAM
    status = ili9341_write_cmd(ili9341, MEM_WRITE); // RAMWR
	if (status != HAL_OK) {
		return status;
	}

	//ili9341_unselect(ili9341);

    return status;
}

HAL_StatusTypeDef ili9341_draw_pixel(Ili9341_HandleTypeDef* ili9341, uint16_t x, uint16_t y, uint16_t color) {
    if((x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT)) {
    	return HAL_ERROR;
    }

    ili9341_select(ili9341);

	HAL_StatusTypeDef status = ili9341_set_address_window(ili9341, x, y, x+1, y+1);
	if (status != HAL_OK) {
		return status;
	}

    uint8_t data[] = { color >> 8, color & 0xFF };

    status = ili9341_write_data(ili9341, data, sizeof(data));

    ili9341_unselect(ili9341);

    return status;
}

HAL_StatusTypeDef ili9341_draw_area(Ili9341_HandleTypeDef* ili9341, Ili9341_AreaTypeDef* area) {
	ili9341_select(ili9341);

	HAL_StatusTypeDef status = ili9341_set_address_window(ili9341, area->x_pos, area->y_pos, area->x_pos + area->width - 1, area->y_pos + area->height - 1);
	if (status != HAL_OK) {
		return status;
	}

    for (uint32_t y = 0; y < area->height * area->width; y++) {
    	uint8_t data[] = { area->buffer[y] >> 8, area->buffer[y] & 0xFF };

        status = ili9341_write_data(ili9341, data, sizeof(data));
    	if (status != HAL_OK) {
    		return status;
    	}
    }

    ili9341_unselect(ili9341);

    return HAL_OK;
}

HAL_StatusTypeDef ili9341_screen_control(Ili9341_HandleTypeDef* ili9341, Screen_Status screen_status) {
	ili9341_select(ili9341);

	HAL_StatusTypeDef status;

	switch (screen_status) {
		case SCREEN_ON:
			status = ili9341_write_cmd(ili9341, SCREEN_ON);
			break;
		case SCREEN_OFF:
			status = ili9341_write_cmd(ili9341, SCREEN_OFF);
			break;
		default:
			return HAL_ERROR;
	}

	ili9341_unselect(ili9341);

	return status;
}

HAL_StatusTypeDef ili9341_draw_character(Ili9341_HandleTypeDef* ili9341, Ili9341_CharacterTypeDef* character, uint16_t scale) {
	if (scale <= 0) {
		return HAL_ERROR;
	}

	if (character->area->width != scale * STD_FONT_WIDTH) {
		character->area->width = scale * STD_FONT_WIDTH;
	}

	if (character->area->height != scale * STD_FONT_HEIGHT) {
		character->area->height = scale * STD_FONT_HEIGHT;
	}

	uint16_t scaled_array[(character->area->width) * (character->area->height)];

	if (scale == 1) {
		for (uint8_t x = 0; x < STD_FONT_HEIGHT * STD_FONT_WIDTH; x++) {
			if (character->pixels[x]) {
				scaled_array[x] = character->pri_color;
			} else {
				scaled_array[x] = character->bkgd_color;
			}
		}

		character->area->buffer = scaled_array;

		return ili9341_draw_area(ili9341, character->area);
	}

	for (uint16_t y = 0; y < STD_FONT_HEIGHT; y++) {
		for (uint16_t x = 0; x < STD_FONT_WIDTH; x++) {
			for (uint16_t cnt = 0; cnt < scale; cnt++) {
				if (character->pixels[(y * STD_FONT_WIDTH) + x]) {
					scaled_array[(y * scale * (STD_FONT_WIDTH * scale)) + (x * scale) + cnt] = character->pri_color;
					for (uint16_t cnt2 = 1; cnt2 < scale; cnt2++) {
						scaled_array[(y * scale * (STD_FONT_WIDTH * scale)) + (x * scale) + cnt + STD_FONT_WIDTH * scale * cnt2] = character->pri_color;
					}
				} else {
					scaled_array[(y * scale * (STD_FONT_WIDTH * scale)) + (x * scale) + cnt] = character->bkgd_color;
					for (uint16_t cnt2 = 1; cnt2 < scale; cnt2++) {
						scaled_array[(y * scale * (STD_FONT_WIDTH * scale)) + (x * scale) + cnt + STD_FONT_WIDTH * scale * cnt2] = character->bkgd_color;
					}
				}
			}
		}
	}

	character->area->buffer = scaled_array;

	return ili9341_draw_area(ili9341, character->area);
}

