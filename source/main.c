/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: main.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责系统初始化、ucos启动与任务创建、看门狗处理;
*
* Others: none;
*
* Function List:
*		
*
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*测试
*************************************************************************************/

/************************************************************************************/
// 引用外部头文件
#include "config.h"
#include <includes.h>
#include "STM32Fxxx.h"
#include "UserVars.h"
#include "APP_Init.h"
#include "OSVars.h"
#include "Delay.h"
#include "Motor.h"
#include "PlatformManage.h"
#include "PlatformDrive.h"
#include "hmi_app.h"
#include "fun.h"
#include "hmi_user_uart.h"
#include "GPIO_manager.h"
/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
static  void  App_TaskCreate       (void);
static  void  App_TaskStart        (void *p_arg);
 /**
****************************************************************************************
@brief:     OS_SemFlagCreat
@Input：    NULL
@Output：   NULL
@Return     NULL
@Warning:   NULL  
@note:      信号量邮箱等一些任务通讯变量的创建
****************************************************************************************
 **/
static void OS_SemFlagCreate(void)
{
	CPU_INT08U  os_err;
	
	OSMboxADC = OSMboxCreate((void*)0);          // 创建ADC数据传输邮箱
	OSMboxMalloc = OSMboxCreate((void*)1);      //  创建malloc()函数保护邮箱
	OSMboxFree   = OSMboxCreate((void*)1);      //  创建free()函数保护邮箱
	OSMboxSPI   = OSMboxCreate((void*)1);       //  创建SPI访问权限保护邮箱
	OSMboxX_Motor   = OSMboxCreate((void*)1);
	OSMboxY_Motor   = OSMboxCreate((void*)1);
	OSFlagSys = OSFlagCreate (0, (INT8U *)&os_err); // 创建标志变量

    APIWaitOSFlag = OSFlagCreate (0, (INT8U *)&os_err); // 创建标志变量  

	
	OSQUniversalSynchFun = OSQCreate(OSQueue_UniverSyncFun,OS_QUEUE_SIZE);//模组功能

}
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/
int  main (void)
 {
    CPU_INT08U  os_err;
	
    API_Init();             // 应用功能初始化
     
	CPU_IntDis();	        // 清除所有中断
	OSInit();               // Initialize "uC/OS-II, The Real-Time Kernel".         

    // 创建App_TaskStart任务
	os_err = OSTaskCreate((void (*)(void *)) App_TaskStart,     // Create the start task.
                          (void          * ) 0,
                          (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                          (INT8U           ) APP_TASK_START_PRIO
                         );                  
    OS_SemFlagCreate();               
	OSTimeSet(0);  // 初始化系统时钟
                          
    #if (IWDG_EN > 0)         // 看门狗使能             
	IWDG_Ctrl(CMD_IWDG_CLEAR);   // 清除看门狗
    #endif
    OSStart();                    // 启动操作系统运行, 让操作系统接管软件运行 
                                  // Start multitasking (i.e. give control to uC/OS-II). 

    return (0);                   // 永远不会运行到这里
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.启动任务，然后做一些高优先级的处理，如电机限位处理，这个任务不允许出现阻塞情况
*********************************************************************************************************/

static  void  App_TaskStart (void *p_arg)
{
	INT8U err;
	static uint8_t DIreadTemp=0xff;
	uint8_t DIread;
	ADC_VAR *pADC;
	(void)p_arg; 
	
	#if (IWDG_EN > 0) 
	IWDG_Ctrl(CMD_IWDG_CLEAR);
    #endif	

    UserVars.Flag |= OS_START_FLAG;      // 设置操作系统启动标志
#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                        // Determine CPU capacity.                              
#endif
 	App_TaskCreate();
	UserVars.TaskRunStatus = 0; 
	UserVars.TimerCount = 0;
  while (1) 
	{                                                           // Task body, always written as an infinite loop.       
		Delay_ms(10);
        #if (IWDG_EN > 0) 
        IWDG_Ctrl(CMD_IWDG_CLEAR);                               // 硬件喂狗  
		#endif
		UserVars.TimerCount+=10;
		if ((UserVars.TimerCount%1000)==0)
		{
			IO_Ctrl(RUN_LED, CMD_IO_ON_T, 300); //RUN LED间隔1秒闪烁 	
		}
		MotorFlagHandle();
		if (UserVars.TimerCount==3000)
		{
			X_AxisPositionFoundStart();;
			printf("%d\r\n",IOFunction_Read(Limiter));
		}
		
		//Limit();//电机限位处理	
	}
}
 /**
****************************************************************************************
@brief:     App_HMI 
@Input：    p_arg 启动任务时传递给任务的参数
@Output：   NULL
@Return     NULL
@Warning:   NULL  
@note:      HMI串口屏处理
****************************************************************************************
 **/
void  App_HMI (void *p_arg)
{
	INT32U General_TimeCnt; 
	uint32_t len,rUart1Len,i;
	General_TimeCnt	= 0;
	hmi_application_init();
	while(1)
	{
		Delay_ms(10);	                 // 延时10ms
        General_TimeCnt +=10 ;           // 更新时间计数器
		hmi_application_handle();		 //屏幕处理
	}
	
} /**
****************************************************************************************
@brief:     App_HMI_RX 
@Input：    p_arg 启动任务时传递给任务的参数
@Output：   NULL
@Return     NULL
@Warning:   NULL  
@note:      串口屏数据接收处理
****************************************************************************************
 **/
static  void  App_HMI_RX (void *p_arg)
{
	
	while(1)
	{
		Delay_ms(20);	                 // 延时10ms
		HMI_UartRecieve();

	}
	
}
/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/ 
static  void  App_TaskCreate (void)
{
    CPU_INT08U  os_err;
	
	//人机界面处理任务，比如串口通信等
   	os_err = OSTaskCreate((void (*)(void *)) App_HMI,
                          (void          * ) 0,
                          (OS_STK        * )&App_HMIStk[APP_HMI_STK_SIZE - 1],
                          (INT8U           ) APP_HMI_PRIO
                          );
	os_err = OSTaskCreate((void (*)(void *)) App_HMI_RX,
                          (void          * ) 0,
                          (OS_STK        * )&App_HMIRXStk[APP_HMI_RX_STK_SIZE - 1],
                          (INT8U           ) APP_HMI_RX_PRIO
                          );
 	//几个电机任务创建
	Motor_TaskCreate();
	Func_TaskCreate();
	//					  
}

/***********************************************************************************/
// 文件结束
/***********************************************************************************/



