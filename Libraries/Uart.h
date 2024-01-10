/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: uart.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.4.1	
* Modify:  ����DMA���ͺͽ���
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���UART����Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S Uart_Init(INT8U id, UART_PARA *pPara);
*          2. INT32S Uart_Read(INT8U id, INT8U *p, INT16U len);
*          3. INT32S Uart_Write(INT8U id, INT8U *p, INT16U len);
*          4. INT32S Uart_RecvChar(INT8U id, INT8U *val);
*          5. INT32S Uart_SendChar(INT8U id, INT8U val);
*          6. INT32S Uart_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __UART_H 
#define __UART_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h" 
/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// UART��������
#define UART1_ID	0 
#define UART2_ID	1 
#define UART3_ID	2 
#define UART4_ID	3 
#define UART5_ID	4 

#define UART6_ID	5  // ֻ��STM32F407VEģ��֧��

// ����ģʽ����  
#define UART_AsynFD 	0    // ȫ˫���ģ��첽ͨ��
#define UART_SyncFD	    1	 // ȫ˫���ģ�ͬ��ͨ��, �ݲ�֧��
#define UART_LIN 		2	 // LINͨ��, �ݲ�֧��
#define UART_IrDA		3	 // IrDAͨ��, �ݲ�֧��
#define UART_ISO7816	4	 // ���ܿ�ͨ��, �ݲ�֧��
#define UART_SWHALF		5    // ���߰�˫��ͨ��, �ݲ�֧��

// �����ʶ���
#define BaudRate_1200	    1200 
#define BaudRate_2400	    2400
#define BaudRate_4800	    4800
#define BaudRate_9600	    9600
#define BaudRate_19200	    19200
#define BaudRate_38400	    38400
#define BaudRate_57600	    57600
#define BaudRate_115200	    115200
#define BaudRate_230400	    230400
#define BaudRate_460800	    460800
#define BaudRate_921600	    921600 

// �����ֳ����壺0: 8bit;   1: 9bit;
#define UART_WORD_LENGTH_8B      0   // ���������ֳ�8bit
#define UART_WORD_LENGTH_9B      1   // ���������ֳ�9bit

// ֹͣλ����: 0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART_STOP_BITS_1         0   // ����ֹͣλ1bit
#define UART_STOP_BITS_2         1   // ����ֹͣλ2bit
#define UART_STOP_BITS_0_5       2   // ����ֹͣλ0.5bit
#define UART_STOP_BITS_1_5       3   // ����ֹͣλ1.5bit

// ��ż����λλ����: 0: ��У��; 1: żУ��;  2: ��У��;  
#define UART_PARITY_NO           0   // ������ż����λ: ��У��
#define UART_PARITY_EVEN         1   // ������ż����λ: żУ��
#define UART_PARITY_ODD          2   // ������ż����λ: ��У��

// Ӳ�����ض���: 0: ������; 1: RTS����;  2: CTS����; 3: RTS��CTS����;
#define UART_HWFLOW_CTRL_NO        0 // ������
#define UART_HWFLOW_CTRL_RTS       1 // RTS����, ��ʱ��֧��
#define UART_HWFLOW_CTRL_CTS       2 // CTS����, ��ʱ��֧��
#define UART_HWFLOW_CTRL_RTS_CTS   3 // RTS��CTS����, ��ʱ��֧��

// DMAʹ�ܶ���: 0: �ر�DMA; 1:TXʹ��DMA; 2: RXʹ��DMA;
#define UART_DMAREQ_NO             0 // �ر�DMA
#define UART_DMAREQ_TX             1 // TXʹ��DMA
#define UART_DMAREQ_RX             2 // RXʹ��DMA

// UART(�ܽ�)������ӳ�䶨��
#define UART_REMAP_0       0    // UARTû����ӳ��
#define UART_REMAP_1       1    // UART��ӳ��1
#define UART_REMAP_2       2    // UART��ӳ��2
/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F107VC,STM32F103VE,STM32F103ZE UART1-5�ܽ�ӳ���, ��������ӳ�䷽ʽ����
/************************************************************************************************************************/
// UART1-UART5(�ܽ�)������ӳ���
/*
|---------------------------------------|
| ��Ŀ  |  ��ӳ��  |  TX�ܽ�  |  RX�ܽ� |
|---------------------------------------|
|       |   û��   |   PA9    |   PA10  |
| UART1 |-------------------------------|
|       |  ��ӳ��1 |   PB6    |   PB7   |
|---------------------------------------|
|       |   û��   |   PA2    |   PA3   |
| UART2 |-------------------------------|
|       |  ��ӳ��1 |   PD5    |   PD6   |
|---------------------------------------|
|       |   û��   |   PB10   |   PB11  |
|       |-------------------------------|
| UART3 |  ��ӳ��1 |   PC10   |   PC11  |
|       |-------------------------------|
|       |  ��ӳ��2 |   PD8    |   PD9   |
|---------------------------------------|
| UART4 |   û��   |   PC10   |   PC11  |
|---------------------------------------|
| UART5 |   û��   |   PC12   |   PD2   |
|---------------------------------------|
*/

