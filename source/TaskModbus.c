/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastModbus.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是Modbus协议, 主机模式和从机模式测试例程;
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
// Modbus从机模式测试说明
/************************************************************************************/
/*
// Modbus从机(设备)模式测试: 

1. Modbus从机设备模式, 在相应配置文件做如下设置:
    #define MODBUS_SLAVE_EN        1           // MODBUS从机通信使能：1, 使能;  0, 关闭;

    #define MODBUS_SLAVE_MODE      0           // MODBUS从机通信模式：0, RTU;  1, ASCII码; 
    #define MODBUS_SLAVE_CH        UART4_ID    // MODBUS从机通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
    #define MODBUS_SLAVE_ID        1           // MODBUS从机通信地址码, 范围：1~255;

    #define MODBUS_COILS_BASEADDR 	  10000        // 线圈寄存器基地址;
    #define MODBUS_DISINPUT_BASEADDR  10000        // 离散输入量寄存器基地址;
    #define MODBUS_HOLDREG_BASEADDR   10000        // 保持寄存器基地址;
    #define MODBUS_INPUTREG_BASEADDR  10000        // 输入寄存器基地址;

    #define MODBUS_MAX_COILS       32          // MODBUS从机最大线圈数量(读写,可用功能码:1,5,15);
    #define MODBUS_MAX_DISINPUT    32          // MODBUS从机最大离散输入量(只读,可用功能码:2);
    #define MODBUS_MAX_HOLDREG     16          // MODBUS从机最大保持寄存器(读写,可用功能码:3,6,16,23)数量;	 
    #define MODBUS_MAX_INPUTREG    16          // MODBUS从机最大输入寄存器(只读,可用功能码:4)数量;

    #define MODBUS_DATA_LEN        64          // 设置协议缓存, 默认64(最大30个寄存器读写),用户可以根据MODBUS_MAX_HOLDREG和MODBUS_MAX_INPUTREG中最大值的2倍再加4即可

2. 应用方式 
     (1) 在从机通信通道(MODBUS_SLAVE_CH)读取数据, 并调用Modbus_Proc()函数进行Modbus协议解析;
         注意: 在函数Modbus_Proc()中解析协议, 读写的寄存器是vars.c中的ModbusCoils[], ModbusDisInput[], ModbusHoldReg[],ModbusInputReg[]寄存器;
         起始地址默认为0; 如果起始起始地址不为0, 则需要再配置文件设置基地址: MODBUS_COILS_BASEADDR,MODBUS_DISINPUT_BASEADDR,MODBUS_HOLDREG_BASEADDR,MODBUS_INPUTREG_BASEADDR
         
     (2) 对于应用程序, 只需要将需要的数据写入读取ModbusCoils[], ModbusDisInput[], ModbusHoldReg[],ModbusInputReg[]寄存器即可，
         例如可以参考在TaskIO.c和TaskADC.c中的IO输入输出及AD采集量写入Modbus寄存器程序:
         DI输入量写入ModbusDisInput[]中, DO输出量写入ModbusCoils[]中, AD采样写入到ModbusInputReg[]中
     
     (3) 通过计算机Modbus测试软件可以读写工控板寄存器
            
3. 通过串口调试输出观察结果; 

4. 注意：如果这里占用了哪个UART(RS232或RS485)端口，请将TaskUart.c中的相应UART测试程序取消;
*/

/************************************************************************************/
// Modbus主机模式(读写设备寄存器)测试说明
/************************************************************************************/
/*
1. Modbus主机模式, 在相应配置文件做如下设置:
    #define MODBUS_EN         1           // MODBUS通信使能：1, 使能;  0, 关闭;
    #define MODBUS_MODE       0           // MODBUS通信模式：0, RTU;  1, ASCII码; 
    #define MODBUS_CH         UART3_ID    // MODBUS通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
    #define MODBUS_ID         1           // MODBUS操作设备的通信地址ID, 默认1 
    #define MODBUS_TIMEOUT    1000        // MODBUS通信超时时间, 单位ms;

2. 根据本文件常量及全局变量中定义，设置相关项目进行测试，注意这时必须连接UART3(RS232或者RS485)接口连接用户的Modbus RTU协议设备或者计算机;

3. 注意：如果这里占用了哪个UART(RS232或RS485)端口，请将TaskUart.c中的相应UART测试程序取消;
*/

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "config.h"
#if (TASK_MODBUS_EN == 1)
#include "Vars.h"
#include "UserVars.h"
#include "OSHook.h"
#include "STM32Fxxx.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#if (MODBUS_EN > 0)
// 工控板作为Modbus主机
#define REG_START_ADDR      0         // 寄存器起始地址

