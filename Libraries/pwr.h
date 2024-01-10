/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: pwr.c
* Project  : STM32F107VC/103VE/103ZE/407VE模块驱动库
* Processor: STM32F107VC/103VE/103ZE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是PWR(电源管理)硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S PWR_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __PWR_H 
#define __PWR_H 

#include "const.h"
#include "config.h"
/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// PWR命令定义
#define CMD_PWR_BackupAccess       0  // 使能或禁止写入RTC和后备寄存器: 参数Para>0,使能; 参数Para=0, 禁止;
#define CMD_PWR_PVD	               1  // 使能或禁止电源电压监测器(PVD): 参数Para>0,使能; 参数Para=0, 禁止;
#define CMD_PWR_PVDLevelConfig	   2  // 选择电源电压监测器的电压阀值
#define CMD_PWR_WakeUpPin          3  // 使能或禁止WKUP管脚用于将CPU从待机模式唤醒功能: 参数Para>0,使能; 参数Para=0, 禁止;
// Regulator_state_is_STOP_mode
#define CMD_PWR_Regulator_ON	   4  // 在停机模式下电压调压器开启
#define CMD_PWR_Regulator_LowPower 5  // 在停机模式下电压调压器处于低功耗模式

// SLEEP_mode_entry 
#define CMD_PWR_SLEEPEntry_WFI     6  // 应用WFI指令进入睡眠模式, Request Wait For Interrupt 
#define CMD_PWR_SLEEPEntry_WFE     7  // 应用WFE指令进入睡眠模式, Request Wait For Event

// STOP_mode_entry 
#define CMD_PWR_STOPEntry_WFI      8  // 应用WFI指令进入停止模式, Request Wait For Interrupt 
#define CMD_PWR_STOPEntry_WFE      9  // 应用WFE指令进入停止模式, Request Wait For Event

#define CMD_PWR_EnterSTANDBYMode   10  // Enters STANDBY mode
//#define CMD_PWR_GetFlagStatus	   9  // 得到PWR状态


// 电源电压监测器的电压阀值
#if (MODULE_CLASS == STM32F407XX)    // STM32F40X_M4 MCU
    #define PWR_PVDLevel_2V0          ((INT32U)0x00000000)  // 2.0V 
    #define PWR_PVDLevel_2V1          ((INT32U)0x00000020)  // 2.1V
    #define PWR_PVDLevel_2V3          ((INT32U)0x00000040)  // 2.2V
    #define PWR_PVDLevel_2V5          ((INT32U)0x00000060)  // 2.5V
    #define PWR_PVDLevel_2V6          ((INT32U)0x00000080)  // 2.6V
    #define PWR_PVDLevel_2V7          ((INT32U)0x000000A0)  // 2.7V
    #define PWR_PVDLevel_2V8          ((INT32U)0x000000C0)  // 2.8V
    #define PWR_PVDLevel_2V9          ((INT32U)0x000000E0)  // 2.9V
    
    
    //PWR_SLEEP_mode_entry PWR SLEEP mode entry
    #define PWR_SLEEPENTRY_WFI              ((INT8U)0x01)
    #define PWR_SLEEPENTRY_WFE              ((INT8U)0x02)

/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI               ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE               ((uint8_t)0x02)

#else // STM32F10X_M3 MCU
    #define PWR_PVDLevel_2V2          ((INT32U)0x00000000)  // 2.2V 
    #define PWR_PVDLevel_2V3          ((INT32U)0x00000020)  // 2.3V
    #define PWR_PVDLevel_2V4          ((INT32U)0x00000040)  // 2.4V
    #define PWR_PVDLevel_2V5          ((INT32U)0x00000060)  // 2.5V
    #define PWR_PVDLevel_2V6          ((INT32U)0x00000080)  // 2.6V
    #define PWR_PVDLevel_2V7          ((INT32U)0x000000A0)  // 2.7V
    #define PWR_PVDLevel_2V8          ((INT32U)0x000000C0)  // 2.8V
    #define PWR_PVDLevel_2V9          ((INT32U)0x000000E0)  // 2.9V
#endif



// PWR_Flag 
//#define PWR_FLAG_WU               ((INT32U)0x00000001)
//#define PWR_FLAG_SB               ((INT32U)0x00000002)
//#define PWR_FLAG_PVDO             ((INT32U)0x00000004)
 
/*************************************************************************************/
//
// 					 PWR硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: PWR_Ctrl;
*
* Description: 芯片电源控制函数;
*              
* Input:  Cmd,  PWR控制命令;
*         Para，PWR控制参数;
*
* Output: none;
*
* Return: ERR_TRUE, 正确; ERR_FALSE, 出错;
*
* Note:   none;
************************************************************************************/
INT32S PWR_Ctrl(INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/



