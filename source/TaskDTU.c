/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastDTU.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责与工业DTU模块通信任务处理;
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
// 测试说明
/************************************************************************************/
/*
1. EMB8600I 板上可以加一块EMB8106G DTU模块来实现无线数据通信, 板上J13跳线选择DTU, 利用
   板上Uart3进行通信, 注意默认DTU的通信波特率是9600bps, 请修改配置文件中的Uart3的波特率,
   并将配置文件中的TASK_DTU_EN设置为1
   
2. 测试例程完成4件事:
   (1). 实现完整的对DTU管理和控制，包括开启通信的过程及断线处理;
   (2). 收到服务器发来的数据，利用调试串口输出显示收到的数据;
   (3). 向服务器发送数据的例程；
   (4). 向手机发送短信例程。

3. 调试串口输出显示通过RS232通信口：TX1、RX1、GND，输出到计算机

4. DTU配置和使用请查看DTU的资料进行
*/

/************************************************************************************/
// 引用外部头文件
#include "config.h"
#if (TASK_DTU_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"

/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 数据通信设置
#define DTU_DATA_EN   1  // 1, 发送数据使能; 0, 停止发送数据
#define DTU_DATA_T    10 // 发送数据间隔
#define DTU_DATA      "0123456789ABCDEF" // 发送数据内容

// 短信通信设置
#define DTU_SMS_EN    1    // 1, 发送短信使能; 0, 停止发送短信
#define DTU_SMS_T     60   // 发送短信间隔
#define DTU_SMS_MODE  '2'  // 短信编码: '0',7BIT编码, 用于发送ASCII码; '1',8BIT编码, 用于发送16进制数据; '2',USC2编码, 用于发送中文; 
#define DTU_SMS_TEL   "18801080298"   // 发送短信到这个电话号码, 客户测试请修改这个电话号码

