/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   uart.c 
����:   ����
˵��:   ���ڿ���
***************************************************************************************************/
#include "uart.h"

/**
**********************************************************************************************
USART2  232
USART3  485
UART4   ���Ų�������
**********************************************************************************************
**/
//һ������շ�128�ֽ�����
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
@brief:    UART_FIFOInit ��ʼ������FIFO
@Input��   NULL
@Output��  NULL
@Warning:  NULL  
@note:     ����2019-4-10
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
@brief:    Uart_Init ��ʼ������
@Input��   UART  ��ʼ���Ĵ���
		   BaudRate ��ʼ��������
@Output��  NULL
@Return    NULL
@Warning:  8bit 1λֹͣλ ��У��λ ���ͺͽ��ն���ʹ���жϷ�������ʽ��NVIC��main��������
@note:     ����2019-4-10
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
	 while(((Huart.Instance->SR&0X40)==0)&&(timeout<0XFFF))//��λ֮���һ���ֽڷ��Ͳ��ɹ�,���Ƿ��Ͳ��ɹ����Ǳ��ڶ����ֽڶ���ȥ��
	{
		timeout++;
	}
 }
 
 /**
****************************************************************************************
@brief:    Uart_GPIOInit��ʼ������IO
@Input��   NULL
@Output��  NULL
@Warning:  �����485��Ҫ����һ��������  
@note:     ����2019-4-10
****************************************************************************************
 **/
void Uart_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	UART_FIFOInit();
    //USART2
	//IO��ӳ��Remap     (CTS/PD3, RTS/PD4, TX/PD5, RX/PD6, CK/PD7)
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
	//IO��ӳ��Full remap     (TX/PD8,  RX/PD9,  CK/PD10, CTS/PD11, RTS/PD12)
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
@brief:    UART2_FIFOReceive ��ȡ����
@Input��   *data ��������Bufferָ��
		   Len  ��Ҫȡ�����ݳ���
@Output��  Len ��Ϊ�������ʵ�ʻ�õ����ݳ���
@Warning:  ����ִ��״̬ ERR_NONE �� ERR_GENERAL  
@note:     ����2019-4-10
****************************************************************************************
 **/

uint8_t UART2_FIFOReceive(uint8_t *data,uint16_t *Len)
{
	uint32_t FifoDataLen;
	FifoDataLen = fifo_data_length(&USART2_FIFO.rxFifo);
	//FIFO����û����
	if(FifoDataLen == 0)
	{
		return ERR_GENERAL;
	}
	//��FIFO�ж�ȡ����
	*Len = fifo_out(&USART2_FIFO.rxFifo, data, *Len);
	
	return ERR_NONE;
}

 /**
****************************************************************************************
@brief:    UART3_FIFOReceive ��ȡ����
@Input��   *data ��������Bufferָ��
		   Len  ��Ҫȡ�����ݳ���
@Output��  Len ��Ϊ�������ʵ�ʻ�õ����ݳ���
@Warning:  ����ִ��״̬ ERR_NONE �� ERR_GENERAL  
@note:     ����2019-4-10
****************************************************************************************
 **/

uint8_t UART3_FIFOReceive(uint8_t *data,uint16_t *Len)
{
	uint32_t FifoDataLen;
	FifoDataLen = fifo_data_length(&USART3_FIFO.rxFifo);
	//FIFO����û����
	if(FifoDataLen == 0)
	{
		return ERR_GENERAL;
	}
	//��FIFO�ж�ȡ����
	*Len = fifo_out(&USART3_FIFO.rxFifo, data, *Len);
	
	return ERR_NONE;
}



 /**
****************************************************************************************
@brief:    UART2_TransmitInFIFO �����������
@Input��   *data ��������Bufferָ��
		   Len  ��Ҫȡ�����ݳ���
@Output��  NULL
@Warning:  NULL
@note:     ����2019-4-10
****************************************************************************************
 **/

void UART2_TransmitInFIFO(uint8_t *data,uint16_t Len)
{
	//�����������
	fifo_in(&USART2_FIFO.txFifo, data, Len);
}


 /**
****************************************************************************************
@brief:    UART3_FIFOTransmit �����������
@Input��   *data ��������Bufferָ��
		   Len  ��Ҫȡ�����ݳ���
@Output��  NULL
@Warning:  NULL
@note:     ����2019-4-10
****************************************************************************************
 **/

void UART3_TransmitInFIFO(uint8_t *data,uint16_t Len)
{
	//�����������
	fifo_in(&USART3_FIFO.txFifo, data, Len);	
}

 /**
****************************************************************************************
@brief:    UART2_Transmit ��������
@Input��   NULL
@Output��  NULL
@return:   NULL
@Warning:  NULL
@note:     ����2019-4-10
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
	while(((USART2->SR&0X40)==0)&&(timeout<0XFFF))//������ɱ�־�������һ��Ҫ����ǰ�����ᵼ�¸�λ֮���һ���ֽڷ��Ͳ��ɹ�
	{
		timeout++;
	}
	for(i=0;i<len;i++)
	{		
		fifo_try(&USART2_FIFO.txFifo,&Data,1);
		USART2->DR = (uint8_t)(Data & (uint8_t)0x00FF);
		timeout = 0;
		while(((USART2->SR&0X40)==0)&&(timeout<0XFFF))//������ɱ�־�������һ��Ҫ����ǰ�����ᵼ�¸�λ֮���һ���ֽڷ��Ͳ��ɹ�
		{
			timeout++;
		}
		if(timeout>=0XFFF )	//��ʱû���ͳɹ����˳�
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
@brief:    UART3_Transmit ��������
@Input��   NULL
@Output��  NULL
@return:   NULL
@Warning:  NULL
@note:     ����2019-4-10
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
		while(((USART3->SR&0X40)==0)&&(timeout<0XFFF))//������ɱ�־�������һ��Ҫ����ǰ�����ᵼ�¸�λ֮���һ���ֽڷ��Ͳ��ɹ�
		{
			timeout++;
		}
		if(timeout>=0XFFF )	//��ʱû���ͳɹ����˳�
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



