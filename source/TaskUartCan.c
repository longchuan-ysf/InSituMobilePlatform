/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastUartCan.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责测试串行通信接口UART(RS232和RS485)、CAN和USB虚拟串口通信任务处理; 
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
1. UART1~UART6(RS232或RS485)通信测试说明: 
    (1). IO配置说明: 在IO配置文件中配置TX,RX和DIR(RS485方向控制)管脚, 以UART1为例 IO配置: 
         // UART1(管脚)功能重映射设置
         #define UART1_REMAP      UART_REMAP_1    // UART1重映射1, 只有STM32F107VC/103VE/103ZE有此配置
         #define UART1_TX         PB6             // 设置TX管脚
         #define UART1_RX         PB7             // 设置RX管脚 
         #define UART1_DIR        IO_NONE         // 设置RS485方向控制IO, 没有转RS485接口则设置为IO_NONE
         #define UART1_DIR_HL     0               // 定义RS485通信时接收数据时方向电平, 0: 低电平接收; 1: 高电平接收
       
         默认已经配置好, 不用修改;
     
    (2). 功能参数配置说明: 在配置文件中做如下配置, 以UART1为例:      
         #define UART1_EN          1       // UART1使能, 1：打开使能， 0：关闭
         #define UART1_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
         #define UART1_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
         #define UART1_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
         #define UART1_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

         #define UART1_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
         #define UART1_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

    (3). 根据以上(1)(2)配置, 在APP_Init.c中调用Uart_APPInit()函数初始化; 
    
    (4). 本文测试程序实现功能: 接收外部(计算机)发来的数据，并将数据原样发送出去;
         实现方法: 间隔20ms调用len = Uart_Ctrl(UART1_ID, CMD_UART_GetCharsRxBuf,0), 读取缓存中接收数据长度,
         再进行if ((len == rUart1Len)&&(len>0))判断: 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了;  
         调用Uart_Read(UART1_ID, UserVars.buf, len) 将数据读取到UserVars.buf中; 
         调用Uart_Write(UART1_ID, UserVars.buf, len) 将UserVars.buf数据在原样发送回去;
         
         本例程接收数据方法: 只适合接收间隔一定时间(大于50ms间隔)的数据段; 如果是无时间间隔分段数据, 请接收完数据自行进行数据拼接及数据解析; 
    
    (5). 通过串口调试输出观察接收发送数据结果; 利用串口调试助手进行收发数据测试;
    
2. CAN1~CAN2通信测试说明: 
    (1). IO配置说明: 在IO配置文件中配置TX, RX管脚, 以CAN1为例 IO配置: 
         // CAN1(管脚)功能重映射设置
         #define CAN1_TX         PD1            // CAN1设置TX管脚
         #define CAN1_RX         PD0            // CAN1设置RX管脚 
       
         默认已经配置好, 不用修改;
     
    (2). 功能参数配置说明: 在配置文件中做如下配置, 以CAN1为例:  
        #define CAN1_EN          1		        // CAN1使能, 1：打开使能， 0：关闭

        #define CAN1_MODE		 0		        // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
        #define CAN1_IDE         CAN_EXT_ID     // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
        #define CAN1_RTR         CAN_RTR_DATA   // 选择数据帧:CAN_RTR_DATA 或远程帧:CAN_RTR_REMOTE
        #define CAN1_BAUD	     50000          // CAN1波特率; 
        
        #define CAN1_RXBUF_SIZE   16            // CAN接收缓存可接收消息个数,范围 1~256
        #define CAN1_TXBUF_SIZE   16            // CAN发送缓存可发送消息个数,范围 1~256

    (3). 根据以上(1)(2)配置, 在APP_Init.c中调用CAN_APPInit()函数初始化; 
    
    (4). 本文测试程序实现功能: 硬件电路板A的CAN接口连接电路板B的CAN接口
         条件编译选择电路板A: 选择#define  CAN_TEST_A, A板地址ID1-ID4发送数据0-7到B板, 并检测B板发回来的数据, 读取并打印输出; 
         条件编译选择电路板B: 选择#define  CAN_TEST_B, B板接收A板发来的数据,并将数据原样发送给A板;
    
    (5). 电路板A发送接收数据例程说明: 
         每隔3秒初始化发送数据CanTx, 并调用CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID)发送4组数据给电路板B
         调用n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0), 读取CAN缓存, 判断是否接收到电路板B返回的数据
         如果n>0, 表示接收到数据, 调用CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID)读取数据, 通过调试串口打印出数据;
         
    (6). 电路板B接收发送数据例程说明: 
         每隔3秒初始化发送数据CanTx, 并调用CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID)发送4组数据给电路板B
         调用n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0), 读取CAN缓存, 判断是否接收到电路板A发来的数据
         如果n>0, 表示接收到数据, 调用CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID)读取数据, 并调用
         CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanRx.ID), 将接收数据发送给电路板A;
         通过调试串口打印出数据;         

