#include "driver/ledc.h"

#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

void initialize_timer(
	ledc_mode_t speed_mode,
	ledc_timer_bit_t duty_resolution,
	ledc_timer_t timer_num,
	uint32_t freq_hz,
	ledc_clk_cfg_t clk_cfg);

void initialize_channel(
	int gpio_num,
	ledc_mode_t speed_mode,
	ledc_channel_t channel,
	ledc_intr_type_t intr_type,
	ledc_timer_t timer_num,
	uint32_t duty,
	int hpoint);

void update_and_change_motor_speed(
	ledc_mode_t speed_mode,
	ledc_channel_t channel,
	uint32_t duty);

#endif