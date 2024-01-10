/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: can.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是CAN硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S CAN_Init(INT8U id,  CAN_PARA *pPara, CAN_FILTER_PARA *pFilter);
*          2. INT32S CAN_FilterInit(CAN_FILTER_PARA *pFilter);
*          3. INT32S CAN_Write(INT8U id, CAN_TX_MSG *pTxMsg);
*          4. INT32S CAN_Read(INT8U id, CAN_RX_MSG *pRxMsg);
*          5. INT32S CAN_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CAN_H 
#define __CAN_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// CAN索引定义
#define CAN1_ID             0
#define CAN2_ID             1 

// 标识符选择 
#define CAN_STD_ID          0  // 使用标准标识符 
#define CAN_EXT_ID          1  // 使用扩展标识符

// 远程发送请求 
#define CAN_RTR_DATA        0  // 数据帧
#define CAN_RTR_REMOTE      1  // 远程帧 

// CAN发送数据帧结构定义  
typedef struct
{
    INT32U ID;      // 标准帧或扩展帧标识: 标准帧范围：0~0x7FF, 扩展帧范围：0~0x1FFFFFFF;
    INT8U  IDE;     // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
    INT8U  RTR;     // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 
    INT8U  DLC;     // 数据长度, 范围：0~8
    INT8U  Data[8]; // 数据, 范围：0~0xFF 
}CAN_TX_MSG;

// CAN接收数据帧结构定义  
typedef struct
{
    INT32U ID;      // 标准帧或扩展帧标识: 标准帧范围：0~0x7FF, 扩展帧范围：0~0x1FFFFFFF;
    INT8U  IDE;     // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
    INT8U  RTR;     // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 
    INT8U  DLC;     // 数据长度, 范围：0~8
    INT8U  Data[8]; // 数据, 范围：0~0xFF 
    INT8U  FMI;     // 过滤器匹配序号, 范围：0~0xFF
}CAN_RX_MSG;

// CAN缓存数据帧结构定义  
typedef struct
{
    INT32U IR;     // 帧类型及ID
    INT32U DTR;    // 数据长度
    INT32U DLR;    // 数据1-4字节 
    INT32U DHR;    // 数据5-8字节
}CAN_BUF_MSG;

// CAN滤波器设置数据帧结构定义  
//typedef struct
//{
//	INT32U Id;      // 标准帧或扩展帧标识: 标准帧范围：0~0x7FF, 扩展帧范围：0~0x1FFFFFFF;
//    INT8U  IDE;     // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
//    INT8U  RTR;     // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 
//    INT8U  Addr;    // 滤波器地址 ,范围：0-27
//}CAN_FILTER;


// CAN控制命令定义
#define CMD_CAN_GetMsgRxBuf	    0 	 // 读取接收数据消息缓存中消息数量
#define CMD_CAN_GetMsgTxBuf   	1 	 // 读取发送数据消息缓存中空闲空间数量
#define CMD_CAN_ClearMsgRxBuf   2    // 清除接收缓存中数据.
#define CMD_CAN_ClearMsgTxBuf   3    // 清除发送缓存中数据.
#define CMD_CAN_RST             4    // 复位CAN寄存器为初始状态
#define CMD_CAN_CLOSE           5    // 关闭CAN时钟,也就是关闭CAN功能,可以省电 

// CAN(管脚)功能重映射定义
#define CAN_REMAP_0       0    // CAN没有重映射
#define CAN_REMAP_1       1    // CAN重映射1
#define CAN_REMAP_2       2    // CAN重映射2

/************************************************************************************************************************/
// 以下表是工控模块STM32F107VC,STM32F103VE,STM32F103ZE CAN1-2管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// CAN1-CAN2(管脚)功能重映射表
/*
|---------------------------------------|
| 项目  |  重映射  |  TX管脚  |  RX管脚 |
|---------------------------------------|
|       |   没有   |   PA12   |   PA11  |
|       |-------------------------------|
| CAN1  |  重映射1 |   PB9    |   PB8   |
|       |-------------------------------|
|       |  重映射2 |   PD1    |   PD0   |
|---------------------------------------|
|       |   没有   |   PB13   |   PB12  |
| CAN2  |-------------------------------|
|       |  重映射1 |   PB6    |   PB5   |
|---------------------------------------|
*/

/************************************************************************************************************************/
// 以下表是工控模块STM32F407VE CAN1-2管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// CAN1-CAN2(管脚)功能映射表
/*
|---------------------------------------|
| 项目  | 复用选择 |  TX管脚  |  RX管脚 |
|---------------------------------------|
|       |          |   PA12   |   PA11  |
|       |          |--------------------|
| CAN1  |   AF9    |   PB9    |   PB8   |
|       |          |--------------------|
|       |          |   PD1    |   PD0   |
|---------------------------------------|
|       |          |   PB13   |   PB12  |
| CAN2  |   AF9    |--------------------|
|       |          |   PB6    |   PB5   |
|---------------------------------------|
*/

