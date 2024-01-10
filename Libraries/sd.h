/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: sd.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是FATFS文件系统SD卡接口驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S SD_Init(SD_PARA *pPara);
*          2. INT8U  SD_Read(INT8U *p, INT32U sector, INT8U count);
*          3. INT8U  SD_Write(INT8U *p, INT32U sector, INT8U count);
*          4. INT32S SD_Ctrl(INT8U Cmd,  INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __SD_H
#define __SD_H
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// 常量定义
/************************************************************************************/
#define SD_NOINIT		0x01	// 磁盘驱动器还没有被初始化标志
#define SD_NODISK		0x02	// 没有SD卡标志
#define SD_PROTECT	    0x04	// 写保护标志 
#define SD_POWER		0x08	// 打开电源标志

#define SD_SPI_MODE     0  // SD卡: SPI操作模式
#define SD_SDIO_MODE    1  // SD卡: SDIO操作模式

// SD卡控制管脚参数结构 
typedef struct
{
    INT8U  INR;   // 插入卡管脚定义
    INT8U  WP;    // 写保护管脚定义
    INT8U  CS;    // 片选管脚定义
    INT8U  CPWR;  // 电源控制管脚定义
}SDCTRL_PIN;

// SD卡初始化参数定义  
typedef struct
{	
    INT16U Flag;          // 工作标志
    INT8U  Mode;          // SD操作模式
    INT8U  SPIx_ID;       // 选择SPI ID
	SDCTRL_PIN Pin;       // SD卡控制管脚
}SD_PARA;


// SD_Ctrl()控制函数命令定义
#define CMD_SD_SYNC          0  // SD检测同步处理: 检测SD是否插入或拔出, 插入则打开电源并初始化, 拔出则关闭电源
#define CMD_SD_STATUS        1  // 读取SD卡状态
#define CMD_SD_SECTOR_COUNT  2  // 读取SD卡扇区数量
#define CMD_SD_SECTOR_SIZE   3  // 读取SD卡扇区大小
#define CMD_SD_TYPE          4  // 读取SD卡类型

/*************************************************************************************/
//
// 				FATFS文件系统SD卡接口驱动程序;
//
/*************************************************************************************/

/***********************************************************************************
* Function: SD_Init;
*
* Description: SD卡初始化函数;
*              
* Input:  *pPara 初始化参数;  
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SD_Init(SD_PARA *pPara);

/***********************************************************************************
* Function: SD_Read;
*
* Description: FatFS接口读取SD卡扇区数据函数;
*              
* Input:  *p, 读取数据缓存指针;
*         sector, 读取扇区起始序号  
*         count, 读取扇区数量 (1..255)    
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U SD_Read(INT8U *p, INT32U sector, INT8U count);

/***********************************************************************************
* Function: SD_Write;
*
* Description: FatFS接口写入SD卡扇区数据函数;
*              
* Input:  *p, 写入数据缓存指针;
*         sector, 写入扇区起始序号  
*         count, 写入扇区数量 (1..255)  
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U SD_Write(INT8U *p, INT32U sector, INT8U count);

/***********************************************************************************
* Function: SD_Ctrl;
*
* Description: FatFS接口SD卡控制函数;
*              
* Input:  Cmd,  控制命令, 如下:
*         CMD_SD_SYNC:           SD检测同步处理: 检测SD是否插入或拔出, 插入则打开电源并初始化, 拔出则关闭电源
*         CMD_SD_STATUS:         读取SD卡状态
*         CMD_SD_SECTOR_COUNT:   读取SD卡扇区数量
*         CMD_SD_BLOCK_SIZE:     读取SD卡块大小
*         CMD_SD_SECTOR_SIZE:    读取SD卡扇区大小
*         CMD_SD_TYPE:           读取SD卡类型
*         Para, 参数,默认0,暂时未用
*
* Output: none;
*
* Return: 根据不同命令返回不同的值
*         当Cmd是CMD_SD_SYNC和CMD_SD_STATUS时:
*         返回SD卡状态:   
*         STA_NOINIT(bit0=1)： SD卡没有初始化 
*         STA_NODISK(bit1=1)： 没有发现SD卡 
*         STA_PROTECT(bit2=1)：SD卡写保护 
*
* Note:   none;
************************************************************************************/
INT32S SD_Ctrl(INT8U Cmd,  INT32U Para);

#endif
