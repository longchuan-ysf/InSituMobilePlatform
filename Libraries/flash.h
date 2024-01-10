/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: flash.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是FLASH硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S Flash_Write(INT32U StartAddr, INT8U *p, INT16U len);
*          2. INT32S Flash_Read(INT32U StartAddr, INT8U *p, INT16U len);
*          3. INT32S Flash_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __FLASH_H 
#define __FLASH_H
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 函数常量定义
/************************************************************************************/

/************************************************************************************/
// Flash_Ctrl()控制指令定义
/************************************************************************************/
#define CMD_FLASH_UNLOCK         0   // FLASH解锁
#define CMD_FLASH_LOCK           1   // FLASH加锁
#define CMD_FLASH_PAGE_ERASE     2   // FLASH页擦除

// STM32F M4增加, 擦除扇区参数
#define FLASH_SECTOR_0     0  // Sector Number 0, 16KB   
#define FLASH_SECTOR_1     1  // Sector Number 1, 16KB   
#define FLASH_SECTOR_2     2  // Sector Number 2, 16KB   
#define FLASH_SECTOR_3     3  // Sector Number 3, 16KB   
#define FLASH_SECTOR_4     4  // Sector Number 4, 64KB   
#define FLASH_SECTOR_5     5  // Sector Number 5, 128KB  
#define FLASH_SECTOR_6     6  // Sector Number 6, 128KB   
#define FLASH_SECTOR_7     7  // Sector Number 7, 128KB 
#define FLASH_SECTOR_8     8  // Sector Number 8, 128KB  
#define FLASH_SECTOR_9     9  // Sector Number 9, 128KB   
#define FLASH_SECTOR_10    10 // Sector Number 10, 128KB  
#define FLASH_SECTOR_11    11 // Sector Number 11, 128KB 

/*************************************************************************************/
//
// 					 FLASH硬件驱动函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: Flash_Write;
*
* Description: 向FLASH写数据;
* 
* Input:  StartAddr, 写入FLASH的起始地址; p, 写数据指针; len, 数据长度
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   len应该是4的倍数;
************************************************************************************/
INT32S Flash_Write(INT32U StartAddr, INT8U *p, INT32U len);

/***********************************************************************************
* Function: Flash_Read;
*
* Description: 读取FLASH数据;
* 
* Input:  StartAddr, 读FLASH的起始地址; p, 读数据指针; len, 数据长度
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   len应该是4的倍数;
************************************************************************************/
INT32S Flash_Read(INT32U StartAddr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Flash_Ctrl;
*
* Description: FLASH控制函数;
* 
* Input:  Cmd: 控制命令：CMD_FLASH_UNLOCK, FLASH解锁
*                        CMD_FLASH_LOCK, FLASH加锁
*                        CMD_FLASH_PAGE_ERASE, FLASH页擦除(2KB)
*         Para: 控制参数; 
*                        控制命令CMD_FLASH_UNLOCK和CMD_FLASH_LOCK, Para设置为0;
*                        控制命令CMD_FLASH_PAGE_ERASE, Para为擦除的页或扇区编号;
*           
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   对于CMD_FLASH_PAGE_ERASE命令, STM32F1xx系列芯片: 按页(2KB)擦除;
*         STM32F4xx系列芯片: 按扇区(FLASH_SECTOR_0~FLASH_SECTOR_11)擦除;
************************************************************************************/
INT32S Flash_Ctrl(INT8U Cmd, INT32U Para);

#endif 

/***********************************************************************************/
// 文件结束
/***********************************************************************************/