#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"


//Start checking busy flag

#define STACK_SIZE 5000
#define delay(x) vTaskDelay(x / portTICK_PERIOD_MS)
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_SCL_IO 22
#define MAX_TIMEOUT 30
#define LONG_DELAY 3
#define SHORT_DELAY 1
#define LCD_ADDR 0x27
//#define LCD_ADDR 0x3F
#define LCD_FREQ 100000
#define BIT_COMP 0xF0
#define EN_HI 0x0C
#define ALL_LO 0x08
#define RS_HI 0x09
#define CHAR_START 0x41

const uint8_t LCD_FUNC_SET_INIT = 0x30;
const uint8_t LCD_FUNC_SET_MID = 0x20;
const uint8_t LCD_FUNC_SET = 0x28;
const uint8_t LCD_DISPLAY_ON = 0x0F;
const uint8_t LCD_DEFAULT_ENTRY_MODE = 0x06;
const uint8_t LCD_CLEAR_DISPLAY = 0x01; 
const uint8_t LCD_RET_HOME = 0x02;
const uint8_t LCD_SHIFT_RIGHT = 0x01D;
const uint8_t LCD_SHIFT_LEFT = 0x18;
const uint8_t LCD_SET_DDRAM_ADDR = 0x80;
const uint8_t LCD_DDRAM_ADDR_00 = 0x02;
const uint8_t LCD_DDRAM_ADDR_01 = 0x0F;
const uint8_t LCD_DDRAM_ADDR_02 = 0x40;
const uint8_t LCD_DDRAM_ADDR_03 = 0x46;
const uint8_t LCD_DDRAM_ADDR_04 = 0x4F;
const uint8_t LCD_READ_CMD = 0xF2;

uint8_t MEM_ADDRESS[16][16];
const uint8_t TOP_ADDR_START = 0x00;
const uint8_t BOTT_ADDR_START = 0x40;

void initialize_i2c(i2c_master_bus_handle_t* mst_handle, i2c_master_dev_handle_t* lcd_handle);
void initialize_lcd(i2c_master_dev_handle_t lcd_handle);
void send_cmd(uint8_t cmd, i2c_master_dev_handle_t lcd_handle);
void send_data(uint8_t data, i2c_master_dev_handle_t lcd_handle);
void init_mem_addr(uint8_t addr[16][16]);
void test_func(void* args);
void test_func_1(void* args);
void test_func_2(void* args);

void app_main(void) {
	i2c_master_bus_handle_t mst_handle = NULL;
	i2c_master_dev_handle_t lcd_handle = NULL;

	initialize_i2c(&mst_handle, &lcd_handle);

	initialize_lcd(lcd_handle);

	xTaskCreate(test_func_2, "Test", STACK_SIZE, (void*)&lcd_handle, 2, NULL);
}

void initialize_i2c(i2c_master_bus_handle_t* mst_handle, i2c_master_dev_handle_t* lcd_handle) {
	i2c_master_bus_config_t mst_config = {
		.i2c_port = I2C_NUM_0,
		.sda_io_num = I2C_MASTER_SDA_IO,
		.scl_io_num = I2C_MASTER_SCL_IO,
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.glitch_ignore_cnt = 7,
		.intr_priority = 0,
		.flags.enable_internal_pullup = false, 
	};

	ESP_ERROR_CHECK(i2c_new_master_bus(&mst_config, mst_handle));

	i2c_device_config_t lcd_config = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = LCD_ADDR,
		.scl_speed_hz = LCD_FREQ,
		.scl_wait_us = 0,
	};

	ESP_ERROR_CHECK(i2c_master_bus_add_device(*mst_handle, &lcd_config, lcd_handle));
}

void initialize_lcd(i2c_master_dev_handle_t lcd_handle) {
	static const char* TAG = "INIT";

	ESP_LOGI(TAG, "Starting LCD Init...");

	send_cmd(LCD_FUNC_SET_INIT, lcd_handle);

	ESP_LOGI(TAG, "Function set 1 complete!");

	delay(SHORT_DELAY);

	send_cmd(LCD_FUNC_SET_MID, lcd_handle);

	ESP_LOGI(TAG, "Function set 2 complete!");

	delay(SHORT_DELAY);

	send_cmd(LCD_FUNC_SET, lcd_handle);

	delay(SHORT_DELAY);

	ESP_LOGI(TAG, "Function set 3 complete!");

	send_cmd(LCD_DISPLAY_ON, lcd_handle);

	delay(SHORT_DELAY);

	ESP_LOGI(TAG, "Turned on display!");

	send_cmd(LCD_CLEAR_DISPLAY, lcd_handle);

	delay(LONG_DELAY);

	ESP_LOGI(TAG, "Cleared display!");

	send_cmd(LCD_DEFAULT_ENTRY_MODE, lcd_handle);

	delay(SHORT_DELAY);

	ESP_LOGI(TAG, "Default entry mode started!");

	send_cmd(LCD_RET_HOME, lcd_handle);

	delay(LONG_DELAY);

	init_mem_addr(MEM_ADDRESS);

	ESP_LOGI(TAG, "Init complete...");
}

