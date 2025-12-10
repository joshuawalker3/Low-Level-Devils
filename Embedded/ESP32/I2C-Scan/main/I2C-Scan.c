#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define STACK_SIZE 3000
#define delay(x) vTaskDelay(x / portTICK_PERIOD_MS)
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_SCL_IO 22
#define MAX_TIMEOUT 30

void scan(void* args);
void initialize(i2c_master_bus_handle_t* mst_handle);

i2c_master_bus_handle_t mst_handle = NULL;

void app_main(void) {
	initialize(&mst_handle);

	xTaskCreate(scan, "Scan", STACK_SIZE, NULL, 2, NULL);
}

void scan(void* args) {
	static const char* TAG = "Scanner-Info";

	while(1) {
		int devices_found = 0;

		ESP_LOGI(TAG, "Beginning scan...");

		for (int i = 0x08; i < 0x78; i++) {
			//ESP_ERROR_CHECK(i2c_master_probe(mst_handle, i, MAX_TIMEOUT));

			if (i2c_master_probe(mst_handle, i, MAX_TIMEOUT) == ESP_OK) {
				ESP_LOGI(TAG, "Found address 0x%02X!", i);
				devices_found++;
			}
		}

		if (!devices_found) {
			ESP_LOGI(TAG, "Found no addresses :(");
		}

		delay(5000);
	}
}

void initialize(i2c_master_bus_handle_t* mst_handle) {
	i2c_master_bus_config_t mst_config = {
		.i2c_port = I2C_NUM_0,
		.sda_io_num = I2C_MASTER_SDA_IO,
		.scl_io_num = I2C_MASTER_SCL_IO,
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.glitch_ignore_cnt = 7,
		.intr_priority = 0,
		.flags.enable_internal_pullup = true, 
	};

	ESP_ERROR_CHECK(i2c_new_master_bus(&mst_config, mst_handle));
}