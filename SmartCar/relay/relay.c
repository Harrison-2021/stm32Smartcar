#include "relay.h"

void open_relay() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);  
}

void close_relay() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

}

void relay_test() {
    while (1) {
        open_relay();
        HAL_Delay(1000);
        close_relay();
        HAL_Delay(1000);
    }
    
}