// 测试程序条件编译选项 , 请使用下面选项设置1或者0, 开启或关闭相关测试
#define DIx_READ_EN         1         // 读取设备DI数字量输入寄存器       
#define DOx_WRITE_EN        1         // 写入设备D0数字量输出寄存器
#define DOx_READ_EN         1         // 读取设备D0数字量输出寄存器
#define AIx_READ_EN         1         // 读取设备模拟量输入寄存器 
#define HOLDREG_WRITE_EN    1         // 写入设备保持寄存器
#define HOLDREG_READ_EN     1         // 读取设备保持寄存器
#define HOLDREG_READ_WRITE_EN   0     // 同时读取写入设备保持寄存器

// 读取寄存器长度定义
#define DI_NUM              8         // 设备DI数量
#define DO_NUM              8         // 设备DO数量
#define AI_NUM              8         // 设备AI数量
#define HOLDREG_NUM         8         // 设备保持寄存器数量

#if (DIx_READ_EN > 0)
INT8U  DI_Buf[(DI_NUM+7)/8];  // 设备DI缓存
#endif

#if ((DOx_WRITE_EN > 0)||(DOx_READ_EN>0))
INT8U  DO_Buf[(DO_NUM+7)/8];  // 设备DO缓存
#endif

#if (AIx_READ_EN > 0)
INT16U AI_Buf[AI_NUM];        // 设备AI缓存
#endif

#if ((HOLDREG_WRITE_EN >0 )||(HOLDREG_READ_EN >0 )||(HOLDREG_READ_WRITE_EN >0 ))
INT16U HoldReg_Buf[HOLDREG_NUM];  // 设备保持寄存器缓存
#endif

