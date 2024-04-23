#include "sht31.h"

/* 发送两个字节的命令-地址选择、复位、测量命令、数据请求 
   IIC通信过程已经被函数接口封装好了，只需传入参数调用即可
*/
void sht31_send_cmd(uint16_t cmd) {
    // 高8字节先传，再传低8字节-将cmd数据放进内存中通过IIC传递
    uint8_t tx_buf[2];
    tx_buf[0] = cmd >> 8;  // 高8位
    tx_buf[1] = cmd & 0xff; // 低8位

    HAL_StatusTypeDef ret;
    
    ret = HAL_I2C_Master_Transmit(&hi2c1,SHT31_ADDR_WRITE,
                                    tx_buf,2,HAL_MAX_DELAY);
    if(ret != HAL_OK) {
        printf("HAL_I2C_Master_Transmit failed!\r\n");
        return;
    }
    
}

/* 初始化sht31模块 */
void sht31_init() {
    // 1.复位，初始化
    sht31_send_cmd(SHT31_SOFT_RESET);
    HAL_Delay(1000);
    // 3.设置测量命令：采样周期，开始采样
    sht31_send_cmd(SHT31_MEASUREMENT);
}

/* 采样温湿度数据 
   要将采集的数据进行收集，放在参数中返回
*/
void sht31_sample_temp_humi(float *ptemp, float *phumi) {
    HAL_StatusTypeDef ret;
    uint8_t rx_buf[6];
    uint16_t data;

    // 1.先发送请求接收数据的命令
    sht31_send_cmd(SHT31_FETCH_DATA);

    // 2.接收sht31通过iic传递的数据-接收6个字节数据
    ret = HAL_I2C_Master_Receive(&hi2c1,SHT31_ADDR_READ,
                                rx_buf,6,HAL_MAX_DELAY);
    if(ret != HAL_OK) {
        printf("HAL_I2C_Master_Receive failed!\r\n");
        return;
    }

    #ifdef SHT31_DEBUG
    printf("Sample Data:");
		int i;
        for(i = 0;i < 6;i ++){
                printf("%#x ",rx_buf[i]);
        }
        printf("\r\n");
    #endif // DEBUG

    // 3.对接收的数据进行整理
    // 16位温度数据拼接与换算摄氏度
    data = (rx_buf[0] << 8 | rx_buf[1]);
    *ptemp = -45 + (float)(175 * data) / 65535; // 类型要强转，否则除法值不对
    // 16位湿度数据拼接与结果换算
    data = (rx_buf[3] << 8 | rx_buf[4]);
    *phumi = (float)(100 * data) / 65535;
}

void sht31_test() {
    float temp;
    float humi;
    
    sht31_init();
    
    while(1){
        sht31_sample_temp_humi(&temp,&humi);
        printf("Temp:%.2f ,Humi:%.2f\r\n",temp,humi);
        HAL_Delay(1000);
    }
}