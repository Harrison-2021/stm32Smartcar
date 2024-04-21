#include "tm.h"

void tm1637_start() {
    TM1637_CLK_H;
    TM1637_DAT_H;
    HAL_Delay(TM1637_DELAY_TIME);
	
    TM1637_DAT_L;
    HAL_Delay(TM1637_DELAY_TIME);
    
}

void tm1637_stop() {
    TM1637_CLK_L;
    TM1637_DAT_L;
    HAL_Delay(TM1637_DELAY_TIME);
    
    TM1637_CLK_H;
    HAL_Delay(TM1637_DELAY_TIME);
    TM1637_DAT_H;
    HAL_Delay(TM1637_DELAY_TIME);

}

void tm1637_ack() {
    TM1637_CLK_L;
    HAL_Delay(TM1637_DELAY_TIME);
    TM1637_CLK_H;
    HAL_Delay(TM1637_DELAY_TIME);

}

/* ����һ���ֽ� -���ֽ��ȴ�*/
void tm1637_write_byte(uint8_t data) {
    int i;
    for(i = 0; i < 8; i++) {
        // 1.������CLK���͵�ƽʱ�����ܴ�DAT��ƽ
        TM1637_CLK_L;
        HAL_Delay(TM1637_DELAY_TIME);
        // 2.��ȡdata���ֽڵ�ƽ����DAT�źű�ʾ
        if(data & 1) TM1637_DAT_H;
        else TM1637_DAT_L;
        // 3.����clk,�ߵ�ƽ�ڼ䣬��tm1637оƬ��ȡ����
        TM1637_CLK_H;
        HAL_Delay(TM1637_DELAY_TIME);
        // 4.�ƶ�data�����¸����λ
        data >>= 1;
    }
}

/* ����ָ�� */
void tm1637_write_cmd(uint8_t cmd) {
    tm1637_start();
    tm1637_write_byte(cmd);
    tm1637_ack();
    tm1637_stop();
}

/* ���͵�ַ������ */
void tm1637_write_data(uint8_t addr, uint8_t data) {
    tm1637_start();
    tm1637_write_byte(addr);
    tm1637_ack();

    tm1637_write_byte(data);
    tm1637_ack();
    tm1637_stop();
}

/* ��ʾʱ�� 12:37*/
void tm1637_display_time(uint8_t hour, uint8_t minute) {
	// ���ܶ����ȫ�ֱ���������ϵͳͬ��
	const uint8_t segmentMap[] = {
		0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
		0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
		0x00
	};
    // 1.������������ָ�д������ָ����ַ����ͨģʽ
    tm1637_write_cmd(TM1637_CMD);
    // 2.���͸�����ܵ�ַ������
    tm1637_write_data(TM1637_ADDR1,segmentMap[hour/10]);
    tm1637_write_data(TM1637_ADDR2,segmentMap[hour%10] + 0x80);//��ʾdpð��
    tm1637_write_data(TM1637_ADDR3,segmentMap[minute/10]);
    tm1637_write_data(TM1637_ADDR4,segmentMap[minute%10]);
    // 3.�����������׼���ú󣬲������ͣ�һͬ��ʾ
    tm1637_write_cmd(TM1637_DSPLAY);
}

void tm1637_test() {
    int i;     
    RTC_TimeTypeDef time;   
    while(1){                 
        for(i = 0;i < 60;i ++){
            HAL_RTC_GetTime(&hrtc,&time,RTC_FORMAT_BIN);
            // tm1637_display_time(12,i);
            tm1637_display_time(time.Minutes, time.Seconds);
			printf("time %02d:%02d\r\n",time.Minutes,time.Seconds);
            //HAL_Delay(1000);
            
        }
    }
}