#endif
/***********************************************************************************
* Function: App_TaskModbus;
*
* Description: 从机MODBUS协议处理任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   必须由UCOS-II操作系统创建;
************************************************************************************/
void App_TaskModbus(void *p_arg)
{	 

    INT32S flag, i, cnt;
    INT16U rUartLen, len;
	INT8U err, *pMEM;
    
    (void)p_arg;
    
     while(1)
     {
         UserVars.TaskRunStatus |= TASK_MODBUS_FLAG;    // 设置本任务运行状态标志
         Delay_ms(20);                                  // 延时20ms
/**********************************************************************************************************/
// 控制板作为Modbus设备测试
/**********************************************************************************************************/          
         #if (MODBUS_SLAVE_EN > 0)  // 判断Modbus从机模式是否使能
		 len = Uart_Ctrl(MODBUS_SLAVE_CH, CMD_UART_GetCharsRxBuf,0);// 读取接收数据长度
		 if ((len == rUartLen)&&(len>0))
		 {
              pMEM = (INT8U *)OSMalloc(len);  // 申请内存             
			  Uart_Read(MODBUS_SLAVE_CH, pMEM, len); // 读取接收数据到内存
              #if (DEBUG_APP_EN > 0)
              printf("AT+MODBUS=RX:");
              for (i=0; i<len; i++)
              {
                  printf("%02X ", *(pMEM+i));
              } 
              printf("\r\n");
              #endif
              flag = Modbus_Proc(MODBUS_SLAVE_CH, MODBUS_SLAVE_ID, pMEM, len, (MODBUS_PARA *)&ModbusPara.Flag); // Modbus数据处理
              OSFree(pMEM);                            // 注销内存 
              #if (DEBUG_APP_EN > 0)
              if (flag == ERR_TRUE) 
              {                  
                  printf("AT+MODBUS=TX:");
                  pMEM = (INT8U *)&ModbusPara.pData->id;
                  for (i=0; i<ModbusData.len; i++)
                  {
                      printf("%02X ", *pMEM++);
                  } 
                  printf("\r\n");
              }
              else
              {
                  printf("AT+MODBUS=协议解析失败\r\n");
              }
              #endif
              
	          rUartLen -= len;
		 }
		 else
		 {
			  rUartLen	= len;
		 }
         #endif

/**********************************************************************************************************/
// 控制板作为Modbus主机测试
/**********************************************************************************************************/          		 
         #if (MODBUS_EN > 0)  // 判断Modbus主机模式是否使能
         cnt++;  
         if ((cnt%150)==0)     // 每隔3秒执行 
         {         
             #if (DIx_READ_EN == 1) // 读取设备DI数字量输入寄存器               
             flag = Modbus_ReadDisInput(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DI_NUM, DI_Buf, MODBUS_TIMEOUT); // 主机读离散输入量请求函数，调用该函数发送读离散输入量请求 
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=DI:");
                 for(i=0;i<((DI_NUM+7)/8); i++)
                 {
                     printf(" %02X", DI_Buf[i]);
                 }
                 printf("\r\n");
             }
             else
             {
                 printf("AT+MODBUS=Read DI error: %d\r\n", flag);
             }
             #endif
              
             #if (AIx_READ_EN == 1) // 读取设备模拟量输入寄存器 
             flag = Modbus_ReadInputReg(MODBUS_CH, MODBUS_ID, REG_START_ADDR, AI_NUM, AI_Buf, MODBUS_TIMEOUT); // 主机读输入寄存器请求函数，调用该函数发送读输入寄存器请求
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=AI:");
                  for (i=0; i<AI_NUM; i++)
                  {
                       printf(" %04X", AI_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Read AI error: %d\r\n", flag);
             }
             #endif
              
             #if (DOx_WRITE_EN == 1) // 写入设备D0数字量输出寄存器			  
              // 写入DO1值1(ON)
             flag = Modbus_WriteSingleCoil(MODBUS_CH,  MODBUS_ID, REG_START_ADDR+0, 1, MODBUS_TIMEOUT);  // 主机写单个线圈请求函数，调用该函数发送写单个线圈请求
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write DO1 OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DO1 error: %d\r\n", flag);
             }
             
             // 写入DO2值0(OFF)
             flag = Modbus_WriteSingleCoil(MODBUS_CH,  MODBUS_ID, REG_START_ADDR+1, 0, MODBUS_TIMEOUT);  // 主机写单个线圈请求函数，调用该函数发送写单个线圈请求
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write DO2 OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DO2 error: %d\r\n", flag);
             }
              
             // 一次写多个DO
             for(i=0;i<((DO_NUM+7)/8); i++)  
             {
                 DO_Buf[i] = 0x55;
             }	 			  
             flag = Modbus_WriteMulCoils(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DO_NUM, DO_Buf, MODBUS_TIMEOUT); // 调用该函数发送写多个线圈请求
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=Write DOx OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DOx error: %d\r\n", flag);
             }
             #endif
              
             #if (DOx_READ_EN == 1) // 读取设备D0数字量输出寄存器
             flag = Modbus_ReadCoils(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DO_NUM, DO_Buf, MODBUS_TIMEOUT); // 主机读线圈请求函数，调用该函数发送读线圈请求
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Read DO:");
                  for(i=0;i<((DO_NUM+7)/8); i++)
                  {
                      printf(" %02X", DO_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                 printf("AT+MODBUS=Read DO error: %d\r\n", flag);
             }
             #endif

              
             #if (HOLDREG_WRITE_EN == 1) // 写入设备保持寄存器
              // 写地址1的保持寄存器: 0x55
             flag = Modbus_WriteSingleReg(MODBUS_CH, MODBUS_ID, 1, 0x55, MODBUS_TIMEOUT); // 调用该函数发送写单个保持寄存器请求			  
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write HoldReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write HoldReg error: %d\r\n", flag);
             }	
              
             // 写多个保持寄存器值
             for(i=0;i<HOLDREG_NUM; i++) // 寄存器设置初始值
             {
                  HoldReg_Buf[i] = 0x55+i;
             }	 			  
             flag = Modbus_WriteMulReg(MODBUS_CH, MODBUS_ID, REG_START_ADDR, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // 调用该函数发送写多个寄存器请求
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write MulReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write MulReg error: %d\r\n", flag);
             }
             #endif
           
             #if (HOLDREG_READ_EN == 1) // 读取设备保持寄存器			   
             flag = Modbus_ReadHoldReg(MODBUS_CH,  MODBUS_ID, REG_START_ADDR, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // 主机读保持寄存器请求函数，调用该函数发送读保持寄存器请求
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Read HoldReg:");
                  for (i=0; i<HOLDREG_NUM; i++)
                  {
                       printf(" %04X", HoldReg_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Read HoldReg error: %d\r\n", flag);
             }
             #endif
              
             #if (HOLDREG_READ_WRITE_EN == 1) // 同时读取写入设备保持寄存器	
             for(i=0;i<HOLDREG_NUM; i++)   // 初始化保持寄存器
             {
                  HoldReg_Buf[i] = 0xAA;
             }	 			  
             // 写入地址0开始写入HOLDREG_NUM个数据，再读出这HOLDREG_NUM个数据
             flag = Modbus_ReadWriteMulReg(MODBUS_CH, MODBUS_ID, 0, HOLDREG_NUM, 0, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // 调用该函数读和写多寄存器请求。执行该函数时，先写入后读出。
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=ReadWrite MulReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=ReadWrite MulReg error: %d\r\n", flag);
             }
             #endif
         }
         #endif
     }
}	  
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/



