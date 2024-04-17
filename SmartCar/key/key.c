#include "gpio.h"
#include "led.h"

void key_scan() {
	GPIO_PinState level = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11);
	if(level == GPIO_PIN_SET) {
		led_off();
	} else {
		led_on();
	}
}
