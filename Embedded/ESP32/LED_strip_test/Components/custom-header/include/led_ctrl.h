#ifndef LED_CTRL_H
#define LED_CTRL_H

/*
Delay Macro
*/
#define delay(time) vTaskDelay(time / portTICK_PERIOD_MS) //delays for time ms

/*
Pin CTRL
*/
#define ON 1
#define OFF 0

void led_strip_init(int pin1, int pin2, int pin3);
void cycle_single(int pin, int delayTime);
void cycle_double(int pin1, int pin2, int delayTime);
void cycle_triple(int pin1, int pin2, int pin3, int delayTime);

#endif