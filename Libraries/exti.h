/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: exti.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是外部中断/事件控制器(EXTI)硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S EXTI_Init(EXTI_PARA *pPara);
*          2. INT32S EXTI_Ctrl(INT8U id, INT8U Cmd);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __EXIT_H 
#define __EXIT_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 常量定义
/************************************************************************************/
// 中断索引ID定义：
#define EXTI0_ID		 0     // IO中断0索引
#define EXTI1_ID		 1     // IO中断1索引
#define EXTI2_ID		 2     // IO中断2索引
#define EXTI3_ID		 3     // IO中断3索引
#define EXTI4_ID		 4     // IO中断4索引
#define EXTI5_ID		 5     // IO中断5索引
#define EXTI6_ID		 6     // IO中断6索引
#define EXTI7_ID		 7     // IO中断7索引
#define EXTI8_ID		 8     // IO中断8索引
#define EXTI9_ID 	     9     // IO中断9索引
#define EXTI10_ID	     10    // IO中断10索引
#define EXTI11_ID	     11    // IO中断11索引
#define EXTI12_ID	     12    // IO中断12索引
#define EXTI13_ID	     13    // IO中断13索引
#define EXTI14_ID	     14    // IO中断14索引
#define EXTI15_ID	     15    // IO中断15索引

#define EXTI16_PVD_ID	            16    // IO中断16索引, EXIT线16连接到PVD输出
#define EXTI17_RTCAlarm_ID	        17    // IO中断17索引, EXIT线17连接到RTC闹钟事件
#define EXTI18_USBWakeUp_ID	        18    // IO中断18索引, EXIT线18连接到USB OTG FS唤醒事件
#define EXTI19_NETWakeUp_ID	        19    // IO中断19索引, EXIT线19连接到以太网唤醒事件
// 以下是STM32F4XX芯片新增定义
#define EXTI20_USBHSWakeUp_ID       20   // IO中断20索引, EXIT线20连接到USB OTG HS唤醒事件
#define EXTI21_RTCTSE_ID	        21   // IO中断21索引, EXIT线21连接到RTC入侵和时间戳事件
#define EXTI22_RTCWakeUp_ID	        22   // IO中断22索引, EXIT线22连接到RTC唤醒事件

// 中断模式定义
#define EXTI_RISING            0    // 上升沿中断和事件;
#define EXTI_FALLING           1    // 下降沿中断和事件;
#define EXTI_RISING_FALLING    2    // 上升沿下降沿都中断和事件;

// EXInt_Ctrl控制命令Cmd定义
#define EXTI_CMD_DIS           0    // 关闭中断和事件请求命令
#define EXTI_CMD_INT_ENA       1    // 打开中断命令
#define EXTI_CMD_EVENT_ENA     2    // 打开事件请求命令

// EXTI_Init() 初始化参数数据结构
typedef struct
{   
    INT8U  id;             // 中断id选择,EXTI0_ID~EXTI15_ID, EXTI16_PVD_ID, EXTI17_RTCAlarm_ID, EXTI18_USBWakeUp_ID, EXTI19_NETWakeUp_ID;
                           //            STM32F4XX芯片新增定义: EXTI20_USBHSWakeUp_ID, EXTI21_RTCTSE_ID, EXTI22_RTCWakeUp_ID    
    INT8U  Mode;           // 中断模式定义: EXTI_RISING, EXTI_FALLING, EXTI_RISING_FALLING 
    INT8U  IOx;            // 选择IO端口: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
}EXTI_PARA;

/*************************************************************************************/
//
// 					 外部中断/事件控制器(EXTI)硬件驱动函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: EXTI_Init;
*
* Description: 外部IO中断初始化函数;
* 
* Input:  *pPara, 中断初始化参数指针
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化这个函数没有启动中断, 需要调用EXTI_Ctrl()启动中断;
************************************************************************************/
INT32S EXTI_Init(EXTI_PARA *pPara);

/***********************************************************************************
* Function: EXTI_Ctrl;
*
* Description: 外部IO中断使能控制函数;
* 
* Input:  id,  中断索引：EXTI0_ID~EXTI15_ID, EXTI16_PVD_ID, EXTI17_RTCAlarm_ID, EXTI18_USBWakeUp_ID, EXTI19_NETWakeUp_ID;
*              STM32F4XX芯片新增定义: EXTI20_USBHSWakeUp_ID, EXTI21_RTCTSE_ID, EXTI22_RTCWakeUp_ID 
*
*		  Cmd: EXTI_CMD_DIS:       关闭中断和事件请求命令
*              EXTI_CMD_INT_ENA:   打开中断命令
*              EXTI_CMD_EVENT_ENA: 打开事件请求命令
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S EXTI_Ctrl(INT8U id, INT8U Cmd);
#endif

/***********************************************************************************/
// 文件结束
/***********************************************************************************/