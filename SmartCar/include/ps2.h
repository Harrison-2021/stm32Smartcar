#ifndef _PS2_H
#define _PS2_H

#include "spi.h"
#include <stdio.h>
#include "motor.h"

// #define PS2_DEBUG
#define PS2_DEBUG1
#define PS2_EMPTY_KEY1 0xffff
#define PS2_EMPTY_KEY2 0x0000
#define PS2_EMPTY_KEY      -1

typedef enum{
          PS2_SELECT = 0,
          PS2_L_3,
          PS2_R_3,
          PS2_START,
          PS2_L_UP,
          PS2_L_RIGHT,
          PS2_L_DOWN,
          PS2_L_LEFT,
          PS2_L_2,
          PS2_R_2,
          PS2_L_1,
          PS2_R_1,
          PS2_R_UP,
          PS2_R_RIGHT,
          PS2_R_DOWN,
          PS2_R_LEFT
}ps2_key_t;

extern uint16_t read_ps2_data();
extern void ps2_test();
extern int8_t read_ps2_press_key();
extern void ps2_control_car();

#endif