/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F407VE UART1-6�ܽ�ӳ���, �����ùܽŸ��üĴ�������
/************************************************************************************************************************/
// UART1-UART6(�ܽ�)����ӳ���
/*
|---------------------------------------|
| ��Ŀ  | ����ѡ�� |  TX�ܽ�  |  RX�ܽ� |
|---------------------------------------|
|       |          |   PA9    |   PA10  |
| UART1 |   AF7    |--------------------|
|       |          |   PB6    |   PB7   |
|---------------------------------------|
|       |          |   PA2    |   PA3   |
| UART2 |   AF7    |--------------------|
|       |          |   PD5    |   PD6   |
|---------------------------------------|
|       |          |   PB10   |   PB11  |
|       |          |--------------------|
| UART3 |   AF7    |   PC10   |   PC11  |
|       |          |--------------------|
|       |          |   PD8    |   PD9   |
|---------------------------------------|
|       |          |   PA0    |   PA1   |
| UART4 |   AF8    |--------------------|
|       |          |   PC10   |   PC11  |
|---------------------------------------|
| UART5 |   AF8    |   PC12   |   PD2   |
|---------------------------------------|
|       |          |   PC6    |   PC7   |
| UART6 |   AF8    |--------------------|
|       |          |   PG14   |   PG9   |
|---------------------------------------|
*/

// ������־Flag����
#define UART_REMAP1_FLAG       0x00000001  // WKFlag��bit0=1, REMAP1��Ч
#define UART_REMAP2_FLAG       0x00000002  // WKFlag��bit1=1, REMAP2��Ч
#define UART_DATA_7BIT_FLAG    0x00000008  // WKFlag��bit3=1, ʵ����Ч7λ����λ;����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit
                                           // ���ʼ��ʱ���øñ�־
#define UART_WORD_LENGTH_9BIT_FLAG  0x00000010  // WKFlag��bit4=1, ����λ9bit��־;
#define UART_PARITY_EVEN_FLAG  0x00000020  // WKFlag��bit5=1, żУ��
#define UART_PARITY_ODD_FLAG   0x00000040  // WKFlag��bit6=1, ��У��
#define UART_STOP_BITS2_FLAG   0x00000080  // WKFlag��bit7=1,  ֹͣλ2λ;
#define UART_STOP_BITS0_5_FLAG 0x00000100  // WKFlag��bit8=1,  ֹͣλ0.5λ;
#define UART_STOP_BITS1_5_FLAG 0x00000200  // WKFlag��bit9=1,  ֹͣλ1.5λ;
#define UART_DMAREQ_RX_FLAG    0x00000400  // WKFlag��bit10=1, RX����DMAʹ��;
#define UART_DMAREQ_TX_FLAG    0x00000800  // WKFlag��bit11=1, TX����DMAʹ��;
#define UART_HWFC_CTS_FLAG     0x00001000  // WKFlag��bit12=1, CTS����ʹ��;
#define UART_HWFC_RTS_FLAG     0x00002000  // WKFlag��bit13=1, RTS����ʹ��;
#define UART_RS485DIR_FLAG     0x00004000  // UARTתRS485�ӿ�ʱ, WKFlag��bit14=1, ����IO DIR�ߵ�ƽ����; bit14=0, ����IO DIR�͵�ƽ��ƽ����;
#define UART_RS485EN_FLAG      0x00008000  // WKFlag��bit15=1, UARTתRS485�ӿ�, ��ҪDIR�����ź�; bit15=0, UARTתRS232����TTL�ӿڣ�����ҪDIR����;
#define UART_ISRHOOK_FLAG      0x00010000  // WKFlag��bit16=1, �жϵ���Uart1(2/3/4/5/6)_ISRHook()��������;


#define UART_TXBUSY_FLAG        0x80000000  // WKFlag��bit31=1, ���ݷ������ڽ��б�־;

