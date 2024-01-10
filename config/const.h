/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: const.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.1.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责整个软件全局常量定义, 用户不可更改;
*
* Others: 本文件的的任何定义都不可修改,否则出错!
*
* Function List:
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CONST_H 
#define __CONST_H 

/*************************************************************************************/
//  核心模块类别定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  STM32F107XX    0   // STM32F107XX系列核心模块
#define  STM32F103XX    1   // STM32F103XX系列核心模块
#define  STM32F407XX    2   // STM32F407XX系列核心模块
#define  STM32F417XX    3   // STM32F417XX系列核心模块

/*************************************************************************************/
//  核心模块型号定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  STM32F107VC  	0   // 原有的EMB8610I模块现在归为这个模块型号 
#define  STM32F103VE 	1
#define  STM32F103ZE  	2   // 就是EMB8612I 包含老版本V1.02和新版本V1.10 
#define  STM32F407VE  	3
#define  STM32F407ZE  	4
#define  STM32F407VG  	5
#define  STM32F407ZG  	6

/*************************************************************************************/
//  产品板型号定义, 以下已经定义绝对不能修改，但可以增加
/*************************************************************************************/
#define  EMB8600I    	1   // 中嵌凌云-工控板产品
#define  EMB8610IDK    	2   // 中嵌凌云-开发板产品
#define  EMB8612IA    	3	// 中嵌凌云-工控板产品
#define  EMB8616I    	4	// 中嵌凌云-工控板产品
#define  EMB8618I    	5	// 中嵌凌云-工控板产品
#define  EMB8626I    	6	// 中嵌凌云-工控板产品
#define  EMB8628I    	7	// 中嵌凌云-工控板产品

#define  STM32F107VC_DK 101	// 中嵌凌云-以STM32F107VC为核心模块的开发板
#define  STM32F103VE_DK 102	// 中嵌凌云-以STM32F103VE为核心模块的开发板
#define  STM32F103ZE_DK 103	// 中嵌凌云-以STM32F103ZE为核心模块的开发板
#define  STM32F407VE_DK 104	// 中嵌凌云-以STM32F407VE为核心模块的开发板
#define  STM32F407ZE_DK 105	// 中嵌凌云-以STM32F407ZE为核心模块的开发板
#define  STM32F407ZG_DK 106	// 中嵌凌云-以STM32F407ZG为核心模块的开发板


#define  EMB7XXXA       150	// 中嵌凌云-给客户定制产品

/*************************************************************************************/
//  常用数据类型定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  null    0
#define  NULL    0
#define  false   0
#define  true    1
#define  OFF     0
#define  ON      1
#define  CLOSE   0
#define  OPEN    1
#define  RSP_OK	 0xff

/*************************************************************************************/
//  数据类型定义, 以下定义绝对不能修改
/*************************************************************************************/
typedef unsigned char  INT8U;      // 8位无符号数                          
typedef signed   char  INT8S;      // 8位有符号数                         
typedef unsigned short INT16U;     // 16位无符号数                            
typedef signed   short INT16S;     // 16位有符号数                          
typedef unsigned int   INT32U;     // 32位无符号数                            
typedef signed   int   INT32S;     // 32位有符号数 
typedef unsigned long long INT64U; // 64位无符号数                            
typedef long long      INT64S;     // 64位有符号数                        
typedef float          FP32;       // 单精度浮点数                    
typedef double         FP64;       // 双精度浮点数 

typedef  void  (*FUNCTION_VOID)(void);  

// 32位数组合结构
typedef union 
{
    struct 
    {
        unsigned char c0;   // LSB
        unsigned char c1;   
        unsigned char c2;   
        unsigned char c3;   // MSB
    }chars;

    struct
    {
        unsigned short w0;  // LSW 
        unsigned short w1;  // MSW
    }ints;

    unsigned int d;         // 无符号32位
	int          s;         // 有符号32位
}INT32_TypeDef;

// 16位数组合结构
typedef union  
{
    struct 
    {
        unsigned char c0;   // LSB
		unsigned char c1;   // MSB 
    } chars;   
    unsigned short d;       // 无符号16位
    short          s;       // 有符号16位
}INT16_TypeDef;

#define EXRAM __attribute__ ((section ("RW_RAM1")))	   //用EXRAM将变量定义到外部RAM中, 只有在核心模块STM32F103ZE中使用, 例如: INT32U tmpreg  EXRAM;
#define CCRAM __attribute__ ((section ("CCM_IRAM")))   //用CCRAM将变量定义到核心RAM中, 只有在核心模块STM32F407XX中使用, 例如: INT32U tmpreg  CCRAM; 

/*************************************************************************************/
//  出错代码定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  ERR_OK   	 0	  // 正确
#define  ERR_TRUE    0	  // 成功
#define  ERR_FALSE   1	  // 失败
#define  ERR_TIMEOUT 2	  // 超时错误
#define  ERR_PARA	 3	  // 函数参数错误
#define  ERR_CRC     4	  // CRC校验错误
#define  ERR_HWID    5    // 硬件识别错误
#define  ERR_NOINIT  6    // 相关硬件未初始化
#define  ERR_NOFIND  7    // 没有发现
#define  ERR_BUFFULL 8    // 缓存已经满
#define  ERR_BUSY    9    // 忙
#define  ERR_DMABUSY 10   // DMA忙或被其它设备占用

/************************************************************************************/
//  板载存储器驱动盘符定义 
/************************************************************************************/
#define SPIFLASH_DISK    0    // SPI FLASH设置为逻辑驱动器0
#define SD_DISK          1    // SD卡设置为逻辑驱动器1;	
#define USB_DISK         2    // U盘设置为逻辑驱动器2;
#define NFLASH_DISK      3    // NAND FLASH设置为逻辑驱动器3;

/************************************************************************************/
//  驱动库等待标志定义 
/************************************************************************************/
#define SPI1_WAIT_FLAG    0x00000001
#define SPI2_WAIT_FLAG    0x00000002
#define SPI3_WAIT_FLAG    0x00000004


#endif

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