void test_func(void* args) {
	i2c_master_dev_handle_t lcd_handle = *(i2c_master_dev_handle_t*)args;
	static const char* TAG = "test_func";

	uint8_t character = CHAR_START;

	while(1) {
		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd((LCD_SET_DDRAM_ADDR|LCD_DDRAM_ADDR_00), lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Moved one space");

		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd((LCD_SET_DDRAM_ADDR|LCD_DDRAM_ADDR_01), lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Moved to end");

		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd((LCD_SET_DDRAM_ADDR|LCD_DDRAM_ADDR_02), lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Next Line!");

		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd((LCD_SET_DDRAM_ADDR|LCD_DDRAM_ADDR_03), lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Moved one space");

		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd((LCD_SET_DDRAM_ADDR|LCD_DDRAM_ADDR_04), lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Moved to end");

		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);

		send_cmd(LCD_RET_HOME, lcd_handle);

		delay(10);

		ESP_LOGI(TAG, "Return Home");
	}
}

void test_func_1(void* args) {
	i2c_master_dev_handle_t lcd_handle = *(i2c_master_dev_handle_t*)args;

	uint8_t character = CHAR_START;

	while(1) {
		send_data(character, lcd_handle);

		if (character == 0xFF) {
			character = CHAR_START;
		}
		else {
			character++;
		}

		delay(500);
	}
}

void test_func_2(void* args) {
	i2c_master_dev_handle_t lcd_handle = *(i2c_master_dev_handle_t*)args;
	static const char* TAG = "test_func";

	while(1) {
		uint8_t character = CHAR_START;

		send_data(character, lcd_handle);

		for (int i = 1; i < 80; i++) {
			if (character == 0xFF) {
				character = CHAR_START;
			}	
			else {
				character++;
			}

			send_data(character, lcd_handle);

			delay(SHORT_DELAY);

			ESP_LOGI(TAG, "Wrote to 0x%02X", i);
		}

		send_cmd(LCD_RET_HOME, lcd_handle);

		ESP_LOGI(TAG, "Returned Home");

		delay(1000);

		for (int i = 0; i < 16; i++) {
			send_cmd(LCD_SHIFT_LEFT, lcd_handle);
			delay(SHORT_DELAY);
		}

		ESP_LOGI(TAG, "Shift left");

		delay(3000);

		for (int i = 0; i < 16; i++) {
			send_cmd(LCD_SHIFT_LEFT, lcd_handle);
			delay(SHORT_DELAY);
		}

		ESP_LOGI(TAG, "Shift left");

		delay(3000);

		for (int i = 0; i < 16; i++) {
			send_cmd(LCD_SHIFT_RIGHT, lcd_handle);
			delay(SHORT_DELAY);
		}

		ESP_LOGI(TAG, "Shift Right");

		delay(3000);

		for (int i = 0; i < 16; i++) {
			send_cmd(LCD_SHIFT_RIGHT, lcd_handle);
			delay(SHORT_DELAY);
		}

		ESP_LOGI(TAG, "Shift Right");

		delay(3000);

		send_cmd(LCD_CLEAR_DISPLAY, lcd_handle);

		delay(1000);
	}
}

void send_cmd(uint8_t cmd,  i2c_master_dev_handle_t lcd_handle) {
	uint8_t upper_data = (cmd&BIT_COMP);
	uint8_t lower_data = ((cmd<<4)&BIT_COMP);

	uint8_t data_byte[4];

	data_byte[0] = upper_data|EN_HI;
	data_byte[1] = upper_data|ALL_LO;
	data_byte[2] = lower_data|EN_HI;
	data_byte[3] = lower_data|ALL_LO; 

	ESP_ERROR_CHECK(i2c_master_transmit(lcd_handle, data_byte, 4, 100));
}

void send_data(uint8_t data, i2c_master_dev_handle_t lcd_handle) {
	uint8_t upper_data = (data&BIT_COMP);
	uint8_t lower_data = ((data<<4)&BIT_COMP);

	uint8_t data_byte[4];

	data_byte[0] = upper_data|(EN_HI|RS_HI);
	data_byte[1] = upper_data|(ALL_LO|RS_HI);
	data_byte[2] = lower_data|(EN_HI|RS_HI);
	data_byte[3] = lower_data|(ALL_LO|RS_HI); 

	ESP_ERROR_CHECK(i2c_master_transmit(lcd_handle, data_byte, 4, 100));
}

void init_mem_addr(uint8_t addr[16][16]) {
	for (uint8_t i = TOP_ADDR_START; i < 0x10; i++) {
		addr[0][i - TOP_ADDR_START] = i;
	}
	for (uint8_t i = BOTT_ADDR_START; i < 0x50; i++) {
		addr[0][i - BOTT_ADDR_START] = i;
	}
}