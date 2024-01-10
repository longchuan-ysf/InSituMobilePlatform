/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: sysint.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是系统驱动库程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S SysLib_Init(SYSLIB_PARA *pPara);
*          2. INT32S SysLib_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef  __SYSINT
#define  __SYSINT
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include    "const.h"
#include    "config.h"

/************************************************************************************/
// 外部或内部晶振频率 
/************************************************************************************/
// STM32F10X系列内部振荡器时钟频率
#define OSC_HSI_8MHZ      8000000

// STM32F40X系列内部振荡器时钟频率
#define OSC_HSI_16MHZ     16000000

/************************************************************************************/
// STM32F1_M3 系统时钟定义 
/************************************************************************************/
// 时钟定义
#define SYSCLK_8MHZ     8000000
#define SYSCLK_11MHZ    11059200
#define SYSCLK_12MHZ    12000000
#define SYSCLK_24MHZ    24000000 
#define SYSCLK_25MHZ    25000000 
#define SYSCLK_36MHZ    36000000 
#define SYSCLK_48MHZ    48000000
#define SYSCLK_56MHZ    56000000
#define SYSCLK_60MHZ    60000000
#define SYSCLK_72MHZ    72000000

/************************************************************************************/
// STM32F4_M4系统时钟定义
/************************************************************************************/
#define SYSCLK_24MHZ    24000000
#define SYSCLK_30MHZ    30000000
#define SYSCLK_36MHZ    36000000
#define SYSCLK_42MHZ    42000000
#define SYSCLK_48MHZ    48000000
#define SYSCLK_60MHZ    60000000
#define SYSCLK_72MHZ    72000000
#define SYSCLK_84MHZ    84000000
#define SYSCLK_96MHZ    96000000
#define SYSCLK_120MHZ   120000000
#define SYSCLK_144MHZ   144000000
#define SYSCLK_168MHZ   168000000


#define SYSCLK_150MHZ   150000000
#define SYSCLK_100MHZ   100000000
#define SYSCLK_50MHZ    50000000


// IAP中断向量表地址定义
#define NVIC_VECTOR_TABLE_ADDR  0x4000     // 不可修改

// 标志位定义
#define SYS_OS_FLAG             0x00000001 // 操作系统使能标志
#define SYS_NVIC_VECTORTAB_FLAG 0x00000002 // 设置新的中断向量表使能标志 
#define SYS_TICK_FLAG           0x00000004 // 设置系统定时器使能标志 
#define SYS_CLK_HSI_FLAG        0x00000008 // 选择内部时钟晶振标志
#define SYS_CLK_HSE_FLAG        0x00000010 // 选择外部时钟晶振标志

#define SYS_DEBUG_LIB_FLAG      0x01000000 // 驱动库其它调试输出标志 
#define SYS_DEBUG_SD_FLAG       0x02000000 // 驱动库SD卡调试输出标志 
#define SYS_DEBUG_USB_FLAG      0x04000000 // 驱动库USB部分调试输出标志 
#define SYS_DEBUG_MODBUS_FLAG   0x08000000 // 驱动库MODBUS调试输出标志 
#define SYS_DEBUG_NET_FLAG      0x10000000 // 驱动库网络调试输出标志 
#define SYS_DEBUG_NFLASH_FLAG   0x20000000 // 驱动库NAND FLASH调试输出标志 


// SYSLIB参数结构 
typedef struct
{
    INT32U Flag;            // 标志
    INT8U  ModuleType;      // 模块类型
    INT8U  DebugUart;       // 选择printf函数输出Uart
    INT16U VectorTableAddr; // 中断向量表地址 
    INT32U OscClk;          // 外部或内部晶振频率
    INT32U SysClk;          // 系统时钟频率
    INT16U Tick;            // 系统定时器定时时间, 单位ms
}SYSLIB_PARA;

// SysLib_Ctrl()控制参数
#define CMD_SYSLIB_RESET           0  // 系统复位(相当于板子加电重启新启动)
#define CMD_SYSLIB_READ_VERSION    1  // 读取驱动库版本
#define CMD_SYSLIB_READ_DATE       2  // 读取驱动库编译生成日期
#define CMD_MCO1                   3  // MCO1输出控制
#if (MODULE_CLASS == STM32F407XX)
#define CMD_MCO2                   4  // MCO2输出控制
#endif
#define CMD_SYSLIB_READ_MCUID      5  // 读取MCU唯一的ID值: 96位，12字节