// UART�����ṹ 
typedef struct
{
    INT32U Flag;                 // ����������־
    INT32U BaudRate;             // �����ʣ��μ������ʶ���
    INT8U  Mode;                 // ����ģʽ���ο�����ģʽ����
   
    INT8U  TXPin;                // ��������IO�ܽŶ���     
    INT8U  RXPin;                // ��������IO�ܽŶ���     
    INT8U  RS485DirPin;          // RS485�������IO�ܽŶ��� 
   
    INT8U *pTxBuf;               // �������ݻ���ָ��
    INT16U TxBufLen;             // ���ͻ��泤��
  
    INT8U *pRxBuf;               // �������ݻ���ָ��
    INT16U RxBufLen;             // ���ջ��泤��
}UART_PARA;

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// UART�����
#define CMD_UART_GetCharsRxBuf	0 	 // ��ȡ�������ݻ��������ݳ���
#define CMD_UART_GetCharsTxBuf	1 	 // ��ȡ�������ݻ����п��пռ䳤��
#define CMD_UART_ChangeBaud  	2 	 // �ı䲨����
#define CMD_UART_ClearRxBuffer  3    // ������ջ���������.
#define CMD_UART_ClearTxBuffer  4    // ������ͻ���������.	
#define CMD_UART_ChangeUtcf		5	 // �ı䴮�����ݸ�ʽ
#define CMD_UART_RXCtrl      	6	 // ���ڽ���ʹ�ܿ���
#define CMD_UART_RST            7    // ��λUART�Ĵ���Ϊ��ʼ״̬
#define CMD_UART_CLOSE          8    // �ر�UARTʱ��,Ҳ���ǹر�UART����,����ʡ�� 

/*************************************************************************************/
//
// 						UARTӲ����������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: Uart_Init;
*
* Description: Uart��ʼ������;
*              
* Input:  id, UART������ʶ(UART1_ID~UART6_ID);
*         *pPara, UART��ʼ������ָ��;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ��ʼ����ɣ�UART�Ѿ�ʹ�ܿ�ʼ�������������Uart_Ctrl�ٴ�ʹ��;
*         �������������ʼ����TXD/RXD, ��RS485����DIR�ź�;
************************************************************************************/
INT32S Uart_Init(INT8U id, UART_PARA *pPara);

/***********************************************************************************
* Function: Uart_Read;
*
* Description: ��ȡ���յ�����; ��������ݱ�����,�ú����᷵�ؽ���һ�����ȵ����ݿ�,
*              ���򽫷��ش������,
*           
* Input:  id,  UART������ʶ(UART1_ID~UART6_ID);
*         *p,  �������ݿ�ָ��; 
*         len, �������ݿ鳤��;
*      		  
* Output: *p,  �������ݿ�ָ��; 
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �ú��������ȴ��������ݾͷ���;
************************************************************************************/
INT32S Uart_Read(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Uart_Write;
*
* Description: ����һ�����ݿ鵽���ͻ�����;
*           
* Input:  id,  UART������ʶ(UART1_ID~UART6_ID);
*         *p,  �������ݿ�ָ��; 
*         len, �������ݿ鳤��;
*      		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �ú���ֻ�ǽ����ݷ��ͻ�����,UART�����������������ݣ�����������ʱ������ζ��
*         �����Ѿ�������ɣ�
************************************************************************************/
INT32S Uart_Write(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Uart_RecvChar;
*
* Description: ����һ���ֽ����ݣ���������ݱ�����,�ú����᷵��һ����������,���򽫷��ش������;
*               
* Input:  id,  UART������ʶ(UART1_ID~UART6_ID);
*         *val,�������ݵ�ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �ú��������ȴ��������ݾͷ���;
************************************************************************************/
INT32S Uart_RecvChar(INT8U id, INT8U *val);

/***********************************************************************************
* Function: Uart_SendChar;
*
* Description: ����һ���ֽ����ݵ����ͻ�����;
* 
* Input:  iid,  UART������ʶ(UART1_ID~UART6_ID);
*         val,  ���͵�����;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   1. �ú���ֻ�Ǵ洢���ݵ����ͻ�����,UART�����������������ݣ�����������ʱ������ζ��
*            �����Ѿ��������;
*         2. �ú�����֧��DMA���ݷ���, ������ΪDMA����ģʽ, ����ERR_FALSE;
************************************************************************************/
INT32S Uart_SendChar(INT8U id, INT8U val);

/***********************************************************************************
* Function: Uart_Ctrl;
*
* Description: UART�������;
* 
* Input:  id,   UART������ʶ(UART1_ID~UART6_ID);
*         Cmd,  UART��������: 
*               CMD_UART_GetCharsRxBuf: ��ȡ�������ݻ��������ݳ���
*               CMD_UART_GetCharsTxBuf: ��ȡ�������ݻ����п��пռ䳤��
*               CMD_UART_ChangeBaud:    �ı䲨����
*               CMD_UART_ClearRxBuffer: ������ջ���������.
*               CMD_UART_ClearTxBuffer: ������ͻ���������.
*               CMD_UART_ChangeUtcf:    �ı䴮�����ݸ�ʽ
*               CMD_UART_RXCtrl:	    ���ڽ���ʹ�ܿ���
*               CMD_UART_RST:           ��λUART�Ĵ���Ϊ��ʼ״̬
*               CMD_UART_CLOSE:         �ر�UARTʱ��,Ҳ���ǹر�UART����,����ʡ�� 
*         Para��CMD������Ʋ���;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������; �з������ݵķ�����Ӧ���ݣ�
*
* Note:   none;
************************************************************************************/
INT32S Uart_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

