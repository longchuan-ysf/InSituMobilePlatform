/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: vars.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责整个程序框架公共全局变量引用头文件, 客户不可更改;
*
* Others: none;
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
#ifndef __VARS_H 
#define __VARS_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "config.h"	  
#include "modbus.h"
#include "net.h"

/************************************************************************************/
//  ISRHook.c文件打印输出信息缓存定义,不可修改
/************************************************************************************/
#if (DEBUG_ISRHOOK_EN>0)
typedef struct
{
    INT8U  len;                // 打印信息长度
    INT8U  buf[DEBUG_INFO_LEN];  // 打印输出信息缓存
}DEBUG_INFO;

extern DEBUG_INFO  DebugInfo;
#endif
/************************************************************************************/
//  ADC接收缓存,不可修改
/************************************************************************************/
#if (ADC_EN>0)
extern INT16S ADC_Buffer[ADC_AVGNUM][ADC_CHNUM];  // ADC1接收数据FIFO(缓存)
extern INT8U  AITab[];                            // AI输入采集顺序表
#endif

/************************************************************************************/
//  DAC1,DAC2发送缓存定义,不可修改
/************************************************************************************/
#if ((DAC1_EN>0)&&(DAC1_MODE>0))
extern INT16U  DAC1_Buffer[DAC1_TXBUF_SIZE];  // DAC1发送数据缓存
#endif
#if ((DAC2_EN>0)&&(DAC2_MODE>0))
extern INT16U  DAC2_Buffer[DAC2_TXBUF_SIZE];  // DAC2发送数据缓存
#endif

/************************************************************************************/
// UART1 发送接收缓存定义,不可修改
/************************************************************************************/
#if (UART1_EN > 0)
extern INT8U Uart1_RxBuffer[]; 	    // 接收数据缓存
extern INT8U  Uart1_TxBuffer[]; 	// 发送数据缓存
#endif

/************************************************************************************/
// UART2 发送接收缓存定义,不可修改
/************************************************************************************/
#if (UART2_EN > 0)
extern INT8U Uart2_RxBuffer[]; 	    // 接收数据缓存
extern INT8U Uart2_TxBuffer[]; 		// 发送数据缓存
#endif

/************************************************************************************/
// UART3 发送接收缓存定义,不可修改
/************************************************************************************/
#if (UART3_EN > 0)
extern INT8U Uart3_RxBuffer[]; 	    // 接收数据缓存
extern INT8U Uart3_TxBuffer[]; 		// 发送数据缓存
#endif

/************************************************************************************/
// UART4 发送接收缓存定义,不可修改
/************************************************************************************/
#if (UART4_EN > 0)
extern INT8U Uart4_RxBuffer[]; 	    // 接收数据缓存
extern INT8U Uart4_TxBuffer[]; 		// 发送数据缓存
#endif

/************************************************************************************/
// UART5 发送接收缓存定义,不可修改
/************************************************************************************/
#if (UART5_EN > 0)
extern INT8U Uart5_RxBuffer[]; 	    // 接收数据缓存
extern INT8U Uart5_TxBuffer[]; 		// 发送数据缓存
#endif

/************************************************************************************/
// UART6 发送接收缓存定义,不可修改
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
#if (UART6_EN > 0)
extern INT8U Uart6_RxBuffer[]; 	    // 接收数据缓存
extern INT8U Uart6_TxBuffer[]; 		// 发送数据缓存
#endif
#endif
/************************************************************************************/
//  FCLK 脉冲输入配置
/************************************************************************************/
// FCLK1缓存
#if ((FCLK1_EN > 0)&&((FCLK1_MODE == 2)||(FCLK1_MODE == 3)))
    #if (FCLK1CH1_EN > 0)
    extern INT16U FClk1CH1Buf[];
    #endif
    #if (FCLK1CH2_EN > 0)
    extern INT16U FClk1CH2Buf[];
    #endif
    #if (FCLK1CH3_EN > 0)
    extern INT16U FClk1CH3Buf[];
    #endif
    #if (FCLK1CH4_EN > 0)
    extern INT16U FClk1CH4Buf[];
    #endif
#endif
								 
// FCLK2缓存
#if ((FCLK2_EN > 0)&&((FCLK2_MODE == 2)||(FCLK2_MODE == 3)))
    #if (FCLK2CH1_EN > 0)
    extern INT16U FClk2CH1Buf[];
    #endif
    #if (FCLK2CH2_EN > 0)
    extern INT16U FClk2CH2Buf[];
    #endif
    #if (FCLK2CH3_EN > 0)
    extern INT16U FClk2CH3Buf[];
    #endif
    #if (FCLK2CH4_EN > 0)
    extern INT16U FClk2CH4Buf[];
    #endif
#endif

// FCLK3缓存
#if ((FCLK3_EN > 0)&&((FCLK3_MODE == 2)||(FCLK3_MODE == 3)))
    #if (FCLK3CH1_EN > 0)
    extern INT16U FClk3CH1Buf[];
    #endif
    #if (FCLK3CH2_EN > 0)
    extern INT16U FClk3CH2Buf[];
    #endif
    #if (FCLK3CH3_EN > 0)
    extern INT16U FClk3CH3Buf[];
    #endif
    #if (FCLK3CH4_EN > 0)
    extern INT16U FClk3CH4Buf[];
    #endif
