#ifndef _SHT31_H
#define _SHT31_H

#include "i2c.h"
#include <stdio.h>

#define SHT31_DEBUG

#define SHT31_ADDR 0x44
#define SHT31_ADDR_WRITE (SHT31_ADDR << 1 | 0)
#define SHT31_ADDR_READ  (SHT31_ADDR << 1 | 1)
#define SHT31_SOFT_RESET  0x3042
#define SHT31_MEASUREMENT 0x2130
#define SHT31_FETCH_DATA  0xe000

extern void sht31_send_cmd(uint16_t cmd) ;
extern void sht31_init();
extern void sht31_sample_temp_humi(float *ptemp, float *phumi);
extern void sht31_test();

#endif