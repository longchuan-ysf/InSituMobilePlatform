/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastUartCan.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�������Դ���ͨ�Žӿ�UART(RS232��RS485)��CAN��USB���⴮��ͨ��������; 
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/

/************************************************************************************/
// ����˵��
/************************************************************************************/
/*
1. UART1~UART6(RS232��RS485)ͨ�Ų���˵��: 
    (1). IO����˵��: ��IO�����ļ�������TX,RX��DIR(RS485�������)�ܽ�, ��UART1Ϊ�� IO����: 
         // UART1(�ܽ�)������ӳ������
         #define UART1_REMAP      UART_REMAP_1    // UART1��ӳ��1, ֻ��STM32F107VC/103VE/103ZE�д�����
         #define UART1_TX         PB6             // ����TX�ܽ�
         #define UART1_RX         PB7             // ����RX�ܽ� 
         #define UART1_DIR        IO_NONE         // ����RS485�������IO, û��תRS485�ӿ�������ΪIO_NONE
         #define UART1_DIR_HL     0               // ����RS485ͨ��ʱ��������ʱ�����ƽ, 0: �͵�ƽ����; 1: �ߵ�ƽ����
       
         Ĭ���Ѿ����ú�, �����޸�;
     
    (2). ���ܲ�������˵��: �������ļ�������������, ��UART1Ϊ��:      
         #define UART1_EN          1       // UART1ʹ��, 1����ʹ�ܣ� 0���ر�
         #define UART1_BAUD        115200  // ���岨���ʣ��������ã�1200��2400��4800��9600��19200��38400��57600��115200
         #define UART1_WORD_LENGTH 0       // ���������ֳ�,   0: 8bit;   1: 9bit;
         #define UART1_STOP_BITS   0       // ����ֹͣλ,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
         #define UART1_PARITY      0       // ������ż����λ, 0: ��У��; 1: żУ��;  2: ��У��;

         #define UART1_RXBUF_SIZE  256     // ������ջ��泤��, ��Χ����0, �����Լ�ʵ����Ҫ����, ������̫��; 
         #define UART1_TXBUF_SIZE  256     // ���巢�ͻ��泤��, ��Χ����0, �����Լ�ʵ����Ҫ����, ������̫��; 

    (3). ��������(1)(2)����, ��APP_Init.c�е���Uart_APPInit()������ʼ��; 
    
    (4). ���Ĳ��Գ���ʵ�ֹ���: �����ⲿ(�����)���������ݣ���������ԭ�����ͳ�ȥ;
         ʵ�ַ���: ���20ms����len = Uart_Ctrl(UART1_ID, CMD_UART_GetCharsRxBuf,0), ��ȡ�����н������ݳ���,
         �ٽ���if ((len == rUart1Len)&&(len>0))�ж�: ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��;  
         ����Uart_Read(UART1_ID, UserVars.buf, len) �����ݶ�ȡ��UserVars.buf��; 
         ����Uart_Write(UART1_ID, UserVars.buf, len) ��UserVars.buf������ԭ�����ͻ�ȥ;
         
         �����̽������ݷ���: ֻ�ʺϽ��ռ��һ��ʱ��(����50ms���)�����ݶ�; �������ʱ�����ֶ�����, ��������������н�������ƴ�Ӽ����ݽ���; 
    
    (5). ͨ�����ڵ�������۲���շ������ݽ��; ���ô��ڵ������ֽ����շ����ݲ���;
    
2. CAN1~CAN2ͨ�Ų���˵��: 
    (1). IO����˵��: ��IO�����ļ�������TX, RX�ܽ�, ��CAN1Ϊ�� IO����: 
         // CAN1(�ܽ�)������ӳ������
         #define CAN1_TX         PD1            // CAN1����TX�ܽ�
         #define CAN1_RX         PD0            // CAN1����RX�ܽ� 
       
         Ĭ���Ѿ����ú�, �����޸�;
     
    (2). ���ܲ�������˵��: �������ļ�������������, ��CAN1Ϊ��:  
        #define CAN1_EN          1		        // CAN1ʹ��, 1����ʹ�ܣ� 0���ر�

        #define CAN1_MODE		 0		        // 0,����ģʽ; 1, ����ģʽ(���ڵ���); 2, ��Ĭģʽ(���ڵ���); 3, ����/��Ĭģʽ(���ڵ���);
        #define CAN1_IDE         CAN_EXT_ID     // ֡����: ��׼֡:CAN_STD_ID, ��չ֡:CAN_EXT_ID
        #define CAN1_RTR         CAN_RTR_DATA   // ѡ������֡:CAN_RTR_DATA ��Զ��֡:CAN_RTR_REMOTE
        #define CAN1_BAUD	     50000          // CAN1������; 
        
        #define CAN1_RXBUF_SIZE   16            // CAN���ջ���ɽ�����Ϣ����,��Χ 1~256
        #define CAN1_TXBUF_SIZE   16            // CAN���ͻ���ɷ�����Ϣ����,��Χ 1~256

    (3). ��������(1)(2)����, ��APP_Init.c�е���CAN_APPInit()������ʼ��; 
    
    (4). ���Ĳ��Գ���ʵ�ֹ���: Ӳ����·��A��CAN�ӿ����ӵ�·��B��CAN�ӿ�
         ��������ѡ���·��A: ѡ��#define  CAN_TEST_A, A���ַID1-ID4��������0-7��B��, �����B�巢����������, ��ȡ����ӡ���; 
         ��������ѡ���·��B: ѡ��#define  CAN_TEST_B, B�����A�巢��������,��������ԭ�����͸�A��;
    
    (5). ��·��A���ͽ�����������˵��: 
         ÿ��3���ʼ����������CanTx, ������CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID)����4�����ݸ���·��B
         ����n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0), ��ȡCAN����, �ж��Ƿ���յ���·��B���ص�����
         ���n>0, ��ʾ���յ�����, ����CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID)��ȡ����, ͨ�����Դ��ڴ�ӡ������;
         
    (6). ��·��B���շ�����������˵��: 
         ÿ��3���ʼ����������CanTx, ������CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID)����4�����ݸ���·��B
         ����n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0), ��ȡCAN����, �ж��Ƿ���յ���·��A����������
         ���n>0, ��ʾ���յ�����, ����CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID)��ȡ����, ������
         CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanRx.ID), ���������ݷ��͸���·��A;
         ͨ�����Դ��ڴ�ӡ������;         

3. USB�豸ģʽ��, ���⴮�ڲ���:
   (1). ���ܲ�������˵��: USB_DEVICE_EN����Ϊ1(ע: USB_HOST_EN��������Ϊ1), USB_VCP_EN����Ϊ1, ע��USB_MSC_ENҪ����Ϊ0;
   
   (2). ��������(1)����, ��APP_Init.c�е���USBD_APPInit()������ʼ��;
   
   (3). ���Ĳ��Գ���ʵ�ֹ���: �����ⲿ(�����, USB���⴮��)���������ݣ���������ԭ�����ͳ�ȥ;
        ʵ�ַ���: ��USB�����ӵ�·��USB�豸�ӿ�, ��һ�ӿڲ��ڼ������, �������ǰҪ��װSTM32�����⴮������;
        �ȵ���USBD_Ctrl(0, CMD_USBD_SYNC, 0), ����USB����ͬ��, ���ݷ���״̬, �ж����⴮����������;
        ���20ms����len = USBD_Ctrl(0, CMD_USBD_GetCharsRxBuf,0), ��ȡUSB���⴮�ڻ����н������ݳ���,
        �ٽ���if ((len == rUSBLen)&&(len>0))�ж�: ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��;  
        ����USBD_Read(0, UserVars.buf, len) �����ݶ�ȡ��UserVars.buf��; 
        ����USBD_Write(0, UserVars.buf, len) ��UserVars.buf������ԭ�����ͻ�ȥ;
         
        �����̽������ݷ���: ֻ�ʺϽ��ռ��һ��ʱ��(����50ms���)�����ݶ�; �������ʱ�����ֶ�����, ��������������н�������ƴ�Ӽ����ݽ���; 

   (4). ͨ�����USB�߿��Թ۲������ϻ�����µĴ���, ���ô��ڵ������ֽ����շ����ݲ���;
*/

