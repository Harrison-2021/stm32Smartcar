#ifndef _MOTOR_H
#define _MOTOR_H

#include "tim.h"

extern void right_motor_forward(uint32_t speed);
extern void motor_test();
extern void left_motor_forward(uint32_t speed);
extern void left_motor_reverse(uint32_t speed);
extern void right_motor_reverse(uint32_t speed);
extern void left_motor_stop();
extern void right_motor_stop();
extern void car_forward(uint32_t speed);
extern void car_reverse(uint32_t speed);
extern void car_turn_left(uint32_t speed);
extern void car_turn_right(uint32_t speed);
extern void car_stop(void);

#endif