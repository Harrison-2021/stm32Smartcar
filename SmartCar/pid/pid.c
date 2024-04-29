#include "pid.h"

pid_t pid;
int32_t left_motor_pwm_speed  = MOTOR_PWM_SPEED;
int32_t right_motor_pwm_speed = MOTOR_PWM_SPEED;
bool pid_control = true;

/* 1.读取5路循迹传感器状态 */
uint8_t read_irs_state() {
    uint8_t ret = 0;
    uint8_t state[5];
    int i;

    /* 从低位到高位，从右往左 */
    state[0] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);
    state[1] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1);
    state[2] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
    state[3] = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13);
    state[4] = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);

    /* 拼接一个字节 */
    for(i = 0; i < 5; i++) {
        ret |= (state[i] << i);
    }

    return ret;
}

/* 2. 采用中值滤波算法获取传感器状态*/
uint8_t get_middle_filter_irs_state() {
    int i;
    uint8_t states[9];

    for(i = 0; i < 9; i++) {
        states[i] = read_irs_state();
    }

    #ifdef PID_DEBUG
    printf("irs:");
    for(i = 4;i >= 0;i --){
        if(states[4] & (1 << i)){
            printf("1");
        }else{
            printf("0");
        }
    }
    printf("\r\n");
    #endif // DEBUG

    return states[4];
}

/* 3. 根据传感器状态获取误差值
      注意，不能是uint8，可正可负
*/
int8_t calc_error_by_irs(uint8_t state) {
    // 根据小车轨迹，设置几个误差值，其它不在特殊轨迹的，误差值不变
    int8_t cur_error = pid.error;

     switch(state){
        // 左转
        case 0B11110: cur_error = -8;break; 
        case 0B10000:
        case 0B11000: cur_error = -7;break;
        case 0B11100: cur_error = -6;break;
        case 0B11101: cur_error = -4;break;
        case 0B11001: cur_error = -2;break;
        // 直行
        case 0B00000:
        case 0B11011: cur_error = 0;break;
        // 右转
        case 0B10011: cur_error = 2;break;
        case 0B10111: cur_error = 4;break;
        case 0B00111: cur_error = 6;break;
        case 0B00011:
        case 0B00001: cur_error = 7;break;
        case 0B01111: cur_error = 8;break;
        // 跑出赛道时，说明转弯力度不够，加大转弯力度
        case 0B11111: cur_error = pid.error > 0 ? 9 : - 9;
        }
        
    return cur_error;
}

/* 4.采用平均数求和滤波算法获取当前的误差值 */
int8_t get_current_irs_error() {
    int i;
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        uint8_t state = get_middle_filter_irs_state();
        sum += calc_error_by_irs(state);
    }

    return sum / 10;
    
}

/* 5.根据误差值采用位置式PID算法算出输出的控制量 */
int32_t pid_calc_output() {
    int32_t P, D;
    static int32_t I = 0;
    int32_t pid_output;

    pid.error = get_current_irs_error();
    P = pid.kp * pid.error;
    I += pid.ki * pid.error;
    D = pid.kd * (pid.error - pid.last_error);

    // 注意，要维护上次的误差，以便计算D值
    pid.last_error = pid.error;
    
    pid_output = P + I + D;

    return pid_output;
}

/* 6.根据PID算法的输出控制量调整左右轮速度 */
void update_motor_speed_by_pid(int32_t pid_output) {
    /* 轮子要恢复到之前的状态，防止轮子停止后不再启动  */
    if(!pid.error) {
        left_motor_pwm_speed = MOTOR_PWM_SPEED;
        right_motor_pwm_speed = MOTOR_PWM_SPEED;
        return;
    }
    /* 左轮转速控制，注意边界，超出范围以边界的Pwm值控制 */
    left_motor_pwm_speed += pid_output;
    if(left_motor_pwm_speed <= MOTOR_PWM_MIN_SPEED) {
        left_motor_pwm_speed = MOTOR_PWM_MIN_SPEED;
    }else if(left_motor_pwm_speed >= MOTOR_PWM_MAX_SPEED){
        left_motor_pwm_speed = MOTOR_PWM_MAX_SPEED;
    }

    right_motor_pwm_speed -= pid_output;
    if(right_motor_pwm_speed <= MOTOR_PWM_MIN_SPEED){
                right_motor_pwm_speed = MOTOR_PWM_MIN_SPEED;
    }else if(right_motor_pwm_speed >= MOTOR_PWM_MAX_SPEED){
            right_motor_pwm_speed = MOTOR_PWM_MAX_SPEED;
    }
}

/* 7.初始化PID参数 */
void pid_init() {
    pid.error = 0;
    pid.last_error = 0;
    pid.kp = PID_KP;
    pid.kd = PID_KD;
    pid.ki = PID_KI;
}

/* 8.根据PID算法控制小车 */
void pid_control_motor(void) {
    	// 跑大弯-可以原地旋转
        if(pid.error >= 7 && pid.error <= 9){
                 car_turn_right(MOTOR_PWM_MAX_SPEED);
                 return;
        }else if(pid.error >= -9 && pid.error <= -7){
                 car_turn_left(MOTOR_PWM_MAX_SPEED);
                 return;
        }
        
        left_motor_forward(left_motor_pwm_speed);
        right_motor_forward(right_motor_pwm_speed);
}

void pid_control_car(void) {
    int32_t pid_output;
    
    pid_init();
    
    while(pid_control){
        pid_output = pid_calc_output();
        update_motor_speed_by_pid(pid_output);
        pid_control_motor();
        HAL_Delay(10);
    }
}

void pid_test() {
    pid_control_car();
}