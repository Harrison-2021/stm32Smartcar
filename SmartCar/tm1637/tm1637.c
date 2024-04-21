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

/* 发送一个字节 -低字节先传*/
void tm1637_write_byte(uint8_t data) {
    int i;
    for(i = 0; i < 8; i++) {
        // 1.先拉低CLK，低电平时，才能传DAT电平
        TM1637_CLK_L;
        HAL_Delay(TM1637_DELAY_TIME);
        // 2.获取data低字节电平，以DAT信号表示
        if(data & 1) TM1637_DAT_H;
        else TM1637_DAT_L;
        // 3.拉高clk,高电平期间，让tm1637芯片读取数据
        TM1637_CLK_H;
        HAL_Delay(TM1637_DELAY_TIME);
        // 4.移动data，找下个最低位
        data >>= 1;
    }
}

/* 发送指令 */
void tm1637_write_cmd(uint8_t cmd) {
    tm1637_start();
    tm1637_write_byte(cmd);
    tm1637_ack();
    tm1637_stop();
}

/* 发送地址和数据 */
void tm1637_write_data(uint8_t addr, uint8_t data) {
    tm1637_start();
    tm1637_write_byte(addr);
    tm1637_ack();

    tm1637_write_byte(data);
    tm1637_ack();
    tm1637_stop();
}

/* 显示时间 12:37*/
void tm1637_display_time(uint8_t hour, uint8_t minute) {
	// 不能定义成全局变量，会与系统同名
	const uint8_t segmentMap[] = {
		0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
		0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
		0x00
	};
    // 1.发送数据命令指令：写操作，指定地址，普通模式
    tm1637_write_cmd(TM1637_CMD);
    // 2.发送各数码管地址和数据
    tm1637_write_data(TM1637_ADDR1,segmentMap[hour/10]);
    tm1637_write_data(TM1637_ADDR2,segmentMap[hour%10] + 0x80);//显示dp冒号
    tm1637_write_data(TM1637_ADDR3,segmentMap[minute/10]);
    tm1637_write_data(TM1637_ADDR4,segmentMap[minute%10]);
    // 3.待数码管数据准备好后，并发发送，一同显示
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