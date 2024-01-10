/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: fsmc.h
* Project  : STM32F107VC/103VE/103ZE/407VE模块驱动库
* Processor: STM32F107VC/103VE/103ZE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是FSMC总线硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S FSMC_Init(FSMC_PARA *pPara);
*          2. INT16U FSMC_Read(INT16U addr);
*          3. void FSMC_Write(INT16U addr, INT16U val);
*          4. INT32S FSMC_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __FSMC_H
#define __FSMC_H
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"

// FSMC中断标志定义
//#define FSMC_ITBANK1_FLAG   0x01
//#define FSMC_ITBANK2_FLAG   0x02
//#define FSMC_ITBANK3_FLAG   0x04
//#define FSMC_ITBANK4_FLAG   0x08

// Flag定义
#define FSMC_SRAM_EN      0x0001   // 总线扩展RAM使能标志
#define FSMC_NFLASH_EN    0x0002   // 总线扩展NAND使能标志
#define FSMC_NET_EN       0x0004   // 总线扩展NET使能标志
#define FSMC_EXBUS_EN     0x0008   // 总线扩展引出使能标志
#define FSMC_NFLASH_ECCEN 0x0010   // Nand flash ECC使能标志
#define FSMC_NFLASH_ITFLAG  0x0020   // Nand flash 中断产生标志

// FSMC中断标志定义
#define FSMC_BANK2IT_FLAG   0x2000
#define FSMC_BANK3IT_FLAG   0x4000
#define FSMC_BANK4IT_FLAG   0x8000

// FSMC初始化参数定义  
typedef struct
{	
	INT16U Flag;          // 操作标志
    INT16U ECCSize;       // Nand Flash ECC页面大小
    INT32U SRAMSize;      // 外置SRAM容量
    INT8U  EXBusAddrSet;  // 外部总线地址建立时间(范围：0~15)：实际建立时间(EXBUS_ADDSET+1)个HCLK;
    INT8U  EXBusDataSet;  // 外部总线数据保持时间(范围：1~255)：实际保持时间：读(EXBUS_DATAST+3)个HCLK, 写(DATAST+1)个HCLK;
    INT8U  EXBusTurn;     // 外部总线恢复时间(范围：0~15)：实际恢复时间(EXBUS_TURN+1)个HCLK：1, 使能;  0, 关闭;
}FSMC_PARA;


// FSMC_Ctrl() 控制命令定义
#define CMD_FSMC_SRAM_TEST          0 	 // SRAM测试

/*************************************************************************************/
//
// 					FSMC硬件驱动函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: FSMC_Init;
*
* Description: FSMC初始化函数;
* 
* Input:  *pPara, 初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S FSMC_Init(FSMC_PARA *pPara);


/***********************************************************************************
* Function: FSMC_Read;
*
* Description: 读外部总线数据;
* 
* Input:  addr, 读数据地址, 范围0~31(针对基地址的相对地址);	
*
* Output: none;
*          		
* Return: 16位数据;
*
* Note:   none;
************************************************************************************/
INT16U FSMC_Read(INT16U addr);

/***********************************************************************************
* Function: FSMC_Write;
*
* Description: 向外部总线写数据;
* 
* Input:  addr, 写数据地址, 范围0~31(针对基地址的相对地址);	 val, 要写的16位数据
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void FSMC_Write(INT16U addr, INT16U val);

/***********************************************************************************
* Function: FSMC_Ctrl;
*
* Description: FSMC控制函数;
* 
* Input:  Cmd: CMD_FSMC_SRAM_TEST:  SRAM测试
*         Para: 默认0
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S FSMC_Ctrl(INT8U Cmd, INT32U Para);

#endif 