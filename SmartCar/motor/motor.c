#include "motor.h"

/* 左电机前进-因电机线接反，左电机软件与硬件原理控制相反 
   PA6 0(tim3,ch1), PA7 PWM (tim3,ch2)
*/
void left_motor_forward(uint32_t speed) {
    // 1.PA7,pwm占空比设置
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, speed);
    // 2.PA7,定时器开启
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    // 3.PA6,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    // 4.PA6,管脚输入为0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

/* 左电机后退-因电机线接反，左电机软件与硬件原理控制相反
   PA6 PWM(tiAm3,ch1), PA7 0 (tim4,ch2)
*/
void left_motor_reverse(uint32_t speed) {
    // 1.PA6,pwm占空比设置
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
    // 2.PA6,定时器开启
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    // 3.PA7,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    // 4.PA7,管脚输入为0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

/* 左电机停止-电流快速停止法
   PA6 0(tiAm3,ch1), PA7 0 (tim4,ch2)
*/
void left_motor_stop() {
    // 1.PA6,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    // 2.PA6,管脚输入为0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    // 3.PA7,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    // 4.PA7,管脚输入为0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

/* 右电机前进 
   PB0 PWM(tim3,ch3), PB1 0 (tim4,ch4)
*/
void right_motor_forward(uint32_t speed) {
    // 1.PB0,pwm占空比设置
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, speed);
    // 2.PB0,定时器开启
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    // 3.PB1,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
    // 4.PB1,管脚输入为0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

/* 右电机后退 
   PB0 0 (tim3,ch3), PB1 pwm (tim4,ch4)
*/
void right_motor_reverse(uint32_t speed) {
    // 1.PB1,pwm占空比设置
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed);
    // 2.PB1,定时器开启
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    // 3.PB0,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    // 4.PB0,管脚输入为0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

/* 右电机停止-电流快速停止
   PB0 0 (tim3,ch3), PB1 0 (tim4,ch4)
*/
void right_motor_stop() {
    // 1.PB0,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    // 2.PB0,管脚输入为0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    // 3.PB1,定时器关闭（pwm关闭）
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
    // 4.PB1,管脚输入为0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

void car_forward(uint32_t speed) {
    left_motor_forward(speed);
    right_motor_forward(speed);
}

void car_reverse(uint32_t speed) { 
    left_motor_reverse(speed);
    right_motor_reverse(speed);
}

void car_turn_left(uint32_t speed) {
    left_motor_reverse(speed);
    right_motor_forward(speed);
}

void car_turn_right(uint32_t speed) {
    right_motor_reverse(speed);
    left_motor_forward(speed);
}

void car_stop() {
    left_motor_stop();
    right_motor_stop();
}


void motor_test() {
    int i;
    for(i = 1; i < 10; i++) {
        car_forward(i*100);
        HAL_Delay(2 * 1000);
        car_stop();
        HAL_Delay(2 * 1000);
    
        car_reverse(i*100);
        HAL_Delay(2 * 1000);
        car_stop();
        HAL_Delay(2 * 1000);

        car_turn_left(i*100);
        HAL_Delay(2 * 1000);
        car_stop();
        HAL_Delay(2 * 1000);

        car_turn_right(i*100);
        HAL_Delay(2 * 1000);
        car_stop();
        HAL_Delay(2 * 1000);
    }
}