// CAN初始化参数数据结构  
typedef struct
{
    INT16U Flag;        // 工作标志
    INT8U  Mode;        // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
	INT32U Baud;        // CAN波特率
    INT8U  IDE;         // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
    INT8U  RTR;         // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 
    INT8U  PinRemap;    // CAN引脚功能重映射
    INT8U  TXPin;       // CAN发送引脚定义
    INT8U  RXPin;       // CAN发送引脚定义   
    
    INT16U RxMsgNum;    // CAN接收缓存可接收消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    INT16U TxMsgNum;    // CAN发送缓存可发送消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    CAN_BUF_MSG *pRxMsgBuf;  // CAN接收缓存指针
    CAN_BUF_MSG *pTxMsgBuf;  // CAN发送缓存指针
}CAN_PARA;

// CAN滤波器数据帧结构定义  
typedef struct
{
    INT8U   CAN2StartBank; // CAN2开始组, 它们定义了CAN2(从)接口的开始组，范围是1~27
    
    INT32U  FIFO;          // CAN 过滤器FIFO关联配置:Bit27~Bit0有效, bit0是第0组，bit27是第27组 报文在通过了某过滤器的过滤后，
                           // 将被存放到其关联的FIFO中, 0：过滤器被关联到FIFO0；1：过滤器被关联到FIFO1。

    INT32U  Scale;         // CAN 过滤器位宽寄存器：Bit27~Bit0有效, bit0是第0组，bit27是第27组，
                           // 0：过滤器位宽为2个16位; 1：过滤器位宽为单个32位。

    INT32U  Mode;          // CAN过滤器模式 (Filter mode)：Bit27~Bit0有效, bit0是第0组，	bit27是第27组，
                           // 0: 过滤器组x的2个32位寄存器工作在标识符屏蔽位模式；1: 过滤器组x的2个32位寄存器工作在标识符列表模式。
    
    INT32U  Active;        // 过滤器激活 (Filter active): 	 Bit27~Bit0有效, bit0是第0组，	bit27是第27组
                           // 0：过滤器被禁用；1：过滤器被激活。
    
    INT32U *pBuf;          // 设置的过滤器寄存器数据指针
    
    INT8U  len;            // 设置的过滤器寄存器数据长度
    
    INT8U  MaxLen;         // 滤波器总长度
    
}CAN_FILTER_PARA;

/*************************************************************************************/
//
// 					 CAN硬件驱动函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: CAN_Init;
*
* Description: CAN始化函数;
* 
* Input:  id, CAN识别号(CAN1_ID、CAN2_ID); *pPara, CAN初始化参数指针;
*         pFilter, 过滤器参数指针; 
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   有2个CAN接口的只需初始化一次过滤器; 如果CAN1初始化了过滤器, 则CAN2就不需要
*         再初始化过滤器了，直接把pFilter参数设置为0就可以了;
************************************************************************************/
INT32S CAN_Init(INT8U id,  CAN_PARA *pPara, CAN_FILTER_PARA *pFilter);

/***********************************************************************************
* Function: CAN_FilterInit;
*
* Description: CAN过滤器初始化函数; 
* 
* Input:  *pFilter, 过滤器参数指针
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CAN_FilterInit(CAN_FILTER_PARA *pFilter);

/***********************************************************************************
* Function: CAN_Write;
*
* Description: 发送CAN数据;
*           
* Input:  id, CAN识别号(CAN1_ID、CAN2_ID);
*         pTxMsg,  发送数据块指针;
*      		
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CAN_Write(INT8U id, CAN_TX_MSG *pTxMsg);

/***********************************************************************************
* Function: CAN_Read;
*
* Description: 接收CAN数据;
*           
* Input:  id, CAN识别号(CAN1_ID、CAN2_ID);
*         pRxMsg, 接收数据块指针;
*      		
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CAN_Read(INT8U id, CAN_RX_MSG *pRxMsg);

/***********************************************************************************
* Function: CAN_Ctrl;
*
* Description: CAN命令控制函数;
* 
* Input:  id, CAN识别号(CAN1_ID, CAN2_ID);
*         Cmd, CAN控制命令, 命令如下:
*              CMD_CAN_GetMsgRxBuf: 读取接收数据消息缓存中消息数量, 默认Para为0
*              CMD_CAN_GetMsgTxBuf: 读取发送数据消息缓存中空闲空间数量, 默认Para为0
*              CMD_CAN_ClearMsgRxBuf: 清除接收缓存中数据, 默认Para为0
*              CMD_CAN_ClearMsgTxBuf: 清除发送缓存中数据, 默认Para为0
*              CMD_CAN_RST:           复位CAN寄存器为初始状态, 默认Para为0
*              CMD_CAN_CLOSE:         关闭CAN时钟,也就是关闭CAN功能,可以省电, 默认Para为0 
*
*         Para，CAN命令控制参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码; 如有返回的命令返回相应参数;
*
* Note:   none;
************************************************************************************/
INT32S CAN_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif

/***********************************************************************************/
// 文件结束
/***********************************************************************************/

