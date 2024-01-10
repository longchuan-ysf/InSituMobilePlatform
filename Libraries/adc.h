/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: adc.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是模拟/数字转换(ADC)硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S ADC_Init(INT8U id, ADC_PARA *pPara);
*          2. INT32S ADC_Read(INT8U id, INT16S *p, INT8U len);
*          3. INT32S ADC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __ADC_H 
#define __ADC_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// ADC索引定义
#define ADC1_ID		0 
#define ADC2_ID    	1 
#define ADC3_ID    	2 

// 板子模拟量输入端口序号定义, 不能更改
#define AI1_ID    	0 
#define AI2_ID    	1 
#define AI3_ID    	2 
#define AI4_ID    	3 
#define AI5_ID    	4 
#define AI6_ID    	5 
#define AI7_ID    	6 
#define AI8_ID    	7 
#define AI9_ID    	8 
#define AI10_ID    	9 
#define AI11_ID    	10 
#define AI12_ID    	11 
#define AI13_ID    	12 
#define AI14_ID    	13 
#define AI15_ID    	14 
#define AI16_ID    	15 
#define AI_ID_NONE  0xFF  // 无定义 


// 采样转换周期
#define ADC_SAMP1T17US	 0  // ADC采样转换时间为14周期(1.5+12.5)  :  1.17us
#define ADC_SAMP1T67US	 1  // ADC采样转换时间为20周期(7.5+12.5)  ： 1.67us
#define ADC_SAMP2T17US	 2  // ADC采样转换时间为26周期(13.5+12.5) ： 2.17us
#define ADC_SAMP2T58US	 3  // ADC采样转换时间为31周期(28.5+12.5) ： 2.58us
#define ADC_SAMP4T5US	 4  // ADC采样转换时间为54周期(41.5+12.5) ： 4.5us
#define ADC_SAMP5T67US	 5  // ADC采样转换时间为68周期(55.5+12.5) ： 5.67us
#define ADC_SAMP7T0US	 6  // ADC采样转换时间为84周期(71.5+12.5) ： 7us
#define ADC_SAMP21T0US	 7  // ADC采样转换时间为252周期(239.5+12.5)：21us

// 模块模拟量输入编号(即工控模块模拟管脚)定义, 不能更改
#define AIN0           0      // AIN0对应编号
#define AIN1           1      // AIN1对应编号
#define AIN2           2      // AIN2对应编号
#define AIN3           3      // AIN3对应编号
#define AIN4           4      // AIN4对应编号
#define AIN5           5      // AIN5对应编号
#define AIN6           6      // AIN6对应编号
#define AIN7           7      // AIN7对应编号
#define AIN8           8      // AIN8对应编号
#define AIN9           9      // AIN9对应编号
#define AIN10          10     // AIN10对应编号
#define AIN11          11     // AIN11对应编号
#define AIN12          12     // AIN12对应编号
#define AIN13          13     // AIN13对应编号
#define AIN14          14     // AIN14对应编号
#define AIN15          15     // AIN15对应编号

// 定义ADC转换值输出方式
#define ADC_ISROUT    0     // 选择中断输出AD采样值
#define ADC_READOUT   1     // 选择ADC_Read()函数读取采样值

// Flag参数标志定义
#define ADC_ISROUT_FLAG      0x8000   // 调用中断函数钩子函数输出AD采样数据
// STM32F103XX和STM32F107XX系列模块使用下面标志
#define ADC_TIM5CH1_FLAG     0x0001   // 使用TIM5子定时器1定时AD采样
#define ADC_TIM5CH2_FLAG     0x0002   // 使用TIM5子定时器2定时AD采样
#define ADC_TIM5CH3_FLAG     0x0004   // 使用TIM5子定时器3定时AD采样
#define ADC_TIM5CH4_FLAG     0x0008   // 使用TIM5子定时器4定时AD采样
#define ADC_TIM5MAIN_FLAG    0x0010   // 使用TIM5主定时器定时AD采样

// STM32F407XX系列模块使用下面标志
#define ADC_TIM14MAIN_FLAG   0x0020   // 使用TIM14主定时器定时AD采样
#define ADC_TIM14CH1_FLAG    0x0040   // 使用TIM14子定时器1定时AD采样

typedef struct
{
	INT16U  len;		        // ADC数据长度
	INT16S  *pBuf;              // ADC采样数据指针
}ADC_VAR;


// ADC参数结构 
typedef struct
{
    INT16U Flag;                 // 参数标志
    INT8U  Mode;                 // 工作模式：参考工作模式定义
    INT8U  AINum;                // AIx采样通道板子端口数量
    INT8U  *pAITab;              // AI采样通道顺序转换表指针
    
    INT8U  AvgNum;               // 定义采样次数来计算平均值, 范围 1~256, 注意：此值太大会占用很大内存空间
    INT8U  Freq;                 // AD采样频率, 每秒钟采样次数
    INT16U SampleTime;           // ADC采样转换时间
    INT16S *pBuf;                // AD采集数据缓存指针
}ADC_PARA;

// ADC_Ctrl 控制命令定义
#define  CMD_ADC_ENA     0 // ADC开始转换
#define  CMD_ADC_DIS     1 // ADC停止转换
#define  CMD_ADC_SWSTART 2 // ADC启动转换



/*************************************************************************************/
//
// 					 ADC硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: ADC_Init;
*
* Description: ADC初始化函数;
*              
* Input:  id, ADC索引标识：ADC1_ID,ADC2_ID,ADC3_ID; 默认ADC1_ID
*         *pPara, ADC初始化参数;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化完成，ADC并没有开始工作, 必须调用ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0)使能ADC
*         才开始工作。
************************************************************************************/
INT32S  ADC_Init (INT8U id, ADC_PARA *pPara);

/***********************************************************************************
* Function: ADC_Read;
*
* Description: ADC读取函数;
*              
* Input:  id, ADC标识(ADC1_ID, ADC2_ID, ADC3_ID), 现只支持ADC1_ID;
*         *p, 读取返回数据指针; len，读取数据个数 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S ADC_Read(INT8U id, INT16S *p, INT8U len);

/***********************************************************************************
* Function: ADC_Ctrl;
*
* Description: ADC控制函数;
*              
* Input:  id, ADC标识(ADC1_ID, ADC2_ID, ADC3_ID), 现只支持ADC1_ID
*         Cmd，ADC控制命令, CMD_ADC_ENA:开始转换; CMD_ADC_DIS: 停止转换;
*		  Para，控制参数
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S ADC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif 
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
