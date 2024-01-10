/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: AT45DBXX.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责AT45DBXX系列FLASH读写驱动函数头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S AT45DBXX_Init(AT45DBXX_PARA *pPara);
*          2. INT32S AT45DBXX_WritePage(INT8U *p, INT32U page, INT32U count);
*          3. INT32S AT45DBXX_ReadPage(INT8U *p, INT32U page, INT32U count);
*          4. INT32S AT45DBXX_Write(INT8U *p, INT32U addr, INT32U len);
*          5. INT32S AT45DBXX_Read(INT8U *p, INT32U addr, INT32U len);
*          6. INT32S AT45DBXX_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __AT45DBXX_H
#define __AT45DBXX_H
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// SPI FLASH类型定义
#define W25QXX     0
#define AT45DBXX   1

// 芯片型号定义, 不可更改
#define  AT45DB081      0   // 1MB
#define  AT45DB161      1   // 2MB, 默认
#define  AT45DB321      2   // 4MB

// 器件标识ID 
#define  AT45DBXX_ID 0x1F

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// AT45DBXX_Ctrl() 控制命令定义
#define CMD_AT45DBXX_STATUS           0 	 // 读取AT45DBXX状态
#define CMD_AT45DBXX_PAGE_ERASE       1 	 // 擦除页 
#define CMD_AT45DBXX_BLOCK_ERASE      2 	 // 擦除4KB块, 8页 
#define CMD_AT45DBXX_SECTOR_ERASE     3 	 // 擦除128KB扇区, 32块，256页 
#define CMD_AT45DBXX_CHIP_ERASE       4 	 // 擦除整个芯片 
#define CMD_AT45DBXX_RDID             5 	 // 读取厂商及器件ID

// Flag 标志
#define AT45DBXX_TYPE_FLAG     0x4000   // AT45DBXX类型标志

//SPI Flash(AT45DBXX) 初始化参数定义  
typedef struct
{							 
	//INT8U  Type;          // 芯片芯片类型, 固定为1: AT45DBXX
    //INT8U  Model;         // 芯片型号
    INT16U Flag;          // 工作标志
    INT8U  SPI_ID;        // 选择SPI ID
	INT8U  CS_Pin;        // 片选管脚

	INT16U SectorSize;	  // Flash扇区大小(单位：字节) 
    INT32U SectorNum;	  // Flash扇区数量 
    INT32U FatFSSectorNum; // FatFS文件系统占用扇区数量
}AT45DBXX_PARA;  

/*************************************************************************************/
//
// 				AT45DBXX系列FLASH读写驱动函数
//
/*************************************************************************************/

/***********************************************************************************
* Function: AT45DBXX_Init;
*
* Description: AT45DBXX初始化函数;
*              
* Input:  *pPara, 初始化参数指针;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S AT45DBXX_Init(AT45DBXX_PARA *pPara);

/***********************************************************************************
* Function: AT45DBXX_WritePage;
*
* Description: 按页写入FLASH数据;
*              
* Input:  *p, 要写入数据的指针; page,写入flash数据的起始页; count, 要写入数据的页数;
*         page范围: 0~4095/8191(AT45DB161/AT45DB321); count范围：count + page<=4095/8191;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   每页是512字节;
************************************************************************************/
INT32S AT45DBXX_WritePage(INT8U *p, INT32U page, INT32U count);

/***********************************************************************************
* Function: AT45DBXX_ReadPage;
*
* Description: 按页读取FLASH的数据;
*              
* Input:  *p, 要读取数据存储区指针; page,读取flash数据的起始页;  count, 要读出数据的页数;
*         page/count+page范围: 0~4095/8191(AT45DB161/AT45DB321); 
*
* Output: *p, 数据存储区指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   每页512字节;
************************************************************************************/
INT32S AT45DBXX_ReadPage(INT8U *p, INT32U page, INT32U count);

/***********************************************************************************
* Function: AT45DBXX_Write;
*
* Description: 写入FLASH一段数据;
*              
* Input:  *p, 要写入数据的指针; addr,写入flash数据的起始地址;  len,要写入数据的长度;
*         addr地址范围: 0x000000~0x001fffff/0x003fffff(AT45DB161/AT45DB321);
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数不做地址范围范围检查,所以不要超过范围;
************************************************************************************/
INT32S AT45DBXX_Write(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: AT45DBXX_Read;
*
* Description: 读取FLASH的数据;
*              
* Input:  *p, 要读取数据存储区指针; addr, 内部FLASH起始地址;  len,要读取数据的长度;
*         addr地址范围: 0x000000~0x001fffff/0x003fffff(AT45DB161/AT45DB321);
*
* Output: *p, 数据存储区指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数不做地址范围范围检查,所以不要超过范围;
************************************************************************************/
INT32S AT45DBXX_Read(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: AT45DBXX_Ctrl;
*
* Description: SPI Flash命令控制;
* 
* Input:  Cmd,  SPI Flash控制命令：
*                CMD_AT45DBXX_PAGE_ERASE:      擦除页;  Para为页数
*                CMD_AT45DBXX_BLOCK_ERASE:     擦除4KB块, 8页; Para为块数
*                CMD_AT45DBXX_SECTOR_ERASE:    擦除128KB扇区, 32块，256页; Para为扇区数  
*                CMD_AT45DBXX_CHIP_ERASE:      擦除整个芯片;  Para为0
*                CMD_AT45DBXX_RDID:            读取厂商及器件ID; Para为0
*         Para，SPI Flash命令控制参数, 参考上面说明
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码; 有返回的命令返回相应参数;
*
* Note:   none;
************************************************************************************/
INT32S AT45DBXX_Ctrl(INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
