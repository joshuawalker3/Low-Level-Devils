#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "led_ctrl.h"

void led_strip_init(int pin1, int pin2, int pin3) {
	//reset pin buffers
	ESP_ERROR_CHECK(gpio_reset_pin(pin1));
	ESP_ERROR_CHECK(gpio_reset_pin(pin2));
	ESP_ERROR_CHECK(gpio_reset_pin(pin3));

	//Start Pins
	ESP_ERROR_CHECK(gpio_set_direction(pin1, GPIO_MODE_OUTPUT));
	ESP_ERROR_CHECK(gpio_set_direction(pin2, GPIO_MODE_OUTPUT));
	ESP_ERROR_CHECK(gpio_set_direction(pin3, GPIO_MODE_OUTPUT));
}

void cycle_single(int pin, int delayTime) {
	gpio_set_level(pin, ON);
	delay(delayTime);
	gpio_set_level(pin, OFF);
}

void cycle_double(int pin1, int pin2, int delayTime) {
	gpio_set_level(pin1, ON);
	gpio_set_level(pin2, ON);
	delay(delayTime);
	gpio_set_level(pin1, OFF);
	gpio_set_level(pin2, OFF);
}

void cycle_triple(int pin1, int pin2, int pin3, int delayTime) {
	gpio_set_level(pin1, ON);
	gpio_set_level(pin2, ON);
	gpio_set_level(pin3, ON);
	delay(delayTime);
	gpio_set_level(pin1, OFF);
	gpio_set_level(pin2, OFF);
	gpio_set_level(pin3, OFF);
}