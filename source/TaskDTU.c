/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastDTU.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ������빤ҵDTUģ��ͨ��������;
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
1. EMB8600I ���Ͽ��Լ�һ��EMB8106G DTUģ����ʵ����������ͨ��, ����J13����ѡ��DTU, ����
   ����Uart3����ͨ��, ע��Ĭ��DTU��ͨ�Ų�������9600bps, ���޸������ļ��е�Uart3�Ĳ�����,
   ���������ļ��е�TASK_DTU_EN����Ϊ1
   
2. �����������4����:
   (1). ʵ�������Ķ�DTU����Ϳ��ƣ���������ͨ�ŵĹ��̼����ߴ���;
   (2). �յ����������������ݣ����õ��Դ��������ʾ�յ�������;
   (3). ��������������ݵ����̣�
   (4). ���ֻ����Ͷ������̡�

3. ���Դ��������ʾͨ��RS232ͨ�ſڣ�TX1��RX1��GND������������

4. DTU���ú�ʹ����鿴DTU�����Ͻ���
*/

/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"
#if (TASK_DTU_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"

/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// ����ͨ������
#define DTU_DATA_EN   1  // 1, ��������ʹ��; 0, ֹͣ��������
#define DTU_DATA_T    10 // �������ݼ��
#define DTU_DATA      "0123456789ABCDEF" // ������������

// ����ͨ������
#define DTU_SMS_EN    1    // 1, ���Ͷ���ʹ��; 0, ֹͣ���Ͷ���
#define DTU_SMS_T     60   // ���Ͷ��ż��
#define DTU_SMS_MODE  '2'  // ���ű���: '0',7BIT����, ���ڷ���ASCII��; '1',8BIT����, ���ڷ���16��������; '2',USC2����, ���ڷ�������; 
#define DTU_SMS_TEL   "18801080298"   // ���Ͷ��ŵ�����绰����, �ͻ��������޸�����绰����

#define DTU_SMS_7BIT  "0123456789ABCDEF" // ���Ͷ�������, 7BITģʽ����
#define DTU_SMS_8BIT  "00105A8FFB"       // ���Ͷ������ݣ�0x00,0x10,0x5A,0x8F,0xFB, 8BITģʽ����
#define DTU_SMS_USC2  "5DE54F5C61095FEBFF01" // ���Ͷ������ݣ�������죡, USC2ģʽ���ͣ���:0x5DE5, ��:0x4F5C, ��:0x6109, ��:0x5FEB, ��:0xFF01

typedef enum
{
	DTU_INIT = 0,
	DTU_PWRON,
	DTU_PWROFF,
	DTU_ONLINE,
	DTU_IDLE,
}DTU_STATUS;

#define MAX_DTUDATA_SIZE   64
INT8U  DTUData[MAX_DTUDATA_SIZE];

