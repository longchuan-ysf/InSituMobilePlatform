/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: W25QXX.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责W25QXX系列FLASH读写驱动函数头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S W25QXX_Init(W25QXX_PARA *pPara);
*          2. INT32S W25QXX_Write(INT8U *p, INT32U addr, INT16U len);
*          3. INT32S W25QXX_WritePage(INT8U *p,  INT32U addr,  INT16U len);
*          4. INT32S W25QXX_WriteSector(INT8U *p, INT32U Sector, INT32U count);
*          5. INT32U W25QXX_Read(INT8U *p, INT32U addr, INT32U len);
*          6. INT32S W25QXX_ReadSector(INT8U *p, INT32U Sector, INT32U count);
*          7. INT32S W25QXX_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __W25QXX_H
#define __W25QXX_H

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// SPI FLASH类型定义
#define W25QXX     0
#define AT45DBXX   1

// 芯片型号定义, 不可更改
#define  W25Q80         0   // 1MB
#define  W25Q16         1   // 2MB
#define  W25Q32         2   // 4MB
#define  W25Q64         3   // 8MB, 默认
#define  W25Q128        4   // 16MB

// 器件标识ID 
#define  W25QXX_ID      0xEF
#define  GD25QXX_ID     0xC8

// Flag 标志
#define W25QXX_TYPE_FLAG     0x8000   // W25QXX类型标志

//SPI Flash(W25QXX) 初始化参数定义  
typedef struct
{							 
	//INT8U  Type;           // 芯片芯片类型, 固定为0: W25QXX
    //INT8U  Model;          // 芯片型号
    INT16U Flag;           // 工作标志
    INT8U  SPI_ID;         // 选择SPI ID
	INT8U  CS_Pin;         // 片选管脚
    INT16U SectorSize;	   // Flash扇区大小(单位：字节) 
    INT32U SectorNum;	   // Flash扇区数量 
    INT32U FatFSSectorNum; // FatFS文件系统占用扇区数量
    INT8U  *pBuf;          // FatFS接口函数缓存
}W25QXX_PARA;  

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// W25QXX_Ctrl() 控制命令定义
#define CMD_W25QXX_SYNC               0 	 // 同步处理(回写缓存), 只能在FATFS的diskio.c中调用
#define CMD_W25QXX_INIT               1 	 // W25QXX初始化, 只能在FATFS的diskio.c中调用
#define CMD_W25QXX_STATUS             2 	 // 读取W25QXX状态,只能在FATFS的diskio.c中调用

#define CMD_W25QXX_SECTOR_ERASE       3 	 // 擦除扇区
#define CMD_W25QXX_BLOCK32KB_ERASE    4 	 // 擦除32KB块
#define CMD_W25QXX_BLOCK64KB_ERASE    5 	 // 擦除64KB块
#define CMD_W25QXX_CHIP_ERASE         6 	 // 擦除整个芯片
#define CMD_W25QXX_RDID               7 	 // 读取厂商及器件ID
#define CMD_W25QXX_POWERDOWN          8 	 // 进入掉电模式
#define CMD_W25QXX_WAKEUP             9 	 // 唤醒

/************************************************************************************
//
//                 W25QXX系列FLASH读写驱动库函数
//
*************************************************************************************/

/***********************************************************************************
* Function: W25QXX_Init;
*
* Description: W25QXX初始化函数;
*              
* Input:  *pPara, 初始化参数指针;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   如果返回错误请检查参数以及所选择的SPI总线是否初始化;
************************************************************************************/
INT32S W25QXX_Init(W25QXX_PARA *pPara);

/***********************************************************************************
* Function: W25QXX_Write;
*
* Description: 写入FLASH一段数据;
*              
* Input:  *p, 要写入数据的指针; addr, 写入flash数据的起始地址;  len,要写入数据的长度;
*         addr地址范围: W25Q80, 0x000000~0x000fffff; W25Q16, 0x000000~0x001fffff;
*                       W25Q32, 0x000000~0x003fffff; W25Q64, 0x000000~0x007fffff;
*                       W25Q128, 0x000000~0x00ffffff; 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数不做地址范围范围检查,所以不要超过范围;
************************************************************************************/
INT32S W25QXX_Write(INT8U *p, INT32U addr, INT16U len);

/***********************************************************************************
* Function: W25QXX_WritePage;
*
* Description: 按页写入FLASH数据;
*              
* Input:  *p, 要写入数据的指针; addr, 每页的起始起始地址;  len, 要写入数据长度;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   addr必须是256的整数倍, len范围必须是1-256;
************************************************************************************/
INT32S W25QXX_WritePage(INT8U *p,  INT32U addr,  INT16U len);

/***********************************************************************************
* Function: W25QXX_Read;
*
* Description: 读取FLASH的数据;
*              
* Input:  *p, 要读取数据存储区指针; addr, 内部FLASH起始地址;  len,要读取数据的长度;
*         addr地址范围: W25Q80, 0x000000~0x000fffff; W25Q16, 0x000000~0x001fffff;
*                       W25Q32, 0x000000~0x003fffff; W25Q64, 0x000000~0x007fffff;
*                       W25Q128, 0x000000~0x00ffffff; 
*
* Output: *p, 数据存储区指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数不做地址范围范围检查,所以不要超过范围;
************************************************************************************/
INT32U W25QXX_Read(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: W25QXX_WriteSector;
*
* Description: 按扇区写入FLASH数据;
*              
* Input:  *p, 要写入数据的指针; sector,写入flash数据的起始扇区序号;  count, 要写入扇区数量;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   扇区大小为512字节, 本函数只能应用在FATFS的diskio.c中调用;
************************************************************************************/
INT32S W25QXX_WriteSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: W25QXX_ReadSector;
*
* Description: 按扇区读取FLASH的数据;
*              
* Input:  *p, 要读取数据存储区指针; sector,读取Flash数据的起始扇区;  count, 要读取的扇区数;
*
* Output: *p, 数据存储区指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   扇区大小为512字节, 本函数只能应用在FATFS的diskio.c中调用;
************************************************************************************/
INT32S W25QXX_ReadSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: W25QXX_Ctrl;
*
* Description: W25QXX命令控制;
* 
* Input:  Cmd,  W25QXX控制命令：
*                CMD_W25QXX_SYNC:            同步处理(回写缓存), 只能在FATFS的diskio.c中调用
*                CMD_W25QXX_INIT: 	         W25QXX初始化, 只能在FATFS的diskio.c中调用
*                CMD_W25QXX_STATUS:          读取W25QXX状态,只能在FATFS的diskio.c中调用
*                CMD_W25QXX_SECTOR_ERASE:    擦除扇区; Para, 扇区序号 
*                CMD_W25QXX_BLOCK32KB_ERASE: 擦除32KB块; Para, 32KB块序号 
*                CMD_W25QXX_BLOCK64KB_ERASE: 擦除64KB块; Para, 64KB块序号
*                CMD_W25QXX_CHIP_ERASE:      擦除整个芯片; Para, 为0
*                CMD_W25QXX_RDID:            读取厂商及器件ID; Para, 为0
*                CMD_W25QXX_POWERDOWN:       进入掉电模式; Para, 为0
*                CMD_W25QXX_WAKEUP:          唤醒; Para, 为0	
*
*         Para，W25QXX命令控制参数, 参看上面说明
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码; 有返回的命令返回相应参数;
*
* Note:   none;
************************************************************************************/
INT32S W25QXX_Ctrl(INT8U Cmd, INT32U Para);

#endif 

