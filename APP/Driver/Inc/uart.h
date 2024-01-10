/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   uart.c 
作者:   龙川
说明:   串口控制
***************************************************************************************************/
#ifndef __UART_H
#define __UART_H
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "fifo.h"

#define USART2_TXByInt
#define USART3_TXByInt

extern ComFifoStruct  USART2_FIFO;
extern ComFifoStruct  USART3_FIFO;

extern void Uart_Init(USART_TypeDef *UART,uint32_t BaudRate );
extern void Uart_GPIOInit(void);
extern uint8_t UART2_FIFOReceive(uint8_t *data,uint16_t *Len);
extern uint8_t UART3_FIFOReceive(uint8_t *data,uint16_t *Len);
extern void UART2_TransmitInFIFO(uint8_t *data,uint16_t Len);
extern void UART3_TransmitInFIFO(uint8_t *data,uint16_t Len);
extern void UART2_Transmit(void);
extern void UART3_Transmit(void);
#endif


