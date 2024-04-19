#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "string.h"
#include "stdio.h"
#include "motor.h"
#include "tim.h"
#include "my_uart.h"


extern void bluetooth_car_control(uint8_t *buffer,uint32_t size);
extern void bluetooth_test();
#endif