#ifndef _TM_H
#define _TM_H

#include "gpio.h"
#include <stdio.h>
#include "my_uart.h"
#include "rtc.h"

#define TM1637_CLK_H HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)
#define TM1637_CLK_L HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)
#define TM1637_DAT_H HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)
#define TM1637_DAT_L HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)

#define TM1637_DELAY_TIME 1 // 高低电平持续时间ms
#define TM1637_CMD 0x44
#define TM1637_ADDR1 0xc0
#define TM1637_ADDR2 0xc1
#define TM1637_ADDR3 0xc2
#define TM1637_ADDR4 0xc3
#define TM1637_DSPLAY 0x8a

extern void tm1637_start();
extern void tm1637_stop();
extern void tm1637_ack();
extern void tm1637_write_byte(uint8_t data);
extern void tm1637_write_cmd(uint8_t cmd);
extern void tm1637_write_data(uint8_t addr, uint8_t data);
extern void tm1637_display_time(uint8_t hour, uint8_t minute);
extern void tm1637_test();

#endif