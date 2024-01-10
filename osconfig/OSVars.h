/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: OSVars.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是操作系统任务全局变量定义, 客户可以把和操作系统相关的全局变量设置到这里;
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
// 引用外部头文件
/************************************************************************************/
#include <includes.h>
#include "const.h"
#include "config.h"
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
#define OSFLAG_FSMC_BANK1	0x00000001	 // BANK1中断标志
#define OSFLAG_FSMC_BANK2	0x00000002	 // BANK2中断标志
#define OSFLAG_FSMC_BANK3	0x00000004	 // BANK3中断标志
#define OSFLAG_FSMC_BANK4	0x00000008	 // BANK4中断标志
#define OSFLAG_NET_RXINT	0x00000010	 // DM9000接收中断标志

#define OS_QUEUE_SIZE 8//消息队列大小
/************************************************************************************
*
*       系统状态标志定义
*
*************************************************************************************/
extern OS_FLAG_GRP *APIWaitOSFlag;       // 专供驱动库API使用等待事件标志

extern OS_FLAG_GRP *OSFlagSys;
//基本任务邮箱
extern OS_EVENT *OSMboxADC;          // ADC转换完成邮箱
extern OS_EVENT *OSMboxMalloc;       // malloc()函数保护
extern OS_EVENT *OSMboxFree;         // free()函数保护
extern OS_EVENT *OSMboxSPI;          // SPI访问权限保护
extern OS_EVENT *OSMboxNET;          // 网络驱动访问权限保护
extern OS_EVENT *OSMboxNETInt;       // 网络中断

//电机控制邮箱

extern OS_EVENT *OSMboxX_Motor;//升降电机邮箱
extern OS_EVENT *OSMboxY_Motor;//转锅电机邮箱


//通用同步消息队列 洗锅功能 入料模组的撕膜 退盒子基本不会同一段时间所以只用一个任务
extern OS_EVENT *OSQUniversalSynchFun;//模组功能邮箱
extern void * OSQueue_UniverSyncFun[OS_QUEUE_SIZE];
/************************************************************************************
*
*   发送命令内存申请及消息队列定义 
*
*************************************************************************************/
// 发送命令队列
//#define OSQ_WRITE_CMD_SIZE  512
//extern  OS_EVENT *OSQWriteCmd;
//extern  void *OSQWriteCmdTbl[OSQ_WRITE_CMD_SIZE];
//
//
//#define OSQ_OUT_DATA_SIZE  32
//extern  OS_EVENT *OSQOutData;
//extern  void *OSQOutDataTbl[OSQ_OUT_DATA_SIZE];
/************************************************************************************
*   UCOS-ii 任务堆栈定义
*************************************************************************************/
extern  OS_STK   App_TaskStartStk[];

extern OS_STK   App_HMIRXStk[APP_HMI_RX_STK_SIZE];
extern OS_STK   App_HMIStk[APP_HMI_STK_SIZE];

//电机任务

extern OS_STK  APP_MotorPanRFstk[APP_MOTOR_PanRF_STK_SIZE];
extern OS_STK  APP_MotorPanRotatestk[APP_MOTOR_PanRotate_STK_SIZE];

//模组任务
extern OS_STK  APP_UniversalSynchFunstk[APP_UNIVERSAL_SYNCH_FUN_STK_SIZE];

#if (TASK_ADCDAC_EN == 1)
extern  OS_STK   App_TaskADCDACStk[APP_TASK_ADCDAC_STK_SIZE];  
#endif

#if (TASK_IO_EN == 1)
extern  OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_UARTCAN_EN == 1)
extern  OS_STK   App_TaskUartCanStk[APP_TASK_UARTCAN_STK_SIZE];	
#endif

#if (TASK_FILE_EN == 1)
extern  OS_STK   App_TaskFileStk[APP_TASK_FILE_STK_SIZE];
#endif

#if (TASK_PWMFCLK_EN == 1)
extern  OS_STK   App_TaskPWMFClkStk[APP_TASK_PWMFCLK_STK_SIZE];
#endif

#if (TASK_LWIP_EN == 1)
extern  OS_STK   App_TaskLWIPStk[APP_TASK_LWIP_STK_SIZE];
#endif

#if (TASK_MODBUS_EN == 1)
extern  OS_STK   APP_TaskModbusStk[APP_TASK_MODBUS_STK_SIZE];
#endif

#if (TASK_DTU_EN == 1)
extern  OS_STK   APP_TaskDTUStk[APP_TASK_DTU_STK_SIZE];
#endif

/************************************************************************************
*
*   任务函数定义 
*  OS_MAX_TASKS 30u最多定义30个任务
*************************************************************************************/
//最主要的任务

extern  void  App_HMI           	(void *p_arg);
extern  void  App_HMI_RX           (void *p_arg);


//电机任务
extern void Motor_PanRiseFallTask	(void *p_arg);//升降电机
extern void Motor_PanRotateTask	    (void *p_arg);//转锅电机

//功能模组
extern void Func_UniversalSynchTask	(void *p_arg);//功能模组

//电机任务

//其他任务

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