3. USB设备模式下, 虚拟串口测试:
   (1). 功能参数配置说明: USB_DEVICE_EN配置为1(注: USB_HOST_EN必须设置为1), USB_VCP_EN配置为1, 注意USB_MSC_EN要设置为0;
   
   (2). 根据以上(1)配置, 在APP_Init.c中调用USBD_APPInit()函数初始化;
   
   (3). 本文测试程序实现功能: 接收外部(计算机, USB虚拟串口)发来的数据，并将数据原样发送出去;
        实现方法: 将USB线连接电路板USB设备接口, 另一接口插在计算机上, 计算机提前要安装STM32的虚拟串口驱动;
        先调用USBD_Ctrl(0, CMD_USBD_SYNC, 0), 进行USB更新同步, 根据返回状态, 判断虚拟串口正常工作;
        间隔20ms调用len = USBD_Ctrl(0, CMD_USBD_GetCharsRxBuf,0), 读取USB虚拟串口缓存中接收数据长度,
        再进行if ((len == rUSBLen)&&(len>0))判断: 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了;  
        调用USBD_Read(0, UserVars.buf, len) 将数据读取到UserVars.buf中; 
        调用USBD_Write(0, UserVars.buf, len) 将UserVars.buf数据在原样发送回去;
         
        本例程接收数据方法: 只适合接收间隔一定时间(大于50ms间隔)的数据段; 如果是无时间间隔分段数据, 请接收完数据自行进行数据拼接及数据解析; 

   (4). 通过插拔USB线可以观察计算机上会出现新的串口, 利用串口调试助手进行收发数据测试;
*/

/************************************************************************************/
// 引用外部头文件
#include "config.h"
#if (TASK_UARTCAN_EN == 1)
#include "STM32Fxxx.h"
#include "UserVars.h"
#include "AT.h"
#include "vars.h"

/************************************************************************************/
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
//#define  CAN_TEST_A      // 条件编译电路板A(A板)程序：电路板A发送数据到电路板B, 并接收电路板B返回的数据
#define  CAN_TEST_B    // 条件编译电路板B(B板)程序: 电路板B接收电路板A发来的数据,并将数据原样发送给电路板A