/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"
#if (TASK_UARTCAN_EN == 1)
#include "STM32Fxxx.h"
#include "UserVars.h"
#include "AT.h"
#include "vars.h"

/************************************************************************************/
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
//#define  CAN_TEST_A      // ���������·��A(A��)���򣺵�·��A�������ݵ���·��B, �����յ�·��B���ص�����
#define  CAN_TEST_B    // ���������·��B(B��)����: ��·��B���յ�·��A����������,��������ԭ�����͸���·��A

/***********************************************************************************
* Function: App_TaskUart;
*
* Description: ��ȡ����K1-K4��ֵ;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: ���ؼ�ֵ��KNONE��K1VAL-K4VAL;
*
* Note:   none;
************************************************************************************/
void  App_TaskUartCan(void *p_arg)
{
    INT16U  rUart1Len,rUart2Len,rUart3Len,rUart4Len,rUart5Len,rUart6Len;  // UART1/2/3/4/5/6�������ݳ���
	INT16U  rUSBLen;    // USB�������ݳ���
	INT16U  len, i, n, t3s;
    INT32S  flag;
    #if (CAN1_EN > 0)
   	CAN_TX_MSG CanTx; // CAN��������
	CAN_RX_MSG CanRx; // CAN��������
    #endif
    
	(void)p_arg;

    rUSBLen = 0;
	rUart1Len = 0;
	rUart2Len = 0;
	rUart3Len = 0;
	rUart4Len = 0;
	rUart5Len = 0;
	rUart6Len = 0;    
    t3s = 0;
    
    while (1) 
	{  
	     UserVars.TaskRunStatus |= TASK_UARTCAN_FLAG;         // ���ñ���������״̬��־
        
		 Delay_ms(20);	                                      // ��ʱ20ms         
         #if (DEBUG_ISRHOOK_EN > 0)  
         if(DebugInfo.len > 0)
         {    
             Uart_Write(DEBUG_UART, DebugInfo.buf, DebugInfo.len);
             DebugInfo.len = 0;
         }
         #endif
/*******************************************************************************************************/
// UART1���շ��ʹ���
/*******************************************************************************************************/
#if (UART1_EN > 0)
         len = Uart_Ctrl(UART1_ID, CMD_UART_GetCharsRxBuf,0); // ��ȡ�������ݳ���
		 if ((len == rUart1Len)&&(len>0))                     // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                           // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART1_ID, UserVars.buf, len);         // �����ݶ�ȡ��UserVars.buf��
			  #if (AT_EN > 0)
              AT_Proc(UserVars.buf, len);                     // ATָ�����
              #else
              Uart_Write(UART1_ID, UserVars.buf, len);        // ��UserVars.buf������ԭ�����ͻ�ȥ
              #endif
              
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;
              if (UserVars.Para.ATFlag&AT_UART_FLAG)        // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART1=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
	          
              rUart1Len -= len;                               // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart1Len	= len;                                // ��ֵ���½��ջ������ݳ���
		 }
#endif

/*******************************************************************************************************/
// UART2���շ��ʹ���
/*******************************************************************************************************/
#if (UART2_EN > 0)
		 len = Uart_Ctrl(UART2_ID, CMD_UART_GetCharsRxBuf,0);// ��ȡ�������ݳ���
		 if ((len == rUart2Len)&&(len>0))                    // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                          // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART2_ID, UserVars.buf, len);       // �����ݶ�ȡ��UserVars.buf��			
              Uart_Write(UART2_ID, UserVars.buf, len);      // ��UserVars.buf������ԭ�����ͻ�ȥ   
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;
              if (UserVars.Para.ATFlag&AT_UART_FLAG)        // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART2=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
              rUart2Len -= len;                             // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart2Len	= len;                              // ��ֵ���½��ջ������ݳ���
		 }
