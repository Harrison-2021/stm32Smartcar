# 1. 项目介绍
- 项目本项目以STM32的ARM Cortex-M核为底板，基于HAL库接口，使用MDK,CubrMX开发工具对STM32常见外设进行开发；
- 基于PID算法Wifi智能循迹小车；
- stm32芯片进行智能车控制。

# 2. 项目模块

## [1.stm32GPIO控制](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/1.stm32GPIO%E6%8E%A7%E5%88%B6.md)

- CubeMX配置（新建工程，芯片选择，时钟配置，管脚配置，自动生成Keil工程）；
- HAL库接口使用（GPIO初始化，管脚电平输入与输出）;
- LED灯闪烁与按键控制。

## [2.stm32启动流程](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/2.stm32%E5%90%AF%E5%8A%A8%E6%B5%81%E7%A8%8B.md)

- tm32芯片复位后，根据BOOT引脚选择启动方式（主Flash启动，内置ROM, 内置SRAM启动）；
- 从Flash启动流程（内存映射，堆栈、中断向量表内存空间分配，初始化，main函数执行）。

## [3.stm32串口通讯](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/3.stm32%E4%B8%B2%E5%8F%A3%E9%80%9A%E8%AE%AF.md)

- 原理图阅读与CubeMx配置；
- 基于HAL库接口实现UART收发数据；基于MicroLIB库实现printf函数重写；
- 中断方式接收数据（基于CubeMx使能中断与设置优先级，中断初始化，回调函数）。

## [4.PWM电机控制](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/4.PWM%E7%94%B5%E6%9C%BA%E6%8E%A7%E5%88%B6.md)

- H桥电路控制（正反转，电机速度控制，启停控制）；
- 电机种类（有刷电机，无刷电机，步进电机，伺服电机，永磁同步电机）；
- 使用CubeMx配置PWM,基于PWM的HAL库接口控制电机正反转与停止，从而控制小车方向与刹停。

## [5.PS2手柄控制小车](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/5.PS2%E6%89%8B%E6%9F%84%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6.md)

- PS2手柄特点（手柄，接收器）与通讯协议（时序，协议）；
- CubeMX配置（时钟配置，SPI配置）；
- 主板通过SPI协议读取PS2手柄数据；通过读取PS2手柄按下的按键值控制小车。

## [6.ESP8266无线wifi控制小车](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/6.ESP8266%E6%97%A0%E7%BA%BFwifi%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6.md)

- ESP8266WIFI模块特点；
- PC机与ESP8266建立通信（两个UART之间通信）；
- ESP8266配置wifi的AT指令（指令格式，客户端模式设定，服务端模式设定，TCP协议与UDP协议传输数据，透传模式）；
- 通过ESP8266控制小车（AT指令封装，UART通信控制小车电机，定时器优化时实控制问题）。

## [7.蓝牙控制小车](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/7.%E8%93%9D%E7%89%99%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6.md)

- 蓝牙相关AT命令；
- 蓝牙串口调试助手使用；
- 使用蓝牙模块控制小车。

## [8.数码管显示RTC时间](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/8.%E6%95%B0%E7%A0%81%E7%AE%A1%E6%98%BE%E7%A4%BARTC%E6%97%B6%E9%97%B4.md)

- 数码管工作原理（共阳极与共阴级分类，真值表，通信协议-类似IIC）；
- TM167数码管控制芯片工作原理（数据指令，通信协议）；
- 使用TM167进行RTC时间读取与显示。

## [9.SHT31温度传感器](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/9.SHT31%E6%B8%A9%E5%BA%A6%E4%BC%A0%E6%84%9F%E5%99%A8.md)

- SHT31温湿度传感器特点；
- 基于IIC通信对温湿度数据读取。

## [10.继电器控制](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/10.%E7%BB%A7%E7%94%B5%E5%99%A8%E6%8E%A7%E5%88%B6.md)