/***********************************************************************************
* Function: App_TaskUart;
*
* Description: 读取按键K1-K4键值;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: 返回键值：KNONE，K1VAL-K4VAL;
*
* Note:   none;
************************************************************************************/
void  App_TaskUartCan(void *p_arg)
{
    INT16U  rUart1Len,rUart2Len,rUart3Len,rUart4Len,rUart5Len,rUart6Len;  // UART1/2/3/4/5/6接收数据长度
	INT16U  rUSBLen;    // USB接收数据长度
	INT16U  len, i, n, t3s;
    INT32S  flag;
    #if (CAN1_EN > 0)
   	CAN_TX_MSG CanTx; // CAN发送数据
	CAN_RX_MSG CanRx; // CAN接收数据
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
	     UserVars.TaskRunStatus |= TASK_UARTCAN_FLAG;         // 设置本任务运行状态标志
        
		 Delay_ms(20);	                                      // 延时20ms         
         #if (DEBUG_ISRHOOK_EN > 0)  
         if(DebugInfo.len > 0)
         {    
             Uart_Write(DEBUG_UART, DebugInfo.buf, DebugInfo.len);
             DebugInfo.len = 0;
         }
         #endif
/*******************************************************************************************************/
// UART1接收发送处理
/*******************************************************************************************************/
#if (UART1_EN > 0)
         len = Uart_Ctrl(UART1_ID, CMD_UART_GetCharsRxBuf,0); // 读取接收数据长度
		 if ((len == rUart1Len)&&(len>0))                     // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                           // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART1_ID, UserVars.buf, len);         // 将数据读取到UserVars.buf中
			  #if (AT_EN > 0)
              AT_Proc(UserVars.buf, len);                     // AT指令处理函数
              #else
              Uart_Write(UART1_ID, UserVars.buf, len);        // 将UserVars.buf数据在原样发送回去
              #endif
              
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;
              if (UserVars.Para.ATFlag&AT_UART_FLAG)        // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART1=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
	          
              rUart1Len -= len;                               // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart1Len	= len;                                // 赋值最新接收缓存数据长度
		 }
#endif

/*******************************************************************************************************/
// UART2接收发送处理
/*******************************************************************************************************/
#if (UART2_EN > 0)
		 len = Uart_Ctrl(UART2_ID, CMD_UART_GetCharsRxBuf,0);// 读取接收数据长度
		 if ((len == rUart2Len)&&(len>0))                    // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                          // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART2_ID, UserVars.buf, len);       // 将数据读取到UserVars.buf中			
              Uart_Write(UART2_ID, UserVars.buf, len);      // 将UserVars.buf数据在原样发送回去   
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;
              if (UserVars.Para.ATFlag&AT_UART_FLAG)        // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART2=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
              rUart2Len -= len;                             // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart2Len	= len;                              // 赋值最新接收缓存数据长度
		 }
#endif
        
 /*******************************************************************************************************/
// UART3接收发送处理
/*******************************************************************************************************/        
#if (UART3_EN > 0)
         #if (MODBUS_EN == 0)  // 判断是否被Modbus主机模式占用
		 len = Uart_Ctrl(UART3_ID, CMD_UART_GetCharsRxBuf,0);   // 读取接收数据长度
		 if ((len == rUart3Len)&&(len>0))                       // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                             // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART3_ID, UserVars.buf, len);           // 将数据读取到UserVars.buf中
			  Uart_Write(UART3_ID, UserVars.buf, len);          // 将UserVars.buf数据在原样发送回去
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART3=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
                 
	          rUart3Len -= len;                                 // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart3Len	= len;                                  // 赋值最新接收缓存数据长度
		 }
         #endif
#endif
         
/*******************************************************************************************************/
// UART4接收发送处理
/*******************************************************************************************************/		 
#if (UART4_EN > 0)
         #if (MODBUS_SLAVE_EN == 0)  // 判断是否被Modbus从机模式占用
		 len = Uart_Ctrl(UART4_ID, CMD_UART_GetCharsRxBuf,0);   // 读取接收数据长度
		 if ((len == rUart4Len)&&(len>0))                       // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                             // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART4_ID, UserVars.buf, len);           // 将数据读取到UserVars.buf中
			  Uart_Write(UART4_ID, UserVars.buf, len);          // 将UserVars.buf数据在原样发送回去
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART4=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
	          rUart4Len -= len;                                 // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart4Len	= len;                                  // 赋值最新接收缓存数据长度
		 }
         #endif
#endif
         
