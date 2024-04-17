#ifndef _MY_UART_H
#define _MY_UART_H

#include "usart.h"
#include "string.h"
#include "stdio.h"

#define RX_BUFFER_SIZE 1024

extern void uart_test();
extern void uart_interrupt_init();
extern void uart_interrupt_idel_init();

#endif