#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define BLUE 5
#define RED 2
#define GREEN 4

/**
 * 	function prototypes
 */
void Task1(void *argument);
void Task2(void *argument);
void Task3(void *argument);
void lookBusy( void );

void app_main(void)
{
	const static uint32_t stackSize = 1024;

	gpio_reset_pin(RED);
	gpio_reset_pin(GREEN);
	gpio_reset_pin(BLUE);

	gpio_set_direction(RED, GPIO_MODE_OUTPUT);
	gpio_set_direction(GREEN, GPIO_MODE_OUTPUT);
	gpio_set_direction(BLUE, GPIO_MODE_OUTPUT);

	char* ourTaskName = pcTaskGetName(NULL);

	//HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);	//ensure proper priority grouping for freeRTOS

	if (xTaskCreate(Task1, "task1", stackSize, NULL, 3, NULL) == pdPASS)
	{
		ESP_LOGI(ourTaskName, "RED\n");
		if (xTaskCreate(Task2, "task2", stackSize, NULL, 2, NULL) == pdPASS)
		{
			ESP_LOGI(ourTaskName, "GREEN\n");
			if (xTaskCreate(Task3, "task3", stackSize, NULL, 1, NULL) == pdPASS)
			{
				ESP_LOGI(ourTaskName, "BLUE\n");
				//start the scheduler - shouldn't return unless there's a problem
				//vTaskStartScheduler();
			}
		}
	}

	/*
	while(1)
	{
		ESP_LOGI(ourTaskName, "task fail\n");
	}
	*/
}

void Task1(void *argument)
{
  while(1) {
	gpio_set_level(RED, 1);
	vTaskDelay(100 / portTICK_PERIOD_MS);
	gpio_set_level(RED, 0);
	vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Task2( void* argument )
{
	while(1)
	{
		gpio_set_level(GREEN, 1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		gpio_set_level(GREEN, 0);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Task3( void* argument )
{
	while(1)
	{
		gpio_set_level(BLUE, 1);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
		gpio_set_level(BLUE, 0);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}