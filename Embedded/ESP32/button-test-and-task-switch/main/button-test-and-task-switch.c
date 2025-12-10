#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define BLUE 2
#define RED 4
#define GREEN 5
#define BLUE_BUTTON 25
#define RED_BUTTON 26
#define GREEN_BUTTON 27
#define STACK_SIZE 1024

/**
 * 	function prototypes
 */
void Flash_Blue(void* argument);
void Flash_Red(void* argument);
void Flash_Green(void* argument);
void Button_Handle(void* argument);
int HW_Init();

TaskHandle_t BlueHandle = NULL;
TaskHandle_t RedHandle = NULL;
TaskHandle_t GreenHandle = NULL;

void app_main(void)
{
	char* ourTaskName = pcTaskGetName(NULL);

	if (HW_Init()) {
		ESP_LOGI(ourTaskName, "Failied Initialization\nExiting");
		return;
	}

	xTaskCreate(Button_Handle, "Handle Buttons", 2 * STACK_SIZE, NULL, 3, NULL);
}

int HW_Init() {
	if (gpio_reset_pin(RED) != ESP_OK) {
		return 1;
	}
	if (gpio_reset_pin(GREEN) != ESP_OK) {
		return 1;
	}
	if (gpio_reset_pin(BLUE) != ESP_OK) {
		return 1;
	}

	if (gpio_set_direction(RED, GPIO_MODE_OUTPUT) != ESP_OK) {
		return 1;
	}
	if (gpio_set_direction(GREEN, GPIO_MODE_OUTPUT) != ESP_OK) {
		return 1;
	}
	if (gpio_set_direction(BLUE, GPIO_MODE_OUTPUT) != ESP_OK) {
		return 1;
	}

	if (gpio_set_direction(RED_BUTTON, GPIO_MODE_INPUT) != ESP_OK) {
		return 1;
	}
	if (gpio_set_direction(GREEN_BUTTON, GPIO_MODE_INPUT) != ESP_OK) {
		return 1;
	}
	if (gpio_set_direction(BLUE_BUTTON, GPIO_MODE_INPUT) != ESP_OK) {
		return 1;
	}

	return 0;
}

void Button_Handle(void* argument) {
	char* ourTaskName = pcTaskGetName(NULL);

	while (1) {
		if (gpio_get_level(BLUE_BUTTON)) {
			ESP_LOGI(ourTaskName, "Blue pressed");
	
			if (RedHandle != NULL) {
				vTaskDelete(RedHandle);
				gpio_set_level(RED, 0);
				RedHandle = NULL;
			}
			if (GreenHandle != NULL) {
				vTaskDelete(GreenHandle);
				gpio_set_level(GREEN, 0);
				GreenHandle = NULL;
			}
			if (BlueHandle == NULL) {
				xTaskCreate(Flash_Blue, "BLUE", STACK_SIZE, NULL, 2, &BlueHandle);
			}
			
			while (gpio_get_level(BLUE_BUTTON)) {
				vTaskDelay(50 / portTICK_PERIOD_MS);
			}
		}

		if (gpio_get_level(RED_BUTTON)) {
			ESP_LOGI(ourTaskName, "Red pressed");
	
			if (BlueHandle != NULL) {
				vTaskDelete(BlueHandle);
				gpio_set_level(BLUE, 0);
				BlueHandle = NULL;
			}
			if (GreenHandle != NULL) {
				vTaskDelete(GreenHandle);
				gpio_set_level(GREEN, 0);
				GreenHandle = NULL;
			}
			if (RedHandle == NULL) {
				xTaskCreate(Flash_Red, "RED", STACK_SIZE, NULL, 2, &RedHandle);
			}
	
			while (gpio_get_level(RED_BUTTON)) {
				vTaskDelay(50 / portTICK_PERIOD_MS);
			}
		}

		if (gpio_get_level(GREEN_BUTTON)) {
			ESP_LOGI(ourTaskName, "Green pressed");
			if (BlueHandle != NULL) {
				vTaskDelete(BlueHandle);
				gpio_set_level(BLUE, 0);
				BlueHandle = NULL;
			}
			if (RedHandle != NULL) {
				vTaskDelete(RedHandle);
				gpio_set_level(RED, 0);
				RedHandle = NULL;
			}
			if (GreenHandle == NULL) {
				xTaskCreate(Flash_Green, "GREEN", STACK_SIZE, NULL, 2, &GreenHandle);
			}
	
			while (gpio_get_level(GREEN_BUTTON)) {
				vTaskDelay(50 / portTICK_PERIOD_MS);
			}
		}

		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void Flash_Blue(void *argument)
{
  while(1) {
	gpio_set_level(BLUE, 1);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	gpio_set_level(BLUE, 0);
	vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Flash_Red( void* argument )
{
	while(1)
	{
		gpio_set_level(RED, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		gpio_set_level(RED, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Flash_Green( void* argument )
{
	while(1)
	{
		gpio_set_level(GREEN, 1);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		gpio_set_level(GREEN, 0);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}