- 继电器工作原理；
- 通过HAL库控制继电器操作。

## [11.PID算法自动控制小车循迹](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/11.PID%E7%AE%97%E6%B3%95%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6%E8%87%AA%E5%8A%A8%E5%BE%AA%E8%BF%B9.md)

- PID控制算法分析（位式控制，PID控制算法原理）；
- PID算法实现（位置式PID, 增量式PID）；
- PID控制小车自动循迹（五路循环板，中值滤波算法获取循迹板状态，平均数求和滤波算法获取当前的误差值，位置式PID算法算出输出的控制量，根据控制量调整左右轮速度）。

# 3. 测试结果展示

## [1.stm32GPIO控制](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/1.stm32GPIO%E6%8E%A7%E5%88%B6.md)

### 1. LED灯控制

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2d9ad2f43aad499095cf2df310a6d176.png)

### 2. 按键控制

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/c1bd245abde943f9a6c3cec184d41dbd.png)

## [2.stm32启动流程](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/2.stm32%E5%90%AF%E5%8A%A8%E6%B5%81%E7%A8%8B.md)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/fc206c6baa37411f98bd48aa073b6e4a.png)

## [3.stm32串口通讯](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/3.stm32%E4%B8%B2%E5%8F%A3%E9%80%9A%E8%AE%AF.md)

### 1. 轮循方式收发数据

#### 发送数据

```c
#include "usart.h"
#include <string.h>

void uart_test(void)
{
    HAL_StatusTypeDef ret;
    const char *str = "hello world\r\n";
    uint8_t rx_buffer[10];
        
    while(1){
    	// 1.板子通过uart向调试串口发送数据：str
        ret = HAL_UART_Transmit(&huart1,(uint8_t*)str,
                             strlen(str),HAL_MAX_DELAY);
        if(ret != HAL_OK) break;
           
        // 2.uart等待接收数据（阻塞方式）-接收用户（串口调试助手）通过uart向板子发数据
        // 必须要等待sizeof(rx_buffer)个字节
        ret = HAL_UART_Receive(&huart1,(uint8_t *)rx_buffer,
                             sizeof(rx_buffer),HAL_MAX_DELAY);
        // 3.uart将板子接收的数据，再次发给用户（串口调试助手）   
        ret = HAL_UART_Transmit(&huart1,(uint8_t *)rx_buffer,
                            sizeof(rx_buffer),HAL_MAX_DELAY);
        if(ret != HAL_OK) break;
     }
        
        return;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/54a06237cd914dc99a918f2a12cd031c.png)

#### 接收数据

```c
#include "usart.h"
#include <string.h>

void uart_test(void)
{
    HAL_StatusTypeDef ret;
    const char *str = "hello world\r\n";
    uint8_t rx_buffer[10];
        
    while(1){
    	// 1.通过uart向板子发送数据：str
        ret = HAL_UART_Transmit(&huart1,(uint8_t*)str,
                             strlen(str),HAL_MAX_DELAY);
        if(ret != HAL_OK) break;
           
        // 2.uart等待接收数据（阻塞方式）-接收用户通过uart向板子发数据
        // 必须要等待sizeof(rx_buffer)个字节
        ret = HAL_UART_Receive(&huart1,(uint8_t *)rx_buffer,
                             sizeof(rx_buffer),HAL_MAX_DELAY);
        // 3.uart将板子接收的数据，再次发给用户      
        ret = HAL_UART_Transmit(&huart1,(uint8_t *)rx_buffer,
                            sizeof(rx_buffer),HAL_MAX_DELAY);
        if(ret != HAL_OK) break;
     }
        
        return;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/7c8779b80ac64b549d0e0831c0a66802.png)

### 2. 基于MicroLIB库实现printf函数重写

