/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: NFlash.h
* Project  : STM32F107VC/103VE/103ZE/407VE模块驱动库
* Processor: STM32F107VC/103VE/103ZE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责Nand Flash读写驱动函数头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S NFlash_Init(NFLASH_PARA *pPara);
*          2. INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);
*          3. INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);
*          4. INT32U NFlash_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __NAND_FLASH_H 
#define __NAND_FLASH_H

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// ECC页面大小定义
#define NFLASH_ECCSIZE_256   256  // Nand Flash ECC页面大小: 256字节
#define NFLASH_ECCSIZE_512   512  // Nand Flash ECC页面大小: 512字节
#define NFLASH_ECCSIZE_1024  1024 // Nand Flash ECC页面大小: 1024字节
#define NFLASH_ECCSIZE_2048  2048 // Nand Flash ECC页面大小: 2048字节
#define NFLASH_ECCSIZE_4096  4096 // Nand Flash ECC页面大小: 4096字节
#define NFLASH_ECCSIZE_8192  8192 // Nand Flash ECC页面大小: 8192字节
    
// Flag工作标志定义
typedef struct
{
    INT16U  Flag;           // 工作标志
    INT16U  BlkNum;         // Nand Flash 总块数
    INT16U  PagePerBlk;     // Nand Flash 每个块包含页数 
    INT16U  PageSize;       // 页大小 
    INT16U  PageNum;        // 总页数
    INT16U  BadBlkNum;      // 坏块总数
    INT8U   *pBadBlkFlag;   // 坏块标记指针
    INT16U  *pBadTab;	    // 坏块替换表指针
    INT8U   *pBlkBuf;       // 块缓存指针
    INT8U   *pBlkSpareBuf;  // 块空闲区域缓存指针
}NFLASH_PARA;

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// NFlash_Ctrl() 控制命令定义
#define CMD_NFLASH_SYNC          0 	 // Nand Flash同步处理
#define CMD_NFLASH_BADBLK        1 	 // Nand Flash坏块处理, 调用完NFlash_APPInit()后, 必须调用NFlash_Ctrl(CMD_NFLASH_BADBLK, 0)处理坏块问题
#define CMD_NFLASH_STATUS        2 	 // 读取Nand Flash状态
#define CMD_NFLASH_SECTOR_COUNT  3   // 读取Nand Flash扇区数量
#define CMD_NFLASH_SECTOR_SIZE   4   // 读取Nand Flash扇区大小
#define CMD_NFLASH_BLOCK_SIZE    5   // 读取块大小(包含多少扇区数量)
#define CMD_NFLASH_RDID          6 	 // 读取厂商及器件ID, 返回器件ID指针,5个字节
#define CMD_NFLASH_FORMAT        7 	 // 格式化芯片

/*************************************************************************************/
//
// 				Nand Flash硬件驱动程序函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: NFlash_Init;
*
* Description: Nand Flash初始化函数;
*              
* Input:  *pPara, 初始化参数指针;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S NFlash_Init(NFLASH_PARA *pPara);

/***********************************************************************************
* Function: NFlash_ReadSector;
*
* Description: 按扇区读取Nand Flash的数据;
*              
* Input:  *p, 要读取数据存储区指针; sector,读取flash数据的起始扇区;  count, 要读出数据的扇区数;
*
* Output: *p, 数据存储区指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   每个扇区512字节, 本函数只能应用在FATFS的diskio.c中调用;
************************************************************************************/
INT32S NFlash_ReadSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: NFlash_WriteSector;
*
* Description: 按扇区写入Nand Flash数据;
*              
* Input:  *p, 要写入数据的指针; sector,写入flash数据的起始扇区; count, 要写入数据的扇区数;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   每个扇区512字节, 本函数只能应用在FATFS的diskio.c中调用;
************************************************************************************/
INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: NFlash_Ctrl;
*
* Description: NFlash控制函数;
* 
* Input:  Cmd,  控制命令:  
*               CMD_NFLASH_SYNC:          Nand Flash同步处理
*               CMD_NFLASH_BADBLK:        Nand Flash坏块处理, 调用完NFlash_APPInit()后, 必须调用NFlash_Ctrl(CMD_NFLASH_BADBLK, 0)处理坏块问题
*               CMD_NFLASH_STATUS:        读取Nand Flash状态
*               CMD_NFLASH_SECTOR_COUNT:  读取Nand Flash扇区数量
*               CMD_NFLASH_SECTOR_SIZE:   读取Nand Flash扇区大小
*               CMD_NFLASH_BLOCK_SIZE:    读取块大小(包含多少扇区数量)
*               CMD_NFLASH_RDID:          读取厂商及器件ID, 返回器件ID指针,5个字节
*               CMD_NFLASH_FORMAT:        格式化芯片
*         Para，命令控制参数;
*
* Output: none;
*          		
* Return: 根据命令不同, 返回不同数据; ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32U NFlash_Ctrl(INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
