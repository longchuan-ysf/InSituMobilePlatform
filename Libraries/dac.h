/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: dac.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是数字/模拟转换(DAC)硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S DAC_Init (INT8U id, DAC_PARA *pPara);
*          2. void DAC_Write(INT8U id, INT16U val);
*          3. INT32S DAC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __DAC_H 
#define __DAC_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// DAC索引定义
#define DAC1_ID     0  
#define DAC2_ID     1 

// DAC工作模式定义
#define DAC_MODE_MTOUT	    0	// 手动输出
#define DAC_MODE_ATOUT_N	1	// 连续输出1~N个缓存中的数据后停止
#define DAC_MODE_ATOUT	    2	// 持续输出缓存中的数据, 不停止;

// DAC返回状态
#define DAC_WORK        0x0001  // DAC正在工作 
#define DAC_STOP        0x0000  // DAC停止工作 

// DAC管脚定义
#define DAC1_PIN        PA4  // DAC1管脚定义 
#define DAC2_PIN        PA5  // DAC2管脚定义 

// ADC初始化参数结构
typedef struct
{   
    INT16U Flag;           // 工作标志
    INT8U  Mode;           // 工作模式
    INT8U  pin;            // DAC管脚
    INT16U *pbuf;          // 缓存指针
    INT16U len;            // 缓存长度
    INT32U Freq;           // 工作频率
}DAC_PARA;

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// DAC_Ctrl 控制命令定义
#define CMD_DAC_DIS           0		 // 停止DAC
#define CMD_DAC_ENA           1		 // 使能DAC
#define CMD_DAC_FREQ          2		 // 设置DAC更新频率
#define CMD_DAC_STATUS        3		 // 读取DAC状态, 返回0, 停止; 返回1, 正在执行输出
#define CMD_DAC_RST           4		 // 复位DAC寄存器为初始状态
#define CMD_DAC_CLOSE         5		 // 关闭DAC时钟,也就是关闭DAC功能,可以省电 
   
/*************************************************************************************/
//
// 					 DAC硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: DAC_Init;
*
* Description: DAC初始化函数;
*              
* Input:  id, ADC索引(DAC1_ID~DAC2_ID);
*         DAC_PARA *pPara, DAC设置参数指针
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S DAC_Init (INT8U id, DAC_PARA *pPara);

/***********************************************************************************
* Function: DAC_Write;
*
* Description: 手动控制DAC输出函数即直接向DAC写数据转换成电压输出;
* 
* Input:  id, ADC识别号(DAC1_ID~DAC2_ID);
*         val, 写入的数据, 数据数值范围:0x0000~0x0fff;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void DAC_Write(INT8U id, INT16U val);

/***********************************************************************************
* Function:  DAC_Ctrl;
*
* Description: DAC命令控制;
* 
* Input:  id, ADC识别号: DAC1_ID~DAC2_ID;
*         Cmd,  ADC控制命令：
*         CMD_DAC_DIS,    停止DAC; 
*         CMD_DAC_ENA,    使能DAC; 
*         CMD_DAC_FREQ,   设置DAC更新频率, Para是设置的频率;
*         CMD_DAC_STATUS, 读取DAC状态, 返回DAC_STOP, 停止; 返回DAC_WORK, 正在执行输出; 
*         CMD_DAC_RST,    复位DAC寄存器为初始状态; Para默认为0;
*         CMD_DAC_CLOSE,  关闭DAC时钟,也就是关闭DAC功能,可以省电 ; 
*         Para，ADC命令控制参数, Para默认为0;
*
* Output: none;
*          		
* Return: 无返回的命令，返回ERR_TRUE; 有返回的命令返回相应参数;
*
* Note:   none;
************************************************************************************/
INT32S DAC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif 


