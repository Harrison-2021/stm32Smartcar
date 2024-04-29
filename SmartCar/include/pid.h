#ifndef _PID_H
#define _PID_H

#include "gpio.h"
#include <stdio.h>
#include "motor.h"
#include <stdbool.h>

#define PID_DEBUG
#define MOTOR_PWM_SPEED 300
#define MOTOR_PWM_MAX_SPEED 800
#define MOTOR_PWM_MIN_SPEED 0

#define PID_KP 25
#define PID_KI 0.1 // 可以调整摆动大小，增大可以减少摆动
#define PID_KD 15

typedef struct {
    int8_t error;
    int8_t last_error;
    float kp;
    float ki;
    float kd;
} pid_t;

extern uint8_t read_irs_state();
extern uint8_t get_middle_filter_irs_state();
extern void pid_test();
extern int8_t calc_error_by_irs(uint8_t state);
extern int8_t get_current_irs_error();
extern int32_t pid_calc_output();
extern void update_motor_speed_by_pid(int32_t pid_output);
extern void pid_init();
extern void pid_control_motor(void);
extern void pid_control_car(void);

#endif