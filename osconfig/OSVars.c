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
#include "OSVars.h"

/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
OS_FLAG_GRP *APIWaitOSFlag;       // 专供驱动库API使用等待事件标志

OS_FLAG_GRP *OSFlagSys;

OS_EVENT *OSMboxADC;         // ADC转换完成邮箱

OS_EVENT *OSMboxX;

OS_EVENT *OSMboxMalloc;       // malloc()函数保护
OS_EVENT *OSMboxFree;         // free()函数保护
OS_EVENT *OSMboxSPI;          // SPI访问权限保护
OS_EVENT *OSMboxNET;          // 网络驱动访问权限保护
OS_EVENT *OSMboxNETInt;       // 网络中断


//炒菜机信号量、邮箱、消息队列、事件标志组定义
//电机
OS_EVENT *OSMboxX_Motor;//撕膜电机邮箱——————传递的参数是函数指针
OS_EVENT *OSMboxY_Motor;//挡盒电机邮箱


OS_EVENT *OSQUniversalSynchFun;//通用同步功能消息队列


void * OSQueue_UniverSyncFun[OS_QUEUE_SIZE];//定义消息队列
//模组功能
/************************************************************************************
*   UCOS-ii 任务堆栈定义
*************************************************************************************/
__align(8) OS_STK   App_TaskStartStk[APP_TASK_START_STK_SIZE];//
//常用任务


__align(8) OS_STK   App_HMIStk[APP_HMI_STK_SIZE];
__align(8) OS_STK   App_HMIRXStk[APP_HMI_RX_STK_SIZE];
//电机任务

__align(8) OS_STK  APP_MotorPanRFstk[APP_MOTOR_PanRF_STK_SIZE];
__align(8) OS_STK  APP_MotorPanRotatestk[APP_MOTOR_PanRotate_STK_SIZE];


//模组任务
__align(8) OS_STK  APP_UniversalSynchFunstk[APP_UNIVERSAL_SYNCH_FUN_STK_SIZE];
#if (TASK_ADCDAC_EN == 1)
__align(8) OS_STK   App_TaskADCDACStk[APP_TASK_ADCDAC_STK_SIZE];  
#endif

#if (TASK_IO_EN == 1)
__align(8) OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_UARTCAN_EN == 1)
__align(8) OS_STK   App_TaskUartCanStk[APP_TASK_UARTCAN_STK_SIZE];	
#endif

#if (TASK_FILE_EN == 1)
__align(8) OS_STK   App_TaskFileStk[APP_TASK_FILE_STK_SIZE];
#endif

#if (TASK_PWMFCLK_EN == 1)
__align(8) OS_STK   App_TaskPWMFClkStk[APP_TASK_PWMFCLK_STK_SIZE];
#endif

#if (TASK_LWIP_EN == 1)
__align(8) OS_STK   App_TaskLWIPStk[APP_TASK_LWIP_STK_SIZE];
#endif

#if (TASK_MODBUS_EN == 1)
__align(8) OS_STK   APP_TaskModbusStk[APP_TASK_MODBUS_STK_SIZE];
#endif

#if (TASK_DTU_EN == 1)
__align(8) OS_STK   APP_TaskDTUStk[APP_TASK_DTU_STK_SIZE];
#endif


/***********************************************************************************/
// 文件结束
/***********************************************************************************/



