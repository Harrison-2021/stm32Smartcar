#include "bluetooth.h"

void bluetooth_car_control(uint8_t *buffer,uint32_t size) {
    switch(buffer[0]){
            case 'w':
                car_forward(800);
                printf("forward\r\n");
                break;
            
        case 's':
                car_reverse(800);
                printf("reverse\r\n");
                break;
        case 'a':
                car_turn_left(800);
                printf("turn left\r\n");
                break;
    
        case 'd':
                car_turn_right(800);
                printf("turn right\r\n");
                break;
        default: break;
    }
    
    __HAL_TIM_SET_COUNTER(&htim4,0); // 每次触发点击，重置定时器
    __HAL_TIM_CLEAR_FLAG(&htim4,TIM_FLAG_UPDATE);// 清除标志更新位
    HAL_TIM_Base_Start_IT(&htim4); // 开始定时器
        
}

/*  重写定时器中断处理函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if(htim == &htim4){
        car_stop();
        printf("time over!\r\n");
        HAL_TIM_Base_Stop_IT(&htim4); // 小车停止后，定时器停止工作
    }
}

void bluetooth_test() {
    uart_interrupt_idel_init();
}