/*******************************************************************************************************/
// UART5接收发送处理
/*******************************************************************************************************/	
#if (UART5_EN > 0)
		 len = Uart_Ctrl(UART5_ID, CMD_UART_GetCharsRxBuf,0);   // 读取接收数据长度
		 if ((len == rUart5Len)&&(len>0))                       // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                             // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART5_ID, UserVars.buf, len);           // 将数据读取到UserVars.buf中
			  Uart_Write(UART5_ID, UserVars.buf, len);          // 将UserVars.buf数据在原样发送回去
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART5=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);
              }
              #endif
              
	          rUart5Len -= len;                                 // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart5Len	= len;                                  // 赋值最新接收缓存数据长度
		 }
#endif

/*******************************************************************************************************/
// UART6接收发送处理
/*******************************************************************************************************/	
#if (UART6_EN > 0)
#if (MODULE_CLASS == STM32F407XX)
		 len = Uart_Ctrl(UART6_ID, CMD_UART_GetCharsRxBuf,0);   // 读取接收数据长度
		 if ((len == rUart6Len)&&(len>0))                       // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
		 {
			  if (len>DATABUF_SIZE)                             // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
			  {
			      len = DATABUF_SIZE;
			  }
			  Uart_Read(UART6_ID, UserVars.buf, len);           // 将数据读取到UserVars.buf中
			  Uart_Write(UART6_ID, UserVars.buf, len);          // 将UserVars.buf数据在原样发送回去
              
              #if (DEBUG_APP_EN == 1)
              UserVars.buf[len] = 0;                            
              if (UserVars.Para.ATFlag&AT_UART_FLAG)            // 打印数据输出到调试串口(注意:只能显示ASCII字符)
              {
                  printf("AT+UART6=RH,%d,", len);
                  for(i=0; i<(len-1); i++)
                  {
                       printf("%02x ", UserVars.buf[i]);
                  }
                  printf("%02x\r\n", UserVars.buf[i]);            
              }
              #endif
              
	          rUart6Len -= len;                                 // 调整最新接收缓存数据长度
		 }
		 else
		 {
			  rUart6Len	= len;                                  // 赋值最新接收缓存数据长度
		 }
#endif
#endif
         
/*******************************************************************************************/      
// CAN1通信测试程序
/*******************************************************************************************/      
#if (CAN1_EN > 0)        
#ifdef CAN_TEST_A      // 条件编译A板程序：A板发送数据到B板, 并接收B板返回的数据, 对比是否正确
        t3s++;
        // 初始化发送数据：8个字节，数据：0-7
        if ((t3s%150) == 0)  // 判断每隔3秒
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
            
            for (i=0; i<4; i++)  // 发送4组数据: id分别是1-4, 数据0-7
            {
                CanTx.ID = i+1;  // 设置id: 1-4
                CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanTx.ID); // 发送一组数据给B板
                #if (DEBUG_APP_EN > 0)
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN1=WH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanTx.Data[1], CanTx.Data[2],\
                       CanTx.Data[3], CanTx.Data[4], CanTx.Data[5], CanTx.Data[6], CanTx.Data[7]);    
                }
                #endif
            }
        }
        if ((t3s%5) == 0)  // 判断每隔100ms
        {    
            n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0);  // 读取CAN缓存，是否有数据
            if (n>0)  // 判断是否接收到数据
            {
                for (i=0; i<n; i++)  // 读取接收到的B板发来的n组数据
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
#ifdef  CAN_TEST_B    // 条件编译B板程序: B板接收A板发来的数据,并将数据原样发送给A板         
		n = CAN_Ctrl(CAN1_ID, CMD_CAN_GetMsgRxBuf, 0);  // 读取CAN缓存，是否有数据
		if (n>0)   // 判断是否接收到数据
		{
            for (i=0; i<n; i++)         
			{
				CAN_Read(CAN1_ID, (CAN_RX_MSG *)&CanRx.ID);  // 读取A板发来的一组接收数据
				#if (DEBUG_APP_EN == 1)			
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN1=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                       CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]);                                                 
                }
                #endif
                CAN_Write(CAN1_ID, (CAN_TX_MSG *)&CanRx.ID); // 将接收的数据发送给A板
			}
		}            
