#include "my_uart.h"

uint8_t uart1_rx_buf[RX_BUFFER_SIZE];
uint8_t uart2_rx_buf[RX_BUFFER_SIZE];

/* ��stm32��MicroLIB����ʵ�ֵ�printf�������յ���fputc */
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1,HAL_MAX_DELAY);
    return  EOF;
}

/* �̶������жϳ�ʼ����ֻ��ʼ��һ��-ע���жϲ�׼������ */
void uart_interrupt_init() {
    HAL_UART_Receive_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));
}

/* ��д�̶����Ȼص�����������ʵ���û��Զ�����жϴ����� */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    int i;
	
	if(huart == &huart1){
		printf("uart1 recv interrupt\r\n");
		for(i = 0;i < sizeof(uart1_rx_buf);i ++){
            printf("%c:%d\r\n",uart1_rx_buf[i],
                               uart1_rx_buf[i]);
		}
        uart_interrupt_init(); // �ٴγ�ʼ���������´ε��ûص�����
	 }
	
}

/* ���������жϳ�ʼ����ֻ��ʼ��һ��-ע���жϲ�׼������ */
void uart_interrupt_idel_init() {
    HAL_UARTEx_ReceiveToIdle_IT(&huart1, uart1_rx_buf, sizeof(uart1_rx_buf));
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, uart2_rx_buf, sizeof(uart2_rx_buf));
}

/* ��д�̶����Ȼص�����������ʵ���û��Զ�����жϴ����� */
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
    
    /* 1.����uart������������ݵĺ����ӿ�
    while(1) {
        // 1.ͨ��uart����ӷ���str
        res = HAL_UART_Transmit(&huart1, (uint8_t *)str, 
                strlen(str), HAL_MAX_DELAY);
        if(res != HAL_OK) {
            break;
        }

        // 2.����ͨ��uart�ȴ���ȡ���ݣ�ָ����С
        res = HAL_UART_Receive(&huart1, (uint8_t *) rx_buf,
                sizeof(rx_buf), HAL_MAX_DELAY);
        if(res != HAL_OK) break;

        // 3.����CH340ͨ��uart�����յ�������,�ٴη��ͳ�ȥ
        res = HAL_UART_Transmit(&huart1, (uint8_t *)rx_buf,
                sizeof(rx_buf), HAL_MAX_DELAY);
        if(res != HAL_OK) break;  
    } */

    /* 2.����printf������fputc�ӿڵ���д */
    /* printf("str = %s\r\n",str);
	printf("data = %d\r\n",data);
	printf("fdata = %f\r\n",fdata); */

    /* 3.���Թ̶������жϷ�ʽ���͹̶���С���� */
    // uart_interrupt_init();

    /* 4.���Բ��������жϷ�ʽ���͹̶���С���� */
    uart_interrupt_idel_init();
    /* const char *str = "AT\r\n";
	uint8_t rx_buf[4];
    while(1) {
        // 1.ͨ��uart����ӷ���str
        res = HAL_UART_Transmit(&huart2, (uint8_t *)str, 
                strlen(str), HAL_MAX_DELAY);
        if(res == HAL_OK) {
            printf("uart2 Transmit success\r\n");
        }
		HAL_Delay(1000);
     
    }  */

    // ÿ��ch340����һ�����ݣ����û���������ʱ�������ж�
    // while(1) {
    //     printf("hello world!");
    //     HAL_Delay(1000);
    // }
}