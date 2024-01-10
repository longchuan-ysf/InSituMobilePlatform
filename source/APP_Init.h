/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: APP_Init.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件这个程序的总的硬件初始化函数头文件, 根据STM32F107VC_Conifg.h里的配置进行初始化
*
* Others: 参看API_Init()函数;
*
* Function List: void  API_Init(void);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __API_INIT_H 
#define __API_INIT_H 	 

#include "UserVars.h"
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
/***********************************************************************************
* Function: APP_ParaInit;
*
* Description: 恢复参数默认设置;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaInit(USER_VARS *p);
/***********************************************************************************
* Function: APP_ParaRead;
*
* Description: 读取存储参数函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaRead(USER_VARS *p); 
/***********************************************************************************
* Function: APP_ParaSave;
*
* Description: 存储参数函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaSave(USER_VARS *p);

/***********************************************************************************
* Function: API_Init;
*
* Description: 驱动库初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  API_Init(void);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/

