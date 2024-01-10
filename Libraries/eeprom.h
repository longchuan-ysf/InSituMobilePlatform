/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: eeprom.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是EEPROM读写驱动库程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S EEPROM_Init(EEPROM_PARA *pPara);
*          2. INT32S EEPROM_Read(INT16U addr, INT8U *p, INT16U len);
*          3. INT32S EEPROM_Write(INT16U addr, INT8U *p, INT16U len);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef _EEPROM_H 
#define _EEPROM_H 	 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"  


/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#define IIC_EEPROM_ADDR 	0xA0	// 器件地址标识

// EEPROM芯片型号定义, 说明：因为EEPROM芯片生产厂商不一样，型号也不一样，暂时只按ATMEL公司型号命名
#define	AT24C01		0		// 128 x 8bits
#define AT24C02 	1		// 256 x 8bits
#define AT24C04 	2		// 512 x 8bits
#define AT24C08 	3		// 1024 x 8bits
#define AT24C16 	4		// 2048 x 8bits
#define AT24C32 	5		// 4096 x 8bits
#define AT24C64 	6		// 8192 x 8bits
#define AT24C128 	7		// 16384 x 8bits
#define AT24C256 	8		// 32768 x 8bits
#define AT24C512 	9		// 65536 x 8bits

// I2C参数结构
typedef struct
{
    INT16U Flag;                // 参数标志
    INT8U  SDAPin;              // 定义I2C SDA管脚 
    INT8U  SCLPin;              // 定义I2C SCL管脚 
    INT8U  I2C_ID;              // 选择I2C接口索引: I2C1_ID 或者I2C2_ID 
    INT8U  I2CAddr;             // 器件地址标识
    INT8U  Model;               // 选择器件型号 
    INT32U Freq;                // 操作频率, 设置值必须小于400000Hz.
}EEPROM_PARA;
/************************************************************************************
//
//                 EEPROM读写驱动库程序
//
*************************************************************************************/
/***********************************************************************************
* Function: EEPROM_Init;
*
* Description: EEPROM初始化函数;
*              
* Input:  pPara, EEPROM参数指针;
*
* Output: none;
*
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S EEPROM_Init(EEPROM_PARA *pPara);				 

/***********************************************************************************
* Function: EEPROM_Read;
*
* Description: 从EEPROM的某个地址开始读取一段数据函数;
*              
* Input:  addr,EEPROM读取的起始地址; *P,读取数据存储的地址指针; len,要读取数据长度;
*
* Output: none;
*
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   因为AT24C64的地址:0x01E00~0x01FFF(最后512字节)作为驱动库IAP参数, 所以请不做操作这个地址范围,否则出错;
************************************************************************************/
INT32S EEPROM_Read(INT16U addr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: EEPROM_Write;
*
* Description: 从EEPROM的某个地址开始写入一段数据函数;
*              
* Input:  addr,EEPROM写入的起始地址;*P,写入数据存储的地址指针;len,要写入数据长度;
*
* Output: none;
*
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   因为AT24C64的地址:0x01E00~0x01FFF(最后512字节)作为驱动库IAP参数, 所以请不做操作这个地址范围,否则出错;
************************************************************************************/
INT32S EEPROM_Write(INT16U addr, INT8U *p, INT16U len);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/