/***********************************************************************************
* Function: App_TaskDTU;
*
* Description: �����������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void  App_TaskDTU(void *p_arg)
{
	DTU_STATUS	DTUStatus;
	INT16U Delay_t, Offline_t;
	INT16U  rUartLen = 0;  
	INT16U  len, i;

	(void)p_arg;

	DTUStatus = DTU_INIT;
    while (1) 
	{  
	     UserVars.TaskRunStatus |= TASK_DTU_FLAG;   // ���ñ���������״̬��־
         Delay_ms(100);     // ��ʱ100ms
		 switch (DTUStatus)
		 {
			  case DTU_INIT:
				  DTUStatus = DTU_PWRON;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=��ʼ��\r\n");
			  	  #endif
                  break;
			  case DTU_PWRON:
				  IO_Write(DTU_OFF, 0);	// ����DTU��Դ
				  DTUStatus = DTU_ONLINE;
				  Offline_t = 0;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=�򿪵�Դ,�ȴ�����...\r\n");
			  	  #endif
                  break;
			  case DTU_PWROFF:
			      IO_Write(DTU_OFF, 1);	// �ر�DTU��Դ
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=�رյ�Դ, �ȴ�1����\r\n");
				  #endif
                  Delay_s(60); // ��ʱ60��
                  DTUStatus = DTU_PWRON;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=�ȴ�1�������, ����ģ��\r\n");
                  #endif  
                  break;
			  case DTU_ONLINE:
				  if (IO_Read(DTU_LINK)) // 
				  {
					  DTUStatus = DTU_IDLE;
					  Offline_t = 0;
					  #if (DEBUG_APP_EN == 1)
                      printf("AT+DTU=�������, ��������ͨ��״̬\r\n");
                      #endif
				  }
				  else
				  {
					  Offline_t++;
					  if (Offline_t>6000)  //����ʮ����δ���ߣ���ر�DTU��Դ
					  {
						   DTUStatus = DTU_PWROFF;
						   #if (DEBUG_APP_EN == 1)
                           printf("AT+DTU=����10����δ����\r\n");
                           #endif
					  }
				  }
			  	  break;

			  case DTU_IDLE:
				  if (IO_Read(DTU_LINK))
				  {                    
                     // ���շ��������ݴ���
                     len = Uart_Ctrl(UART3_ID, CMD_UART_GetCharsRxBuf,0);// ��ȡ�������ݳ���
					 if ((len == rUartLen)&&(len>0))
					 {
						  if (len>MAX_DTUDATA_SIZE)
						  {
						      len = MAX_DTUDATA_SIZE;
						  }
						  Uart_Read(UART3_ID, DTUData, len);   // ���շ���������������
					      rUartLen -= len;
						  #if (DEBUG_APP_EN == 1)
                          printf("AT+DTU=�յ�����������[%d]:", len);
		                  for (i=0; i<len; i++)
		                  {
			                   printf("%02X ", DTUData[i]);
		                  }
		                  printf("\r\n");
                          #endif
					 }
					 else
					 {
						  rUartLen	= len;
					 }
                     
					 if (Offline_t>=1)
					 {
						  #if (DEBUG_APP_EN == 1)
                          printf("AT+DTU=��������\r\n");
                          #endif
                          Offline_t = 0;
					 }	
                     
					 Delay_t++; // ��ʱ������1                     
                     #if (DTU_DATA_EN == 1)  // ����ͨ�Ų���ʹ��
                     if ((Delay_t%((INT16U)10*DTU_DATA_T))==0) // ���DTU_DATA_Tʱ�䷢������
                     {
                         Uart_Write(UART3_ID, DTU_DATA, strlen(DTU_DATA));  // ���������������
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=���������������:%s\r\n", DTU_DATA);
                         #endif
                     }
                     #endif        

                     #if (DTU_SMS_EN == 1)  // ����ͨ�Ų���ʹ��
                     if ((Delay_t%((INT16U)10*DTU_SMS_T))==0) // ���DTU_SMS_Tʱ�䷢�Ͷ���
                     {
                         #if(DTU_SMS_MODE == '0')  // ���ű���: '0',7BIT����, ���ڷ���ASCII��;
                         len = sprintf(DTUData,"AT+SMS=%s,0,%s\r\n",DTU_SMS_TEL, DTU_SMS_7BIT);  // �����Ͷ��ŵ�ATָ��д��DTUData������
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=���ֻ�%s���Ͷ���:%s\r\n", DTU_SMS_TEL, DTU_SMS_7BIT);
                         #endif
                         #elif (DTU_SMS_MODE == '1')  // ���ű���: '1',8BIT����, ���ڷ���16��������;
                         len = sprintf(DTUData,"AT+SMS=%s,1,%s\r\n",DTU_SMS_TEL,DTU_SMS_8BIT);  // �����Ͷ��ŵ�ATָ��д��DTUData������
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=���ֻ�%s���Ͷ���:%s\r\n", DTU_SMS_TEL, DTU_SMS_8BIT);
                         #endif
                         #else                        // ���ű���: '2',USC2����, ���ڷ�������; 
                         len = sprintf(DTUData,"AT+SMS=%s,2,%s\r\n",DTU_SMS_TEL,DTU_SMS_USC2);  // �����Ͷ��ŵ�ATָ��д��DTUData������
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=���ֻ�%s���Ͷ���:%s\r\n", DTU_SMS_TEL, DTU_SMS_USC2);
                         #endif
                         #endif                         
                         Uart_Write(UART3_ID, DTUData, len);  // ���ֻ����Ͷ���
                         
                     }
                     #endif 
				  }
				  else
				  {
				  	  Offline_t++;        // ����ʱ���1
					  if (Offline_t==1)
					  {
                           #if (DEBUG_APP_EN == 1)
						   printf("AT+DTU=����\r\n");
                           #endif
					  }

					  if (Offline_t>6000)  // ���ߴ���ʮ���ӣ���ر�DTU��Դ
					  {
						   DTUStatus = DTU_PWROFF;
						   #if (DEBUG_APP_EN == 1)
                           printf("AT+DTU=���߳���10����\r\n");
                           #endif
					  }
				  }
			  	  break;
			  default:

			  	  break;
		 }
	}
}
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