#define DTU_SMS_7BIT  "0123456789ABCDEF" // 发送短信内容, 7BIT模式发送
#define DTU_SMS_8BIT  "00105A8FFB"       // 发送短信内容：0x00,0x10,0x5A,0x8F,0xFB, 8BIT模式发送
#define DTU_SMS_USC2  "5DE54F5C61095FEBFF01" // 发送短信内容：工作愉快！, USC2模式发送；工:0x5DE5, 作:0x4F5C, 愉:0x6109, 快:0x5FEB, ！:0xFF01

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
* Description: 命令处理主函数;
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
	     UserVars.TaskRunStatus |= TASK_DTU_FLAG;   // 设置本任务运行状态标志
         Delay_ms(100);     // 延时100ms
		 switch (DTUStatus)
		 {
			  case DTU_INIT:
				  DTUStatus = DTU_PWRON;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=初始化\r\n");
			  	  #endif
                  break;
			  case DTU_PWRON:
				  IO_Write(DTU_OFF, 0);	// 开启DTU电源
				  DTUStatus = DTU_ONLINE;
				  Offline_t = 0;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=打开电源,等待上线...\r\n");
			  	  #endif
                  break;
			  case DTU_PWROFF:
			      IO_Write(DTU_OFF, 1);	// 关闭DTU电源
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=关闭电源, 等待1分钟\r\n");
				  #endif
                  Delay_s(60); // 延时60秒
                  DTUStatus = DTU_PWRON;
				  #if (DEBUG_APP_EN == 1)
                  printf("AT+DTU=等待1分钟完成, 重启模块\r\n");
                  #endif  
                  break;
			  case DTU_ONLINE:
				  if (IO_Read(DTU_LINK)) // 
				  {
					  DTUStatus = DTU_IDLE;
					  Offline_t = 0;
					  #if (DEBUG_APP_EN == 1)
                      printf("AT+DTU=上线完成, 进入正常通信状态\r\n");
                      #endif
				  }
				  else
				  {
					  Offline_t++;
					  if (Offline_t>6000)  //大于十分钟未上线，则关闭DTU电源
					  {
						   DTUStatus = DTU_PWROFF;
						   #if (DEBUG_APP_EN == 1)
                           printf("AT+DTU=超过10分钟未上线\r\n");
                           #endif
					  }
				  }
			  	  break;

			  case DTU_IDLE:
				  if (IO_Read(DTU_LINK))
				  {                    
                     // 接收服务器数据处理
                     len = Uart_Ctrl(UART3_ID, CMD_UART_GetCharsRxBuf,0);// 读取接收数据长度
					 if ((len == rUartLen)&&(len>0))
					 {
						  if (len>MAX_DTUDATA_SIZE)
						  {
						      len = MAX_DTUDATA_SIZE;
						  }
						  Uart_Read(UART3_ID, DTUData, len);   // 接收服务器发来的数据
					      rUartLen -= len;
						  #if (DEBUG_APP_EN == 1)
                          printf("AT+DTU=收到服务器数据[%d]:", len);
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
                          printf("AT+DTU=重新上线\r\n");
                          #endif
                          Offline_t = 0;
					 }	
                     
					 Delay_t++; // 延时计数加1                     
                     #if (DTU_DATA_EN == 1)  // 数据通信测试使能
                     if ((Delay_t%((INT16U)10*DTU_DATA_T))==0) // 间隔DTU_DATA_T时间发送数据
                     {
                         Uart_Write(UART3_ID, DTU_DATA, strlen(DTU_DATA));  // 向服务器发送数据
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=向服务器发送数据:%s\r\n", DTU_DATA);
                         #endif
                     }
                     #endif        

                     #if (DTU_SMS_EN == 1)  // 短信通信测试使能
                     if ((Delay_t%((INT16U)10*DTU_SMS_T))==0) // 间隔DTU_SMS_T时间发送短信
                     {
                         #if(DTU_SMS_MODE == '0')  // 短信编码: '0',7BIT编码, 用于发送ASCII码;
                         len = sprintf(DTUData,"AT+SMS=%s,0,%s\r\n",DTU_SMS_TEL, DTU_SMS_7BIT);  // 将发送短信的AT指令写到DTUData数组中
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=向手机%s发送短信:%s\r\n", DTU_SMS_TEL, DTU_SMS_7BIT);
                         #endif
                         #elif (DTU_SMS_MODE == '1')  // 短信编码: '1',8BIT编码, 用于发送16进制数据;
                         len = sprintf(DTUData,"AT+SMS=%s,1,%s\r\n",DTU_SMS_TEL,DTU_SMS_8BIT);  // 将发送短信的AT指令写到DTUData数组中
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=向手机%s发送短信:%s\r\n", DTU_SMS_TEL, DTU_SMS_8BIT);
                         #endif
                         #else                        // 短信编码: '2',USC2编码, 用于发送中文; 
                         len = sprintf(DTUData,"AT+SMS=%s,2,%s\r\n",DTU_SMS_TEL,DTU_SMS_USC2);  // 将发送短信的AT指令写到DTUData数组中
                         #if (DEBUG_APP_EN == 1)
                         printf("AT+DTU=向手机%s发送短信:%s\r\n", DTU_SMS_TEL, DTU_SMS_USC2);
                         #endif
                         #endif                         
                         Uart_Write(UART3_ID, DTUData, len);  // 向手机发送短信
                         
                     }
                     #endif 
				  }
				  else
				  {
				  	  Offline_t++;        // 断线时间加1
					  if (Offline_t==1)
					  {
                           #if (DEBUG_APP_EN == 1)
						   printf("AT+DTU=断线\r\n");
                           #endif
					  }

					  if (Offline_t>6000)  // 断线大于十分钟，则关闭DTU电源
					  {
						   DTUStatus = DTU_PWROFF;
						   #if (DEBUG_APP_EN == 1)
                           printf("AT+DTU=断线超过10分钟\r\n");
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
// 文件结束
/***********************************************************************************/