#endif
																		
// FCLK4缓存
#if ((FCLK4_EN > 0)&&((FCLK4_MODE == 2)||(FCLK4_MODE == 3)))
    #if (FCLK4CH1_EN > 0)
    extern INT16U FClk4CH1Buf[];
    #endif    
    #if (FCLK4CH2_EN > 0)
    extern INT16U FClk4CH2Buf[];
    #endif
    #if (FCLK4CH3_EN > 0)
    extern INT16U FClk4CH3Buf[];
    #endif
    #if (FCLK4CH4_EN > 0)
    extern INT16U FClk4CH4Buf[];
    #endif
#endif

#if (MODULE_CLASS == STM32F407XX)
// FCLK5缓存
#if ((FCLK5_EN > 0)&&((FCLK5_MODE == 2)||(FCLK5_MODE == 3)))
    #if (FCLK5CH1_EN > 0)
    extern INT16U FClk5CH1Buf[];
    #endif    
    #if (FCLK5CH2_EN > 0)
    extern INT16U FClk5CH2Buf[];
    #endif
#endif

// FCLK6缓存
#if ((FCLK6_EN > 0)&&((FCLK6_MODE == 2)||(FCLK6_MODE == 3)))
    #if (FCLK6CH1_EN > 0)
    extern INT16U FClk6CH1Buf[];
    #endif    
    #if (FCLK6CH2_EN > 0)
    extern INT16U FClk6CH2Buf[];
    #endif
#endif

// FCLK7缓存
#if ((FCLK7_EN > 0)&&((FCLK7_MODE == 2)||(FCLK7_MODE == 3)))
    #if (FCLK7CH1_EN > 0)
    extern INT16U FClk7CH1Buf[];
    #endif    
    #if (FCLK7CH2_EN > 0)
    extern INT16U FClk7CH2Buf[];
    #endif
#endif

#endif

/************************************************************************************/
//  CAN1, CAN2 通信配置,不可修改
/************************************************************************************/
// CAN1, CAN2滤波器缓存定义
#if ((CAN1_EN > 0)||(CAN2_EN > 0)) 
extern INT32U CAN_FilterBuf[]; // 滤波器缓存
#endif		

// CAN1缓存定义
#if (CAN1_EN > 0)
extern CAN_BUF_MSG CAN1_RxBuffer[];     // CAN1接收缓存
extern CAN_BUF_MSG CAN1_TxBuffer[];     // CAN1发送缓存	 
#endif		

// CAN2缓存定义
#if (CAN2_EN > 0)
extern CAN_BUF_MSG CAN2_RxBuffer[];    // CAN2接收缓存
extern CAN_BUF_MSG CAN2_TxBuffer[];    // CAN2发送缓存
#endif 

/************************************************************************************/
// MODBUS 从机通信配置
/************************************************************************************/
#if (MODBUS_SLAVE_EN > 0)		
extern MODBUS_DATA ModbusData;                               // 缓存数据 
extern INT8U ModbusCoils[(MODBUS_MAX_COILS-1)/8 + 1];        // 输出线圈数组
extern INT8U ModbusDisInput[(MODBUS_MAX_DISINPUT-1)/8 + 1];  // 输入离散输入量数组
extern INT16U ModbusHoldReg[MODBUS_MAX_HOLDREG];             // 保持寄存器
extern INT16U ModbusInputReg[MODBUS_MAX_INPUTREG];           // 输入寄存器
extern MODBUS_PARA ModbusPara;                               // 参数定义  
#endif
/************************************************************************************/
// TCPIP(LWIP)协议栈配置
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))
#if (LWIP_EN > 0)
extern ETH_DMADESCTypeDef  DMARxDscrTab[];
extern ETH_DMADESCTypeDef  DMATxDscrTab[];
extern INT8U ETH_RxBuffer[ETH_RXBUFNB][ETH_MAX_RX_PACKET_SIZE];
extern INT8U ETH_TxBuffer[ETH_TXBUFNB][ETH_MAX_TX_PACKET_SIZE];
#endif
#endif


/************************************************************************************/
// USB设备 虚拟串口发送接收缓存定义,不可修改
/************************************************************************************/
#if (USB_VCP_EN > 0)
extern INT8U USB_RxBuffer[]; 	  // 接收数据缓存
#endif

/************************************************************************************/
//  SPI FLASH(W25QXX)缓存定义,不可修改
/************************************************************************************/
#if ((SPIFLASH_EN > 0)&&(SPIFLASH_TYPE == W25QXX)&&(SPIFLASH_MODE==1))
extern INT8U  W25QBuf[];   // 缓存
#endif

/************************************************************************************/
// NAND FLASH缓存配置
/************************************************************************************/
#if (NFLASH_EN > 0)
extern INT8U  NFlashBadBlkFlag[];                // NAND坏块标记
extern INT16U NFlashBadTab[];	                  // NAND坏块替换表
extern INT8U  NFlashBlkBuffer[NFLASH_BLOCK_SIZE][NFLASH_PAGE_SIZE] EXRAM;	 // NAND块缓存
extern INT8U  NFlashBlkSpareBuffer[NFLASH_BLOCK_SIZE][64] EXRAM;	       // NAND块缓存, 备用区域
#endif

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
