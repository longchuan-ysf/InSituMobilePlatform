/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: crc.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是CRC计算驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32U CRC32(INT32U *p, INT16U len);
*          2. INT16U CRC16(INT8U *p, INT16U len);
*          3. INT16U CRC16_2(INT8U *p1, INT16U len1, INT8U *p2, INT16U len2);
*          4. INT8U  CRC8(INT8U *p, INT16U len);
*          5. INT32S CRC_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CRC_H 
#define __CRC_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// CRC命令定义
#define CRC_CMD_SetCRC32   0 	//	Computes the 32-bit CRC of a given data word(32-bit).
#define CRC_CMD_SetCRC8	   1 	//	Stores a 8-bit data in the Independent Data(ID) register.
#define CRC_CMD_GetCRC8	   2 	//	Returns the 8-bit data stored in the Independent Data(ID) register
#define CRC_CMD_GetCRC32   3 	//	Returns the current 32-bit CRC value.
#define CRC_CMD_ResetCRC32 4	// Resets the CRC Data register (DR)

/*************************************************************************************/
//
// 					 CRC硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: CRC32;
*
* Description: 计算32-bit CRC函数;
*              
* Input:  *p,  要计算CRC32的数据指针;
*         len，数据长度;
*
* Output: none;
*
* Return: CRC校验结果;
*
* Note:   none;
************************************************************************************/
INT32U CRC32(INT32U *p, INT16U len);

/***********************************************************************************
* Function: CRC16;
*
* Description: CRC16计算函数;
*              
* Input:  *p,  要计算CRC16的数据指针;
*         len，数据长度;
*
* Output: none;
*
* Return: CRC校验结果;
*
* Note:   none;
************************************************************************************/
INT16U CRC16(INT8U *p, INT16U len);

/***********************************************************************************
* Function: CRC16_2;
*
* Description: 两组数CRC16计算函数;
*              
* Input:  *p1,*p2  要计算CRC16的数据指针;
*         len1，len2 数据长度;
*
* Output: none;
*
* Return: CRC校验结果;
*
* Note:   *p1, len1这一组数在前; *p2, len2这一组数在后;
************************************************************************************/
INT16U CRC16_2(INT8U *p1, INT16U len1, INT8U *p2, INT16U len2);

/***********************************************************************************
* Function: CRC8;
*
* Description: CRC8计算函数;
*              
* Input:  *p,  要计算CRC8的数据指针;
*         len，数据长度;
*
* Output: none;
*
* Return: CRC校验结果;
*
* Note:   none;
************************************************************************************/
INT8U CRC8(INT8U *p, INT16U len);

/***********************************************************************************
* Function: CRC_Ctrl;
*
* Description: CRC命令控制操作;
*              
* Input:  Cmd,  CRC控制命令;
*         Para，CRC命令控制参数;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CRC_Ctrl(INT8U Cmd, INT32U Para);
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/