#endif   
#endif   
        
/*******************************************************************************************/      
// CAN2通信测试程序
/*******************************************************************************************/     
#if (CAN2_EN > 0)        
#ifdef CAN_TEST_A      // 条件编译A板程序：A板发送数据到B板, 并接收B板返回的数据, 对比是否正确
        //t3s++;
        // 初始化发送数据：8个字节，数据：0-7
        if ((t3s%150) == 0)  // 判断每隔3秒
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
            
            for (i=0; i<4; i++)  // 发送4组数据: id分别是1-4, 数据0-7
            {
                CanTx.ID = i+1;  // 设置id: 1-4
                CAN_Write(CAN2_ID, (CAN_TX_MSG *)&CanTx.ID); // 发送一组数据给B板
                #if (DEBUG_APP_EN > 0)
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN2=WH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanTx.Data[1], CanTx.Data[2],\
                       CanTx.Data[3], CanTx.Data[4], CanTx.Data[5], CanTx.Data[6], CanTx.Data[7]);    
                }
                #endif
            }
        }
        if ((t3s%5) == 0)  // 判断每隔100ms
        {    
            n = CAN_Ctrl(CAN2_ID, CMD_CAN_GetMsgRxBuf, 0);  // 读取CAN缓存，是否有数据
            if (n>0)  // 判断是否接收到数据
            {
                for (i=0; i<n; i++)  // 读取接收到的B板发来的n组数据
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
#ifdef  CAN_TEST_B    // 条件编译B板程序: B板接收A板发来的数据,并将数据原样发送给A板         
		n = CAN_Ctrl(CAN2_ID, CMD_CAN_GetMsgRxBuf, 0);  // 读取CAN缓存，是否有数据
		if (n>0)   // 判断是否接收到数据
		{
            for (i=0; i<n; i++)         
			{
				CAN_Read(CAN2_ID, (CAN_RX_MSG *)&CanRx.ID);  // 读取A板发来的一组接收数据
				#if (DEBUG_APP_EN == 1)
				if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("AT+CAN2=RH,%d,%d,%02x %02x %02x %02x %02x %02x %02x %02x\r\n",CanTx.ID,CanTx.DLC,CanTx.Data[0],CanRx.Data[1], CanRx.Data[2],\
                       CanRx.Data[3], CanRx.Data[4], CanRx.Data[5], CanRx.Data[6], CanRx.Data[7]); 
                }
                #endif
                CAN_Write(CAN2_ID, (CAN_TX_MSG *)&CanRx.ID); // 将接收的数据发送给A板
			}
		}            
#endif   
#endif   
/*******************************************************************************************************/      
// USB虚拟串口接收发送数据接收发送处理
/*******************************************************************************************************/        
        #if ((USB_DEVICE_EN > 0)&&(USB_VCP_EN > 0))  // USB设备配置使能, 工作在虚拟串口模式           
        flag = USBD_Ctrl(USB_ID, CMD_USBD_SYNC, 0);	                     // USB设备同步处理,返回USB设备状态
        if (flag&USBD_WORK_OK)  // 判断虚拟串口正常工作
        {
            len = USBD_Ctrl(USB_ID, CMD_USBD_GetCharsRxBuf,0);    // 读取接收数据长度
            if ((len == rUSBLen)&&(len>0))
            {
                if (len>DATABUF_SIZE)                     // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
                {
                    len = DATABUF_SIZE;
                }
                USBD_Read(USB_ID, UserVars.buf, len);
                USBD_Write(USB_ID, UserVars.buf, len);

                #if (DEBUG_APP_EN == 1)
                UserVars.buf[len] = 0;                            
                if (UserVars.Para.ATFlag&AT_CAN_FLAG)
                {
                    printf("\r\nAT+USB=VCP接收发送数据[%d]:%s\r\n", len, UserVars.buf); // 打印数据输出到调试串口(注意:只能显示ASCII字符)
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
// 文件结束
/***********************************************************************************/

