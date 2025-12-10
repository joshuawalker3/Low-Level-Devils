#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_ctrl.h"

/*
Pins
*/
#define RED 2
#define GREEN 4
#define BLUE 5

/*
Stack Size
*/
#define STACK_SIZE 2048

/*
Prototypes
*/
void HW_Init();
void test_cycle(void* args);

int delayTime = 1000;

void app_main(void) {
	HW_Init();

	xTaskCreate(test_cycle, "Testing", STACK_SIZE, NULL, 2, NULL);
}

void HW_Init() {
	led_strip_init(RED, GREEN, BLUE);
}

/*
Test individual colors first then test all
combinations
*/
void test_cycle(void* args) {
	char* ourTaskName = pcTaskGetName(NULL);

	while(1) {
		ESP_LOGI(ourTaskName, "RED");
		cycle_single(RED, delayTime);
	
	
		ESP_LOGI(ourTaskName, "GREEN");
		cycle_single(GREEN, delayTime);
	
		ESP_LOGI(ourTaskName, "BLUE");
		cycle_single(BLUE, delayTime);
	
		ESP_LOGI(ourTaskName, "RED/GREEN");
		cycle_double(RED, GREEN, delayTime);

		ESP_LOGI(ourTaskName, "RED/BLUE");
		cycle_double(RED, BLUE, delayTime);

		ESP_LOGI(ourTaskName, "GREEN/BLUE");
		cycle_double(BLUE, GREEN, delayTime);

		ESP_LOGI(ourTaskName, "RED/GREEN/BLUE");
		cycle_triple(RED, GREEN, BLUE, delayTime);
	}
}
