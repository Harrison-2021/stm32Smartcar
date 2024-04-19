#include "ps2.h"

/* 读取手柄操作传入的数据 */
uint16_t read_ps2_data() {
    uint16_t key_code;
    uint8_t rx[9] = {0};
    uint8_t tx[9] = {0x1, 0x42};
    HAL_StatusTypeDef ret;
    int i;

    // 1.拉低CS片选信号，开始通讯-PB12
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

    // 2.板子先向手柄一次性发送9个字节,并同时接收
    /* for(i = 0;i < 9;i ++){
        ret = 
            HAL_SPI_TransmitReceive(&hspi2,&tx[i],&rx[i],1,1000);
        if(ret != HAL_OK){
            printf("Fail to HAL_SPI_TransmitReceive,err:%d\r\n",
                   ret);
            break;
        }
    } */
    ret = HAL_SPI_TransmitReceive(&hspi2,tx,rx,9,1000);
        if(ret != HAL_OK){
            printf("Fail to HAL_SPI_TransmitReceive,err:%d\r\n",
                   ret);
        }

    // 3.拉高CS片选信号，结束通讯-PB12
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

    // 4.调试-打印接收手柄通过spi传输的数据
    #ifdef PS2_DEBUG
    for(i = 0;i < 9;i ++){
        printf("%#x ",rx[i]);
    }
    printf("\r\n");
    #endif 

    // 5.获取第3和第4字节的数据-手柄信息，拼接成一个16位数据
    key_code = rx[4] << 8 | rx[3];
    return key_code;
 }

/* 将手柄读入的数据转为枚举类型的key值，便于操作单片机 */
int8_t read_ps2_press_key() {
    uint8_t key_number = PS2_EMPTY_KEY;
    int i;
    int pres_flag = 1;

    // 1.读取数据，先判断是否为空键
    uint16_t key_code = read_ps2_data();
    if(key_code == PS2_EMPTY_KEY1 || key_code == PS2_EMPTY_KEY2) {
        return key_number;
    }

    // 2.从低到高读取每一位，判断是否为0-按下
    for(i = 0; i < 16; i++) {
        pres_flag = (key_code & (1 << i));
        if(!pres_flag) {
            key_number = i;
            #ifdef PS2_DEBUG1
            printf("press key number:%d\r\n",key_number);
            #endif // 0
        }
    }
    return key_number;
}

/* 控制小车 */
void ps2_control_car() {
    int8_t key_number = read_ps2_press_key();

    if(key_number == PS2_EMPTY_KEY) {
        car_stop();
        return;
    }

    switch(key_number){
        case PS2_L_UP:
        case PS2_R_UP:
                car_forward(800);
                break;
        
        case PS2_L_DOWN:
        case PS2_R_DOWN:
                car_reverse(800);
                break;
        
        case PS2_L_LEFT:
        case PS2_R_LEFT:
                car_turn_left(800);
                break;

        case PS2_L_RIGHT:
        case PS2_R_RIGHT:
                car_turn_right(800);
                break;
    }
}

 void ps2_test() {
    while(1) {
        ps2_control_car();
        HAL_Delay(10);
    }
 }