#endif
        
 /*******************************************************************************************************/
// UART3���շ��ʹ���
/*******************************************************************************************************/        
#if (UART3_EN > 0)
         #if (MODBUS_EN == 0)  // �ж��Ƿ�Modbus����ģʽռ��
		 len = Uart_Ctrl(UART3_ID, CMD_UART_GetCharsRxBuf,0);   // ��ȡ�������ݳ���
		 if ((len == rUart3Len)&&(len>0))                       // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                             // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART3_ID, UserVars.buf, len);           // �����ݶ�ȡ��UserVars.buf��
			  Uart_Write(UART3_ID, UserVars.buf, len);          // ��UserVars.buf������ԭ�����ͻ�ȥ
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART3=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
                 
	          rUart3Len -= len;                                 // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart3Len	= len;                                  // ��ֵ���½��ջ������ݳ���
		 }
         #endif
#endif
         
/*******************************************************************************************************/
// UART4���շ��ʹ���
/*******************************************************************************************************/		 
#if (UART4_EN > 0)
         #if (MODBUS_SLAVE_EN == 0)  // �ж��Ƿ�Modbus�ӻ�ģʽռ��
		 len = Uart_Ctrl(UART4_ID, CMD_UART_GetCharsRxBuf,0);   // ��ȡ�������ݳ���
		 if ((len == rUart4Len)&&(len>0))                       // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                             // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART4_ID, UserVars.buf, len);           // �����ݶ�ȡ��UserVars.buf��
			  Uart_Write(UART4_ID, UserVars.buf, len);          // ��UserVars.buf������ԭ�����ͻ�ȥ
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART4=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
	          rUart4Len -= len;                                 // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart4Len	= len;                                  // ��ֵ���½��ջ������ݳ���
		 }
         #endif
