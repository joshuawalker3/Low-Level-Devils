#include "esp_err.h"
#include "driver/ledc.h"
#include "motor_ctrl.h"

void initialize_timer(
	ledc_mode_t speed_mode,
	ledc_timer_bit_t duty_resolution,
	ledc_timer_t timer_num,
	uint32_t freq_hz, 
	ledc_clk_cfg_t clk_cfg) {

	ledc_timer_config_t ledc_timer = {
		.speed_mode = speed_mode, //set mode
		.duty_resolution = duty_resolution, //set resolution
		.timer_num = timer_num, //set timer
		.freq_hz = freq_hz, //set freq
		.clk_cfg = clk_cfg //set clock ticks
	};

	ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
}

void initialize_channel(
	int gpio_num,
	ledc_mode_t speed_mode,
	ledc_channel_t channel,
	ledc_intr_type_t intr_type,
	ledc_timer_t timer_num,
	uint32_t duty,
	int hpoint) {

	ledc_channel_config_t ledc_channel = {
		.speed_mode = speed_mode, //set speed
		.channel = channel, //set channel
		.timer_sel = timer_num, //set timer
		.intr_type = intr_type, //set interrupt type
		.gpio_num = gpio_num, //set pin
		.duty = duty, //set initial duty %
		.hpoint = hpoint //set phase shift
	};

	ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void update_and_change_motor_speed(
	ledc_mode_t speed_mode,
	ledc_channel_t channel,
	uint32_t duty) {

	ESP_ERROR_CHECK(ledc_set_duty(speed_mode, channel, duty)); //Update duty to zero for channel
	ESP_ERROR_CHECK(ledc_update_duty(speed_mode, channel)); //Applies changes to the channel
}
