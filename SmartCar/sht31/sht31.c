#include "sht31.h"

/* ���������ֽڵ�����-��ַѡ�񡢸�λ����������������� 
   IICͨ�Ź����Ѿ��������ӿڷ�װ���ˣ�ֻ�贫��������ü���
*/
void sht31_send_cmd(uint16_t cmd) {
    // ��8�ֽ��ȴ����ٴ���8�ֽ�-��cmd���ݷŽ��ڴ���ͨ��IIC����
    uint8_t tx_buf[2];
    tx_buf[0] = cmd >> 8;  // ��8λ
    tx_buf[1] = cmd & 0xff; // ��8λ

    HAL_StatusTypeDef ret;
    
    ret = HAL_I2C_Master_Transmit(&hi2c1,SHT31_ADDR_WRITE,
                                    tx_buf,2,HAL_MAX_DELAY);
    if(ret != HAL_OK) {
        printf("HAL_I2C_Master_Transmit failed!\r\n");
        return;
    }
    
}

/* ��ʼ��sht31ģ�� */
void sht31_init() {
    // 1.��λ����ʼ��
    sht31_send_cmd(SHT31_SOFT_RESET);
    HAL_Delay(1000);
    // 3.���ò�������������ڣ���ʼ����
    sht31_send_cmd(SHT31_MEASUREMENT);
}

/* ������ʪ������ 
   Ҫ���ɼ������ݽ����ռ������ڲ����з���
*/
void sht31_sample_temp_humi(float *ptemp, float *phumi) {
    HAL_StatusTypeDef ret;
    uint8_t rx_buf[6];
    uint16_t data;

    // 1.�ȷ�������������ݵ�����
    sht31_send_cmd(SHT31_FETCH_DATA);

    // 2.����sht31ͨ��iic���ݵ�����-����6���ֽ�����
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

    // 3.�Խ��յ����ݽ�������
    // 16λ�¶�����ƴ���뻻�����϶�
    data = (rx_buf[0] << 8 | rx_buf[1]);
    *ptemp = -45 + (float)(175 * data) / 65535; // ����Ҫǿת���������ֵ����
    // 16λʪ������ƴ����������
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