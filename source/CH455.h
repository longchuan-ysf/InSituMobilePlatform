/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: CH455.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是CH455读写驱动库程序头文件;
*
* Others: none;
*
* Function List: 
*          1. void CH455_Read(void);
*          2. INT8U CH455_Read(void);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CH455_H 
#define __CH455_H

#include "const.h"
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
// 在EMB8628I中JP4接入4*4按键: 接入L1-L4,C1-C4
// 按键值定义
#define	 KEY_1				0x1F
#define	 KEY_2				0x1E
#define	 KEY_3				0x1D
#define	 KEY_A				0x1C
#define	 KEY_4				0x17
#define	 KEY_5				0x16
#define	 KEY_6				0x15
#define	 KEY_B				0x14
#define	 KEY_7				0x0F
#define	 KEY_8				0x0E
#define	 KEY_9				0x0D
#define	 KEY_C				0x0C
#define	 KEY_X				0x07
#define	 KEY_0				0x06
#define	 KEY_J				0x05
#define	 KEY_D				0x04

#define	 KEY_NO				0x00  // 无按键

// CH455控制方式
#define CH455_MODE_I2C    0	 // CH455用I2C总线控制
#define CH455_MODE_IO	  1	 // CH455用IO(模拟I2C总线)控制

//#define I2C_ID            I2C3_ID  // 选择I2C ID 

// 请根据电路图在这里定义IO管脚
//#define KEY_SCL         PA8
//#define KEY_SDA         PC9
//#define K_INT           PD3 // CH455中断线IO定义

// CH455初始化参数结构
typedef struct
{   
    INT8U  Mode;           // 工作标志
    INT8U  I2C;             // I2C选择ID
    INT8U  SDAPin;         // SDA管脚
    INT8U  SCLPin;         // SCL管脚
    INT8U  INTPin;         // INT中断管脚
}CH455_PARA;

/************************************************************************************
//
//                 按键硬件驱动程序
//
*************************************************************************************/

/***********************************************************************************
* Function: CH455_Init;
*
* Description: CH455初始化函数;
*           
* Input:  *pPara: 初始化函数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CH455_Init(CH455_PARA *pPara);

/***********************************************************************************
* Function: CH455_Read;
*
* Description: CH455读取按键值函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: 按键值4-7/12-15/20-23/28-31/36-39/44-47/52-55或0(无按键按下);
*
* Note:   none;
************************************************************************************/
INT8U CH455_Read(void);
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/

