#include "my_uart.h"

uint8_t uart1_rx_buf[RX_BUFFER_SIZE];
uint8_t uart2_rx_buf[RX_BUFFER_SIZE];

/* 在stm32的MicroLIB库中实现的printf函数最终调用fputc */
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    return  EOF;
}

/* 固定长度中断初始化，只初始化一次-注册中断并准备数据 */
void uart_interrupt_init() {
    HAL_UART_Receive_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));
}

/* 重写固定长度回调函数，最终实现用户自定义的中断处理函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    int i;
	
	if(huart == &huart1){
		printf("uart1 recv interrupt\r\n");
		for(i = 0;i < sizeof(uart1_rx_buf);i ++){
            printf("%c:%d\r\n",uart1_rx_buf[i],
                               uart1_rx_buf[i]);
		}
        uart_interrupt_init(); // 再次初始化，便于下次调用回调函数
	 }
	
}

/* 不定长度中断初始化，只初始化一次-注册中断并准备数据 */
void uart_interrupt_idel_init() {
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, uart2_rx_buf, sizeof(uart2_rx_buf));
}

/* 重写固定长度回调函数，最终实现用户自定义的中断处理函数 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    int i;
	
	if(huart == &huart1){
        #ifdef UART_DEBUG
        printf("uart1 recv interrupt\r\n");
		for(i = 0;i < Size;i ++){
            printf("%c:%d\r\n",uart1_rx_buf[i],
                               uart1_rx_buf[i]);
		}
        #endif 
		HAL_StatusTypeDef res = HAL_UART_Transmit_IT(&huart2, uart1_rx_buf, Size);
        HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));   
	} else if(huart == &huart2) {
        #ifdef UART_DEBUG
        printf("uart2 recv interrupt\r\n");
		for(i = 0;i < Size;i ++){
            printf("%c:%d\r\n",uart2_rx_buf[i],
                               uart2_rx_buf[i]);
		}
        #endif // UART_DEBUG
        bluetooth_car_control(uart2_rx_buf, Size);
        HAL_UART_Transmit_IT(&huart1, uart2_rx_buf, Size);
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, uart2_rx_buf, sizeof(uart2_rx_buf));
    }
	
}

void uart_test() {
    float fdata = 1.23;
	int data = 100;
    HAL_StatusTypeDef res;
    
    /* 1.测试uart发送与接收数据的函数接口
    while(1) {
        // 1.通过uart向板子发送str
        res = HAL_UART_Transmit(&huart1, (uint8_t *)str, 
                strlen(str), HAL_MAX_DELAY);
        if(res != HAL_OK) {
            break;
        }

        // 2.板子通过uart等待读取数据，指定大小
        res = HAL_UART_Receive(&huart1, (uint8_t *) rx_buf,
                sizeof(rx_buf), HAL_MAX_DELAY);
        if(res != HAL_OK) break;

        // 3.板子CH340通过uart将接收到的数据,再次发送出去
        res = HAL_UART_Transmit(&huart1, (uint8_t *)rx_buf,
                sizeof(rx_buf), HAL_MAX_DELAY);
        if(res != HAL_OK) break;  
    } */

    /* 2.测试printf函数中fputc接口的重写 */
    /* printf("str = %s\r\n",str);
	printf("data = %d\r\n",data);
	printf("fdata = %f\r\n",fdata); */

    /* 3.测试固定长度中断方式发送固定大小数据 */
    // uart_interrupt_init();

    /* 4.测试不定长度中断方式发送固定大小数据 */
    uart_interrupt_idel_init();
    /* const char *str = "AT\r\n";
	uint8_t rx_buf[4];
    while(1) {
        // 1.通过uart向板子发送str
        res = HAL_UART_Transmit(&huart2, (uint8_t *)str, 
                strlen(str), HAL_MAX_DELAY);
        if(res == HAL_OK) {
            printf("uart2 Transmit success\r\n");
        }
		HAL_Delay(1000);
     
    }  */

    // 每秒ch340发送一次数据，当用户发送数据时，触发中断
    // while(1) {
    //     printf("hello world!");
    //     HAL_Delay(1000);
    // }
}