#endif
         
/*******************************************************************************************************/
// UART5���շ��ʹ���
/*******************************************************************************************************/	
#if (UART5_EN > 0)
		 len = Uart_Ctrl(UART5_ID, CMD_UART_GetCharsRxBuf,0);   // ��ȡ�������ݳ���
		 if ((len == rUart5Len)&&(len>0))                       // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                             // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART5_ID, UserVars.buf, len);           // �����ݶ�ȡ��UserVars.buf��
			  Uart_Write(UART5_ID, UserVars.buf, len);          // ��UserVars.buf������ԭ�����ͻ�ȥ
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART5=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
	          rUart5Len -= len;                                 // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart5Len	= len;                                  // ��ֵ���½��ջ������ݳ���
		 }
#endif

/*******************************************************************************************************/
// UART6���շ��ʹ���
/*******************************************************************************************************/	
#if (UART6_EN > 0)
#if (MODULE_CLASS == STM32F407XX)
		 len = Uart_Ctrl(UART6_ID, CMD_UART_GetCharsRxBuf,0);   // ��ȡ�������ݳ���
		 if ((len == rUart6Len)&&(len>0))                       // ���20ms��ȡ, ���2�ζ�ȡ�������ݳ��ȴ���0, �������,˵���������Ѿ��յ�����һ�����ݣ����Զ�ȡ��  
		 {
			  if (len>DATABUF_SIZE)                             // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART6_ID, UserVars.buf, len);           // �����ݶ�ȡ��UserVars.buf��
			  Uart_Write(UART6_ID, UserVars.buf, len);          // ��UserVars.buf������ԭ�����ͻ�ȥ
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
              {
                  printf("AT+UART6=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);            
              }
              #endif
              
	          rUart6Len -= len;                                 // �������½��ջ������ݳ���
		 }
		 else
		 {
			  rUart6Len	= len;                                  // ��ֵ���½��ջ������ݳ���
		 }
#endif
#endif
         
/*******************************************************************************************/      
// CAN1ͨ�Ų��Գ���
/*******************************************************************************************/      
#if (CAN1_EN > 0)        
#ifdef CAN_TEST_A      // ��������A�����A�巢�����ݵ�B��, ������B�巵�ص�����, �Ա��Ƿ���ȷ
        t3s++;
        // ��ʼ���������ݣ�8���ֽڣ����ݣ�0-7
        if ((t3s%150) == 0)  // �ж�ÿ��3��
        {
            CanTx.ID = 1;                 
            CanTx.IDE = CAN_EXT_ID;     
            CanTx.RTR = CAN_RTR_DATA;      
            CanTx.DLC = 8;                 
            CanTx.Data[0] = 0;             
            CanTx.Data[1] = 1;
            CanTx.Data[2] = 2;
            CanTx.Data[3] = 3;
            CanTx.Data[4] = 4;
            CanTx.Data[5] = 5;
            CanTx.Data[6] = 6;
            CanTx.Data[7] = 7;
            
            for (i=0; i<4; i++)  // ����4������: id�ֱ���1-4, ����0-7
            {
                CanTx.ID = i+1;  // ����id: 1-4
                CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID); // ����һ�����ݸ�B��
                #if (DEBUG_APP_EN > 0)
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN1=WH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanTx.Data[1], CanTx.Data[2],\
                       CanTx.Data[3], CanTx.Data[4], CanTx.Data[5], CanTx.Data[6], CanTx.Data[7]);    
                }
                #endif
            }
        }
        if ((t3s%5) == 0)  // �ж�ÿ��100ms
        {    
            n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0);  // ��ȡCAN���棬�Ƿ�������
            if (n>0)  // �ж��Ƿ���յ�����
            {
                for (i=0; i<n; i++)  // ��ȡ���յ���B�巢����n������
                {
                    CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID);
                    #if (DEBUG_APP_EN > 0)
                    if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                    {
                        printf("AT+CAN1=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                            CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]); 
                    }
                    #endif
                }
            }
        }
