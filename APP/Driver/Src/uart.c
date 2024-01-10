/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   uart.c 
作者:   龙川
说明:   串口控制
***************************************************************************************************/
#include "uart.h"

/**
**********************************************************************************************
USART2  232
USART3  485
UART4   留着不做处理
**********************************************************************************************
**/
//一次最多收发128字节数据
#define TxBufferLen  128
#define RxBufferLen  128

ComFifoStruct  USART2_FIFO;
ComFifoStruct  USART3_FIFO;

uint8_t USART2_TXBuffer[TxBufferLen];
uint8_t USART2_RXBuffer[RxBufferLen];

uint8_t USART3_TXBuffer[TxBufferLen];
uint8_t USART3_RXBuffer[RxBufferLen];

 /**
****************************************************************************************
@brief:    UART_FIFOInit 初始化串口FIFO
@Input：   NULL
@Output：  NULL
@Warning:  NULL  
@note:     龙川2019-4-10
****************************************************************************************
 **/
void UART_FIFOInit(void)
{
	memset(&USART2_FIFO,0,sizeof(USART2_FIFO));
	USART2_FIFO.rxFifo.len = RxBufferLen;
	USART2_FIFO.rxFifo.data = USART2_RXBuffer;
	USART2_FIFO.txFifo.len = TxBufferLen;
	USART2_FIFO.txFifo.data = USART2_TXBuffer;
	
	memset(&USART3_FIFO,0,sizeof(USART3_FIFO));
	USART3_FIFO.rxFifo.len = RxBufferLen;
	USART3_FIFO.rxFifo.data = USART3_RXBuffer;
	USART3_FIFO.txFifo.len = TxBufferLen;
	USART3_FIFO.txFifo.data = USART3_TXBuffer;

}

/**
****************************************************************************************
@brief:    Uart_Init 初始化串口
@Input：   UART  初始化的串口
		   BaudRate 初始化波特率
@Output：  NULL
@Return    NULL
@Warning:  8bit 1位停止位 无校验位 发送和接收都是使用中断非阻塞方式，NVIC在main函数配置
@note:     龙川2019-4-10
****************************************************************************************
 **/
 void Uart_Init(USART_TypeDef *UART,uint32_t BaudRate )
 {
	uint16_t timeout;
	UART_HandleTypeDef Huart;
	Huart.Instance = UART;
	Huart.Init.BaudRate = BaudRate;
	Huart.Init.WordLength = UART_WORDLENGTH_8B;
	Huart.Init.StopBits = UART_STOPBITS_1;
	Huart.Init.Parity = UART_PARITY_NONE;
	Huart.Init.Mode = UART_MODE_TX_RX;
	Huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	Huart.Init.OverSampling = UART_OVERSAMPLING_16;
	/* Enable the USART Data Register not empty Interrupt */
    __HAL_USART_ENABLE_IT(&Huart, USART_IT_RXNE); 
	 
	HAL_UART_Init(&Huart);
	timeout = 0;
	 while(((Huart.Instance->SR&0X40)==0)&&(timeout<0XFFF))//复位之后第一个字节发送不成功,不是发送不成功而是被第二个字节顶出去了
	{
		timeout++;
	}
 }
 
 /**
****************************************************************************************
@brief:    Uart_GPIOInit初始化串口IO
@Input：   NULL
@Output：  NULL
@Warning:  如果是485还要增加一个控制线  
@note:     龙川2019-4-10
****************************************************************************************
 **/
void Uart_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	UART_FIFOInit();
    //USART2
	//IO重映射Remap     (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
	__HAL_AFIO_REMAP_USART2_ENABLE();	
	__HAL_RCC_USART2_CLK_ENABLE();
	//PD5
	GPIO_InitStruct.Pin =  GPIO_PIN_5;	 
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//PD6
	GPIO_InitStruct.Pin =  GPIO_PIN_6;	 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//USART3
	//IO重映射Full remap     (TX/PD8,  RX/PD9,  CK/PD10, CTS/PD11, RTS/PD12)
	__HAL_AFIO_REMAP_USART3_ENABLE();
	__HAL_RCC_USART3_CLK_ENABLE();
	
	//PD8
	GPIO_InitStruct.Pin =  GPIO_PIN_8;	 
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//PD9
	GPIO_InitStruct.Pin =  GPIO_PIN_9;	 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
//	//USART4
//	//PC10
//	GPIO_InitStruct.Pin =  GPIO_PIN_10;	 
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//	
//	//PC11
//	GPIO_InitStruct.Pin =  GPIO_PIN_11;	 
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


 /**
****************************************************************************************
@brief:    UART2_FIFOReceive 获取数据
@Input：   *data 接收数据Buffer指针
		   Len  需要取得数据长度
@Output：  Len 作为输出传递实际获得的数据长度
@Warning:  函数执行状态 ERR_NONE 或 ERR_GENERAL  
@note:     龙川2019-4-10
****************************************************************************************
 **/