```c
// 在stm32的MicroLIB库中实现的printf函数最终调用fputc
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    return  EOF;
}

void uart_test() {
    float fdata = 1.23;
	int data = 100;
    HAL_StatusTypeDef res;
    const char *str = "hello world!\r\n";
    uint8_t rx_buf[10];

    /* 测试printf函数中fputc接口的重写 */
    printf("str = %s\r\n",str);
	printf("data = %d\r\n",data);
	printf("fdata = %f\r\n",fdata);
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/01e2c3dbe121476a95a18927450f564a.png)

### 3. 中断方式接收数据

#### 发送固定长度

```c
#include "usart.h"
#include <stdio.h>

#define RX_BUFFER_SIZE 10

uint8_t rx_buffer[RX_BUFFER_SIZE];

//1.这个函数在main函数中要调用一次，因此要在回调函数中再次调用，保证一直使用
void uart_interrupt_init(void) {
     /*interrupt mode recive data,recv sizeof(rx_buffer) data,
      *call back HAL_UART_RxCpltCallback
      */
    HAL_UART_Receive_IT(&huart1, rx_buffer,sizeof(rx_buffer));
}

//2.这个回调函数只有在UART收到了10个字节数据才会调用一次
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int i;
	
	if(huart == &huart1){
		printf("uart1 recv interrupt\r\n");
		for(i = 0;i < sizeof(uart1_rx_buffer);i ++){
            		printf("%c:%d\r\n",uart1_rx_buffer[i],uart1_rx_buffer[i]);
		}
        	uart_interrupt_init() // 再次初始化，便于下次调用回调函数
	 }
	
	 return;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/47202970379e4e6380612e7a7cc46169.png)

#### 发送不定长度

```c
#include "usart.h"
#include <stdio.h>

#define RX_BUFFER_SIZE 1024

uint8_t uart1_rx_buf[RX_BUFFER_SIZE];

/* 不定长度中断初始化，只初始化一次-注册中断并准备数据 */
void uart_interrupt_idel_init() {
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));
}

/* 重写不定长度回调函数，最终实现用户自定义的中断处理函数 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
           int i;
	
           if(huart == &huart1){
		printf("uart1 recv interrupt\r\n");
		for(i = 0; i < Size; i ++){
           			 printf("%c:%d\r\n",uart1_rx_buf[i],
                               uart1_rx_buf[i]);
		}
        	uart_interrupt_idel_init(); // 再次初始化，便于下次调用回调函数
	 }
	
}
```

![image-20240416210643589](C:\Users\ls2690069470\AppData\Roaming\Typora\typora-user-images\image-20240416210643589.png)

## [6.ESP8266无线wifi控制小车](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/6.ESP8266%E6%97%A0%E7%BA%BFwifi%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6.md)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/74fa322b38684b41bbe28dc676d2854f.png)

## [7.蓝牙控制小车](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/7.%E8%93%9D%E7%89%99%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6.md)

![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/2ed5f9efbc21493f8f1ef0d76faa4869.png)

## [8.数码管显示RTC时间](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/8.%E6%95%B0%E7%A0%81%E7%AE%A1%E6%98%BE%E7%A4%BARTC%E6%97%B6%E9%97%B4.md)

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/43068029d32c4098a75aa904735fbffc.png)

## [9.SHT31温度传感器](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/9.SHT31%E6%B8%A9%E5%BA%A6%E4%BC%A0%E6%84%9F%E5%99%A8.md)

![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/6323e6bd3a3c4134864b07e5527acfeb.png)

## [11.PID算法自动控制小车循迹](https://github.com/Harrison-2021/stm32Smartcar/blob/main/nodes/11.PID%E7%AE%97%E6%B3%95%E6%8E%A7%E5%88%B6%E5%B0%8F%E8%BD%A6%E8%87%AA%E5%8A%A8%E5%BE%AA%E8%BF%B9.md)

![请添加图片描述](https://i-blog.csdnimg.cn/direct/a332fd7d817749e2817606bde16ec4d7.gif)