#endif   
/*******************************************************************************************/         
#ifdef  CAN_TEST_B    // ��������B�����: B�����A�巢��������,��������ԭ�����͸�A��         
		n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0);  // ��ȡCAN���棬�Ƿ�������
		if (n>0)   // �ж��Ƿ���յ�����
		{
            for (i=0; i<n; i++)         
			{
				CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID);  // ��ȡA�巢����һ���������
				#if (DEBUG_APP_EN == 1)			
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN1=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                       CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]);                                                 
                }
                #endif
                CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanRx.ID); // �����յ����ݷ��͸�A��
			}
		}            
#endif   
#endif   
        
/*******************************************************************************************/      
// CAN2ͨ�Ų��Գ���
/*******************************************************************************************/     
#if (CAN2_EN > 0)        
#ifdef CAN_TEST_A      // ��������A�����A�巢�����ݵ�B��, ������B�巵�ص�����, �Ա��Ƿ���ȷ
        //t3s++;
        // ��ʼ���������ݣ�8���ֽڣ����ݣ�0-7
        if ((t3s%150) == 0)  // �ж�ÿ��3��
        {
            CanTx.ID = 1;                 
            CanTx.IDE = CAN_EXT_ID;     
            CanTx.RTR = CAN_RTR_DATA;      
            CanTx.DLC = 8;                 
            CanTx.Data[0] = 0;             
            CanTx.Data[1] = 1;
            CanTx.Data[2] = 2;
            CanTx.Data[3] = 3;
            CanTx.Data[4] = 4;
            CanTx.Data[5] = 5;
            CanTx.Data[6] = 6;
            CanTx.Data[7] = 7;
            
            for (i=0; i<4; i++)  // ����4������: id�ֱ���1-4, ����0-7
            {
                CanTx.ID = i+1;  // ����id: 1-4
                CAN_Write(CAN2_ID, (CAN_TX_MSG *)&CanTx.ID); // ����һ�����ݸ�B��
                #if (DEBUG_APP_EN > 0)
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN2=WH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanTx.Data[1], CanTx.Data[2],\
                       CanTx.Data[3], CanTx.Data[4], CanTx.Data[5], CanTx.Data[6], CanTx.Data[7]);    
                }
                #endif
            }
        }
        if ((t3s%5) == 0)  // �ж�ÿ��100ms
        {    
            n = CAN_Ctrl(CAN2_ID, CMD_CAN_GetMsgRxBuf, 0);  // ��ȡCAN���棬�Ƿ�������
            if (n>0)  // �ж��Ƿ���յ�����
            {
                for (i=0; i<n; i++)  // ��ȡ���յ���B�巢����n������
                {
                    CAN_Read(CAN2_ID, (CAN_RX_MSG *)&CanRx.ID);
                    #if (DEBUG_APP_EN > 0)
                    if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                    {
                        printf("AT+CAN2=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                            CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]); 
                    }
                    #endif
                }
            }
        }
#endif   
/*******************************************************************************************/         
#ifdef  CAN_TEST_B    // ��������B�����: B�����A�巢��������,��������ԭ�����͸�A��         
		n = CAN_Ctrl(CAN2_ID, CMD_CAN_GetMsgRxBuf, 0);  // ��ȡCAN���棬�Ƿ�������
		if (n>0)   // �ж��Ƿ���յ�����
		{
            for (i=0; i<n; i++)         
			{
				CAN_Read(CAN2_ID, (CAN_RX_MSG *)&CanRx.ID);  // ��ȡA�巢����һ���������
				#if (DEBUG_APP_EN == 1)
				if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN2=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                       CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]); 
                }
                #endif
                CAN_Write(CAN2_ID, (CAN_TX_MSG *)&CanRx.ID); // �����յ����ݷ��͸�A��
			}
		}            