uint8_t UART2_FIFOReceive(uint8_t *data,uint16_t *Len)
{
	uint32_t FifoDataLen;
	FifoDataLen = fifo_data_length(&USART2_FIFO.rxFifo);
	//FIFO里面没数据
	if(FifoDataLen == 0)
	{
		return ERR_GENERAL;
	}
	//从FIFO中读取数据
	*Len = fifo_out(&USART2_FIFO.rxFifo, data, *Len);
	
	return ERR_NONE;
}

 /**
****************************************************************************************
@brief:    UART3_FIFOReceive 获取数据
@Input：   *data 接收数据Buffer指针
		   Len  需要取得数据长度
@Output：  Len 作为输出传递实际获得的数据长度
@Warning:  函数执行状态 ERR_NONE 或 ERR_GENERAL  
@note:     龙川2019-4-10
****************************************************************************************
 **/

uint8_t UART3_FIFOReceive(uint8_t *data,uint16_t *Len)
{
	uint32_t FifoDataLen;
	FifoDataLen = fifo_data_length(&USART3_FIFO.rxFifo);
	//FIFO里面没数据
	if(FifoDataLen == 0)
	{
		return ERR_GENERAL;
	}
	//从FIFO中读取数据
	*Len = fifo_out(&USART3_FIFO.rxFifo, data, *Len);
	
	return ERR_NONE;
}



 /**
****************************************************************************************
@brief:    UART2_TransmitInFIFO 传输数据入队
@Input：   *data 发送数据Buffer指针
		   Len  需要取得数据长度
@Output：  NULL
@Warning:  NULL
@note:     龙川2019-4-10
****************************************************************************************
 **/

void UART2_TransmitInFIFO(uint8_t *data,uint16_t Len)
{
	//发送数据入队
	fifo_in(&USART2_FIFO.txFifo, data, Len);
}


 /**
****************************************************************************************
@brief:    UART3_FIFOTransmit 传输数据入队
@Input：   *data 发送数据Buffer指针
		   Len  需要取得数据长度
@Output：  NULL
@Warning:  NULL
@note:     龙川2019-4-10
****************************************************************************************
 **/

void UART3_TransmitInFIFO(uint8_t *data,uint16_t Len)
{
	//发送数据入队
	fifo_in(&USART3_FIFO.txFifo, data, Len);	
}

 /**
****************************************************************************************
@brief:    UART2_Transmit 传输数据
@Input：   NULL
@Output：  NULL
@return:   NULL
@Warning:  NULL
@note:     龙川2019-4-10
****************************************************************************************
 **/
void UART2_Transmit()
{
	uint32_t i,timeout,len;
	uint8_t Data;

	len = fifo_data_length(&USART2_FIFO.txFifo);
	
	if( len == 0)
		return;
	timeout = 0;
	while(((USART2->SR&0X40)==0)&&(timeout<0XFFF))//发送完成标志——这个一定要放在前面否则会导致复位之后第一个字节发送不成功
	{
		timeout++;
	}
	for(i=0;i<len;i++)
	{		
		fifo_try(&USART2_FIFO.txFifo,&Data,1);
		USART2->DR = (uint8_t)(Data & (uint8_t)0x00FF);
		timeout = 0;
		while(((USART2->SR&0X40)==0)&&(timeout<0XFFF))//发送完成标志——这个一定要放在前面否则会导致复位之后第一个字节发送不成功
		{
			timeout++;
		}
		if(timeout>=0XFFF )	//超时没发送成功，退出
		{
			fifo_untry(&USART2_FIFO.txFifo);
			return;
		}
		else
		{
			fifo_out_sync(&USART2_FIFO.txFifo);
		}
	}

}

 /**
****************************************************************************************
@brief:    UART3_Transmit 传输数据
@Input：   NULL
@Output：  NULL
@return:   NULL
@Warning:  NULL
@note:     龙川2019-4-10
****************************************************************************************
 **/
void UART3_Transmit()
{
	uint32_t i,timeout,len;
	uint8_t Data;

	len = fifo_data_length(&USART3_FIFO.txFifo);
	
	if( len == 0)
		return;
	
	for(i=0;i<len;i++)
	{	
		timeout = 0;
		while(((USART3->SR&0X40)==0)&&(timeout<0XFFF))//发送完成标志——这个一定要放在前面否则会导致复位之后第一个字节发送不成功
		{
			timeout++;
		}
		if(timeout>=0XFFF )	//超时没发送成功，退出
		{
			return;
		}
		else
		{
			fifo_out_sync(&USART3_FIFO.txFifo);
		}
		fifo_try(&USART3_FIFO.txFifo,&Data,1);
		USART3->DR = (uint8_t)(Data & (uint8_t)0x00FF);
	
	}
}



