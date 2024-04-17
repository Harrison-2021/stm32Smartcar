#include "gpio.h"
#include "led.h"

void led_on_off() {
	while(1) {
		led_on();
		HAL_Delay(500);
		led_off();
		HAL_Delay(500);
	}
}

void led_on() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
}

void led_off() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
}
