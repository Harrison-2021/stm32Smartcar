#include "motor.h"

/* ����ǰ��-�����߽ӷ������������Ӳ��ԭ������෴ 
   PA6 0(tim3,ch1), PA7 PWM (tim3,ch2)
*/
void left_motor_forward(uint32_t speed) {
    // 1.PA7,pwmռ�ձ�����
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, speed);
    // 2.PA7,��ʱ������
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    // 3.PA6,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    // 4.PA6,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
}

/* ��������-�����߽ӷ������������Ӳ��ԭ������෴
   PA6 PWM(tiAm3,ch1), PA7 0 (tim4,ch2)
*/
void left_motor_reverse(uint32_t speed) {
    // 1.PA6,pwmռ�ձ�����
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
    // 2.PA6,��ʱ������
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    // 3.PA7,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    // 4.PA7,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

/* ����ֹͣ-��������ֹͣ��
   PA6 0(tiAm3,ch1), PA7 0 (tim4,ch2)
*/
void left_motor_stop() {
    // 1.PA6,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    // 2.PA6,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    // 3.PA7,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
    // 4.PA7,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

/* �ҵ��ǰ�� 
   PB0 PWM(tim3,ch3), PB1 0 (tim4,ch4)
*/
void right_motor_forward(uint32_t speed) {
    // 1.PB0,pwmռ�ձ�����
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, speed);
    // 2.PB0,��ʱ������
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    // 3.PB1,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
    // 4.PB1,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

/* �ҵ������ 
   PB0 0 (tim3,ch3), PB1 pwm (tim4,ch4)
*/
void right_motor_reverse(uint32_t speed) {
    // 1.PB1,pwmռ�ձ�����
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, speed);
    // 2.PB1,��ʱ������
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
    // 3.PB0,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    // 4.PB0,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

/* �ҵ��ֹͣ-��������ֹͣ
   PB0 0 (tim3,ch3), PB1 0 (tim4,ch4)
*/
void right_motor_stop() {
    // 1.PB0,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
    // 2.PB0,�ܽ�����Ϊ0
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    // 3.PB1,��ʱ���رգ�pwm�رգ�
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
    // 4.PB1,�ܽ�����Ϊ0
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