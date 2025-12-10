#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor_ctrl.h"
#include "esp_log.h"

/*
Pins
*/
#define PWM_PIN 2

/*
stuff for pwm
*/
#define LEDC_TIMER LEDC_TIMER_0 //1 of 4 timers
#define LEDC_MODE LEDC_LOW_SPEED_MODE //Changes to speed done by function call
#define LEDC_CHANNEL LEDC_CHANNEL_0 //1 of 8 channels
#define LEDC_DUTY_RES LEDC_TIMER_3_BIT //Duty resolution of 3 bits (2^3 - 1 discrete values)
#define LEDC_FREQUENCY 4000 //4 kHz
#define LEDC_PHASE_SHIFT 0 //0 phase shift

/*
Power Levels
*/
#define ZERO_POWER 0
#define QTR_POWER 2
#define HALF_POWER 4
#define FULL_POWER 7

/*
Random
*/
#define STACK_SIZE 2048

/**
 * 	function prototypes
 */
void TestTask(void *argument);
void HW_Init();

void app_main(void) {
	HW_Init();

	xTaskCreate(TestTask, "Motor Run", STACK_SIZE, NULL, 3, NULL);
}

void HW_Init() {
	char* ourTaskName = pcTaskGetName(NULL);

	ESP_LOGI(ourTaskName, "Initializing...");

	ESP_LOGI(ourTaskName, "Initializing Timer...");

	initialize_timer(LEDC_MODE, LEDC_DUTY_RES, LEDC_TIMER, LEDC_FREQUENCY, LEDC_AUTO_CLK);

	ESP_LOGI(ourTaskName, "Initializing Channel...");

	initialize_channel(PWM_PIN, LEDC_MODE, LEDC_CHANNEL, LEDC_INTR_DISABLE, LEDC_TIMER, ZERO_POWER, LEDC_PHASE_SHIFT);
}
		

void TestTask(void *argument) {
	char* ourTaskName = pcTaskGetName(NULL);

	while(1) {
		update_and_change_motor_speed(LEDC_MODE, LEDC_CHANNEL, ZERO_POWER);
		ESP_LOGI(ourTaskName, "Fan power 0");
		vTaskDelay(5000 / portTICK_PERIOD_MS);

		update_and_change_motor_speed(LEDC_MODE, LEDC_CHANNEL, QTR_POWER);
		ESP_LOGI(ourTaskName, "Fan power 0.25");
		vTaskDelay(5000 / portTICK_PERIOD_MS);

		update_and_change_motor_speed(LEDC_MODE, LEDC_CHANNEL, HALF_POWER);
		ESP_LOGI(ourTaskName, "Fan power 0.5");
		vTaskDelay(5000 / portTICK_PERIOD_MS);

		update_and_change_motor_speed(LEDC_MODE, LEDC_CHANNEL, FULL_POWER);
		ESP_LOGI(ourTaskName, "Fan power 1");
		vTaskDelay(5000 / portTICK_PERIOD_MS);
  	}
}