// MCO1/2 参数Para定义
#define MCO_OUT_ENA               0x8000  // MCO1/2 输出使能, bit15=1;
#define MCO_OUT_DIS               0x0000  // MCO1/2 输出关闭, bit15=0;

#if (MODULE_CLASS == STM32F407XX) //STM32F40X芯片用以下参数 
// MCO1/2输出参数定义
#define MCO_DIV1                  0x0010  // MCO1/2 无分频, bit[6,5,4]= 1;
#define MCO_DIV2                  0x0020  // MCO1/2 2分频,  bit[6,5,4]= 2;
#define MCO_DIV3                  0x0030  // MCO1/2 3分频,  bit[6,5,4]= 3;
#define MCO_DIV4                  0x0040  // MCO1/2 4分频,  bit[6,5,4]= 4;
#define MCO_DIV5                  0x0050  // MCO1/2 5分频,  bit[6,5,4]= 5;

// MCO1输出信号选择(管脚PA8输出)
#define MCO1_HSI                  0x0000  // MCO1输出HSI, bit[1,0] = 0;
#define MCO1_LSE                  0x0001  // MCO1输出LSE, bit[1,0] = 1;
#define MCO1_HSE                  0x0002  // MCO1输出HSE, bit[1,0] = 2;
#define MCO1_PLL                  0x0003  // MCO1输出PLL, bit[1,0] = 3;

// MCO2输出信号选择(管脚PC9输出)
#define MCO2_SYSCLK               0x0000  // MCO2输出系统时钟, bit[1,0] = 0;
#define MCO2_PLLI2S               0x0001  // MCO2输出PLLI2S,   bit[1,0] = 1;
#define MCO2_HSE                  0x0002  // MCO2输出HSE,      bit[1,0] = 2;
#define MCO2_PLL                  0x0003  // MCO2输出PLL,      bit[1,0] = 3;

#else  //STM32F10X芯片用以下参数 
#define MCO1_SYSCLK               0x0001  // MCO1输出系统时钟,  bit[1,0] = 0;
#define MCO1_HSI                  0x0001  // MCO1输出PLLI2S,   bit[1,0] = 1;
#define MCO1_HSE                  0x0002  // MCO1输出HSE,      bit[1,0] = 2;
#define MCO1_PLL_DIV2             0x0003  // MCO1输出PLL,      bit[1,0] = 3;
#endif

/************************************************************************************
//
//                 系统驱动库程序
//
*************************************************************************************/

/***********************************************************************************
* Function: SysLib_Init;
*
* Description: 系统驱动库初始化函数;
* 
* Input: *pPara, 初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SysLib_Init(SYSLIB_PARA *pPara);

/***********************************************************************************
* Function: SysLib_Ctrl;
*
* Description: 系统控制函数;
* 
* Input:  Cmd: 控制命令：CMD_SYSLIB_RESET, 系统复位, Para默认0;
*                        CMD_SYSLIB_READ_VERSION,  读取驱动库版本, Para默认0;
*                        CMD_SYSLIB_READ_DATE, 读取驱动库编译生成日期, Para默认0;
*                        CMD_MCO1,CMD_MCO2: MCO1/2输出控制, Para参看: MCO1/2参数Para定义
*                        CMD_SYSLIB_READ_MCUID: 读取MCU唯一的ID值: 96位，12字节, Para默认0;
*         Para: 控制参数 
*
* Output: none;
*          		
* Return: 命令：CMD_SYSLIB_RESET/CMD_MCO1/CMD_MCO2: 返回：ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*               CMD_SYSLIB_READ_DATE/CMD_SYSLIB_READ_MCUID: 返回字符串指针/12字节指针
*               CMD_SYSLIB_READ_VERSION：返回版本数值
*
* Note:   none;
************************************************************************************/
INT32S SysLib_Ctrl(INT8U Cmd, INT32U Para);

#endif                                                          