#endif   
#endif   
/*******************************************************************************************************/      
// USB���⴮�ڽ��շ������ݽ��շ��ʹ���
/*******************************************************************************************************/        
        #if ((USB_DEVICE_EN > 0)&&(USB_VCP_EN > 0))  // USB�豸����ʹ��, ���������⴮��ģʽ           
        flag = USBD_Ctrl(USB_ID, CMD_USBD_SYNC, 0);	                     // USB�豸ͬ������,����USB�豸״̬
        if (flag&USBD_WORK_OK)  // �ж����⴮����������
        {
            len = USBD_Ctrl(USB_ID, CMD_USBD_GetCharsRxBuf,0);    // ��ȡ�������ݳ���
            if ((len == rUSBLen)&&(len>0))
            {
                if (len>DATABUF_SIZE)                     // ����������ݳ��ȴ���DATABUF_SIZE(UserVars.buf)����, ��ֵlen = DATABUF_SIZE;
                {
                    len = DATABUF_SIZE;
                }
                USBD_Read(USB_ID, UserVars.buf, len);
                USBD_Write(USB_ID, UserVars.buf, len);

                #if (DEBUG_APP_EN == 1)
                UserVars.buf[len] = 0;                            
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("\r\nAT+USB=VCP���շ�������[%d]:%s\r\n", len, UserVars.buf); // ��ӡ������������Դ���(ע��:ֻ����ʾASCII�ַ�)
                }
                #endif

                rUSBLen -= len;
            }
            else
            {
                rUSBLen	= len;
            }
        }
        #endif
	}
}

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

