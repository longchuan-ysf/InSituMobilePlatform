/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name:timer.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    20120.8.24			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是Timer硬件驱动程序(包括PWM和FCLK)头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S Timer_Init(INT8U id, TIM_PARA *pPara);
*          2. INT32S Timer_Ctrl(INT8U id, INT8U Cmd, TIM_CTRL *pPara);
*          3. INT32S PWM_Init(INT8U id, PWM_PARA *pPara);
*          4. INT32S PWM_Ctrl(INT8U id, INT8U Cmd, PWM_CTRL *pPara);
*          5. INT32S PWM_Write(INT8U id, PWM_WRITE *pPara);
*          6. INT32S FCLK_Init(INT8U id, FCLK_PARA *pPara);
*          7. INT32S FCLK_Ctrl(INT8U id, INT8U Cmd, INT8U Chx);
*          8. INT32S FCLK_Read(INT8U id, INT8U Cmd, INT8U Chx, INT32U *p, INT16U len, INT16U TimeOut);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __TIMER_H 
#define __TIMER_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// Timer索引定义
#define TIM1_ID       0  
#define TIM2_ID       1
#define TIM3_ID       2
#define TIM4_ID       3
#define TIM5_ID       4
#define TIM6_ID       5
#define TIM7_ID       6
#define TIM8_ID       7		

//以下是STM32F M4增加
#define TIM9_ID       8		
#define TIM10_ID      9		
#define TIM11_ID      10		
#define TIM12_ID      11		
#define TIM13_ID      12		
#define TIM14_ID      13		

// TIMER 工作模式
#define TIM_MODE_NONE       0  // 定时器功能未定义; 
#define TIM_MODE_TIM        1  // 定时模式(无外部输入输出); 
#define TIM_MODE_PWM        2  // PWM输出(连续脉冲)模式(CH1,CH2,CH3,CH4输出);
#define TIM_MODE_FCLK       3  // 脉冲输入(CH1,CH2,CH3,CH4输入);

// TIMER 控制命令
#define CMD_TIM_ENA       0	  // 使能定时器
#define CMD_TIM_DIS       1	  // 关闭定时器
#define CMD_TIM_READ      2   // 读取定时计数值
#define CMD_TIM_STATUS    3	  // 读取定时器状态
#define CMD_TIM_RST       4	  // 复位TIM寄存器为初始状态
#define CMD_TIM_CLOSE     5	  // 关闭TIM时钟,也就是关闭TIM功能,可以省电 

// TIM通道定义 
#define TIM_CH1 	0  
#define TIM_CH2 	1  
#define TIM_CH3 	2  
#define TIM_CH4 	3
#define TIM_MAIN 	4
#define TIM_ALL 	5

// TIM中断标志
#define TIM_IT_FLAG            0x0001  // TIM主定时器中断标志(更新中断)
#define TIM_CH1IT_FLAG         0x0002  // TIM CH1子定时器1中断标志(捕获/比较1中断)
#define TIM_CH2IT_FLAG         0x0004  // TIM CH2子定时器2中断标志(捕获/比较2中断)
#define TIM_CH3IT_FLAG         0x0008  // TIM CH3子定时器3中断标志(捕获/比较3中断)
#define TIM_CH4IT_FLAG         0x0010  // TIM CH4子定时器4中断标志(捕获/比较4中断)
#define TIM_COMIT_FLAG         0x0020  // TIM Commutation Interrupts
#define TIM_TRGIT_FLAG         0x0040  // TIM Trigger Interrupts
#define TIM_BRKIT_FLAG         0x0080  // TIM Break Interrupts

// 工作参数标志(Flag)定义
#define TIM_EN      0x0001  // 定时器(主定时器)使能; 如果主定时器没有使能，则子定时器1-4使能无效
#define TIM_CH1EN   0x0002  // 定时器通道1(子定时器1)使能
#define TIM_CH2EN   0x0004  // 定时器通道2(子定时器1)使能
#define TIM_CH3EN   0x0008  // 定时器通道3(子定时器1)使能
#define TIM_CH4EN   0x0010  // 定时器通道4(子定时器1)使能



// 定时器工作模式
#define TIM_WKMODE_INT          0  // 定时器工作在定时中断模式, 定时时间由参数t,t1-t4设置; 
#define TIM_WKMODE_COUNT        1  // 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                   // 再通过参数CMD_TIM_READ读取计数值

// TIMER参数结构 
typedef struct
{
    INT32U Flag;    // 工作参数参数标志
    INT8U  Mode;    // 工作模式
    INT16U Prescaler;// 分频系数, 当工作模式是TIM_WKMODE_COUNT时, 必须设置分频系数
    //INT32U t;       // 主定时器定时时间, 单位us
    //INT32U t1;      // 子定时器1(主定时器CH1)定时时间, 单位us; 注意：定时时间要小于主定时器
    //INT32U t2;      // 子定时器2(主定时器CH2)定时时间, 单位us; 注意：定时时间要小于主定时器
    //INT32U t3;      // 子定时器3(主定时器CH3)定时时间, 单位us; 注意：定时时间要小于主定时器
    //INT32U t4;      // 子定时器4(主定时器CH4)定时时间, 单位us; 注意：定时时间要小于主定时器
    //void (* isr) (INT8U flag, void *p);    // 主定时器及子定时器定时中断函数钩子函?
}TIM_PARA;


// TIMER控制参数结构 
typedef struct
{
    INT16U Chx;     // 主定制器和子定时器选择:TIM_CH1EN~TIM_CH4EN,TIM_MAINEN    
    INT32U t;       // 主定时器定时时间, 单位us
    INT32U t1;      // 子定时器1(主定时器CH1)定时时间, 单位us; 注意：定时时间要小于主定时器
    INT32U t2;      // 子定时器2(主定时器CH2)定时时间, 单位us; 注意：定时时间要小于主定时器
    INT32U t3;      // 子定时器3(主定时器CH3)定时时间, 单位us; 注意：定时时间要小于主定时器
    INT32U t4;      // 子定时器4(主定时器CH4)定时时间, 单位us; 注意：定时时间要小于主定时器
}TIM_CTRL;

/************************************************************************************************************************/
// 以下2个表是工控模块STM32F107VC,STM32F103VE,STM32F103ZE定时器管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// TIM1(管脚)功能重映射表
/*
|---------------------------------------------------------------------------------------------------------------|
| 项目  |  重映射  | CH1管脚 | CH2管脚 | CH3管脚 | CH4管脚 | CH1N管脚 | CH2N管脚 | CH3N管脚 | ETR管脚 | BKIN管脚|
|---------------------------------------------------------------------------------------------------------------|
|       |   没有   |   PA8   |   PA9   |   PA10  |   PA11  |   PB13   |   PB14   |   PB15   |  PA12   |  PB12   |
|       |-------------------------------------------------------------------------------------------------------|
| TIM1  |  重映射1 |   PA8   |   PA9   |   PA10  |   PA11  |   PA7    |   PB0    |   PB1    |  PA12   |  PA6    |
|       |-------------------------------------------------------------------------------------------------------|
|       |  重映射3 |   PE9   |   PE11  |   PE13  |   PE14  |   PE8    |   PE10   |   PE12   |  PE7    |  PE15   |
|---------------------------------------------------------------------------------------------------------------|
*/

// TIM2-TIM5(管脚)功能重映射表
/*
|--------------------------------------------------------------------|
| 项目  |  重映射  | CH1管脚 | CH2管脚 | CH3管脚 | CH4管脚 | ETR管脚 |
|--------------------------------------------------------------------|
|       |   没有   |PA0(ETR) |   PA1   |   PA2   |   PA3   |同CH1管脚|
|       |------------------------------------------------------------|
|       |  重映射1 |PA15(ETR)|   PB3   |   PA2   |   PA3   |同CH1管脚|
| TIM2  |------------------------------------------------------------|
|       |  重映射2 |PA0(ETR) |   PA1   |   PB10  |   PB11  |同CH1管脚|
|       |------------------------------------------------------------|
|       |  重映射3 |PA15(ETR)|   PB3   |   PB10  |   PB11  |同CH1管脚|
|--------------------------------------------------------------------|
|       |   没有   |   PA6   |   PA7   |   PB0   |   PB1   |   PD2   |
|       |------------------------------------------------------------|
| TIM3  |  重映射2 |   PB4   |   PB5   |   PB0   |   PB1   |   PD2   |
|       |------------------------------------------------------------|
|       |  重映射3 |   PC6   |   PC7   |   PC8   |   PC9   |   PD2   |
|--------------------------------------------------------------------|
|       |   没有   |   PB6   |   PB7   |   PB8   |   PB9   |   PE0   |
| TIM4  |------------------------------------------------------------|
|       |  重映射1 |   PD12  |   PD13  |   PD14  |   PD15  |   PE0   |
|--------------------------------------------------------------------|
| TIM5  |   没有   |   PA0   |   PA1   |   PA2   |   PA3   |   无    |
|--------------------------------------------------------------------|
*/

/************************************************************************************************************************/
// 以下3个表是系列工控模块STM32F407XX定时器管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// TIM1/8管脚功能映射表
/*
|---------------------------------------------------------------------------------------------------------------|
| 项目  | 复用选择 | CH1管脚 | CH2管脚 | CH3管脚 | CH4管脚 | CH1N管脚 | CH2N管脚 | CH3N管脚 | ETR管脚 | BKIN管脚|
|---------------------------------------------------------------------------------------------------------------|
|       |          |   PA8   |   PA9   |   PA10  |   PA11  |   PB13   |   PB14   |   PB15   |  PA12   |  PB12   |
|       |          |--------------------------------------------------------------------------------------------|
| TIM1  |   AF1    |   PE9   |   PE11  |   PE13  |   PE14  |   PA7    |   PB0    |   PB1    |  PA12   |  PA6    |
|       |          |--------------------------------------------------------------------------------------------|
|       |          |    -    |    -    |    -    |    -    |   PE8    |   PE10   |   PE12   |  PE7    |  PE15   |
|---------------------------------------------------------------------------------------------------------------|
|       |          |   PC6   |   PC7   |   PC8   |   PC9   |   PA5    |   PB0    |   PB1    |  PA0    |  PA6    |
|       |          |--------------------------------------------------------------------------------------------|
| TIM8  |   AF3    |   PI5   |   PI6   |   PI7   |   PI2   |   PA7    |   PB14   |   PB15   |  PI3    |  PI4    |
|       |          |--------------------------------------------------------------------------------------------|
|       |          |    -    |    -    |    -    |    -    |   PH13   |   PH14   |   PH15   |   -     |   -     |
|---------------------------------------------------------------------------------------------------------------|
*/
// TIM2-TIM5管脚功能映射表
/*
|--------------------------------------------------------------------|
| 项目  | 复用选择 | CH1管脚 | CH2管脚 | CH3管脚 | CH4管脚 | ETR管脚 |
|--------------------------------------------------------------------|
|       |          |   PA0   |   PA1   |   PA2   |   PA3   |   PA0   |
|       |          | ------------------------------------------------|
|       |   AF1    |   PA5   |   PB3   |   PB10  |   PB11  |   PA5   |
| TIM2  |          |-------------------------------------------------|
|       |          |   PA15  |    -    |    -    |    -    |   PA15  |
|--------------------------------------------------------------------|
|       |          |   PA6   |   PA7   |   PB0   |   PB1   |   PD2   |
|       |          |-------------------------------------------------|
| TIM3  |   AF2    |   PB4   |   PB5   |    -    |    -    |    -    |
|       |          |-------------------------------------------------|
|       |          |   PC6   |   PC7   |   PC8   |   PC9   |    -    |
|--------------------------------------------------------------------|
|       |          |   PB6   |   PB7   |   PB8   |   PB9   |   PE0   |
| TIM4  |   AF2    | ------------------------------------------------|
|       |          |   PD12  |   PD13  |   PD14  |   PD15  |    -    |
|--------------------------------------------------------------------|
|       |          |   PA0   |   PA1   |   PA2   |   PA3   |   无    |
| TIM5  |   AF2    |-------------------------------------------------|
|       |          |   PH10  |   PH11  |   PH12  |   PI0   |    -    |
|--------------------------------------------------------------------|
*/
// TIM9-TIM14管脚功能映射表
/*
|----------------------------------------------------------|
| 项目  | 复用选择 | CH1管脚 | CH2管脚 | CH3管脚 | CH4管脚 | 
|----------------------------------------------------------|
|       |          |   PA2   |   PA3   |    -    |    -    |
| TIM9  |   AF3    | --------------------------------------|
|       |          |   PE5   |   PE6   |    -    |    -    | 
|----------------------------------------------------------|
|       |          |   PB8   |    -    |    -    |    -    |
| TIM10 |   AF3    |---------------------------------------|
|       |          |   PF6   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PB9   |    -    |    -    |    -    |
| TIM11 |   AF3    | --------------------------------------|
|       |          |   PF7   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PB14  |   PB15  |    -    |    -    |
| TIM12 |   AF9    | --------------------------------------|
|       |          |   PH6   |   PH9   |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PA6   |    -    |    -    |    -    |
| TIM13 |   AF9    | --------------------------------------|
|       |          |   PF8   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PA7   |    -    |    -    |    -    |
| TIM14 |   AF9    | --------------------------------------|
|       |          |   PF9   |    -    |    -    |    -    |
|----------------------------------------------------------|
*/

/************************************************************************************************************************/
// TIMER(管脚)功能重映射定义
#define TIM_REMAP_0       0    // TIMER没有重映射
#define TIM_REMAP_1       1    // TIMER重映射1
#define TIM_REMAP_2       2    // TIMER重映射2
#define TIM_REMAP_3       3    // TIMER重映射3

// TIMER 管脚参数结构 
typedef struct
{
    INT8U  Remap; // TIMER引脚功能重映射
    
    INT8U  CH1;   // 通道1管脚定义
    INT8U  CH2;   // 通道2管脚定义
    INT8U  CH3;   // 通道3管脚定义
    INT8U  CH4;   // 通道4管脚定义

    INT8U  CH1N;  // 通道1反向输出管脚定义
    INT8U  CH2N;  // 通道2反向输出管脚定义
    INT8U  CH3N;  // 通道3反向输出管脚定义
    
    INT8U  ETR;   // ETR管脚定义
    INT8U  BKIN;  // BKIN管脚定义    
}TIM_PIN;

/*************************************************************************************/
//
// 						Timer硬件驱动程序函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: Timer_Init;
*
* Description: TIMER初始化函数;
* 
* Input:  id, TIMER索引: STM32F1XX: TIM1_ID ~ TIM8_ID; STM32F4XX: TIM1_ID ~ TIM14_ID;  
*         *pPara, 初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S Timer_Init(INT8U id, TIM_PARA *pPara);

/***********************************************************************************
* Function: Timer_Ctrl;
*
* Description: TIMER控制操作;
* 
* Input:  id, TIMER索引: STM32F1XX: TIM1_ID ~ TIM8_ID; STM32F4XX: TIM1_ID ~ TIM14_ID; 
*         Cmd, 控制命令: CMD_TIM_ENA:  使能定时器   
*                        CMD_TIM_DIS:  关闭定时器
*                        CMD_TIM_STATUS: 读取定时器状态
*         pPara, 参数值;
*
* Output: none;
*          		
* Return: 控制命令是CMD_TIM_STATUS时返回TIMER状态;其它命令返回ERR_TRUE, 控制正确, ERR_TRUE, 控制失败;
*
* Note:   当控制命令是CMD_TIM_ENA, 
*         当控制命令是CMD_TIM_STATUS, 返回数值：0: 定时器停止; 1：定时器正在运行
************************************************************************************/
INT32S Timer_Ctrl(INT8U id, INT8U Cmd, TIM_CTRL *pPara);

/**********************************************************************************************/
// PWM常量定义
/**********************************************************************************************/
// PWM1-4索引定义
#define  PWM1_ID		  		0	   	// PWM1索引
#define  PWM2_ID		  		1	   	// PWM2索引
#define  PWM3_ID		  		2	   	// PWM3索引
#define  PWM4_ID		  		3	   	// PWM4索引

//以下是STM32F M4增加
#define  PWM5_ID		  		4	   	// PWM5索引
#define  PWM6_ID		  		5	   	// PWM6索引
#define  PWM7_ID		  		6	   	// PWM7索引
#define  PWM8_ID		  		7	   	// PWM8索引


// PWM通道定义
#define  PWM_CH1          		0      	// PWM通道1
#define  PWM_CH2          		1      	// PWM通道2
#define  PWM_CH3          		2  		// PWM通道3
#define  PWM_CH4          		3   	// PWM通道4

// PWM通道标志定义
#define  PWM_CH1FLAG          	0x01   	// PWM通道1标志位, 适用多通道操作 
#define  PWM_CH2FLAG          	0x02   	// PWM通道2标志位, 适用多通道操作 
#define  PWM_CH3FLAG          	0x04   	// PWM通道3标志位, 适用多通道操作 
#define  PWM_CH4FLAG          	0x08   	// PWM通道4标志位, 适用多通道操作 

// PWM_Ctrl 控制命令定义
#define  CMD_PWM_ENA      		0  		// 使能, 允许PWM输出
#define  CMD_PWM_DIS      		1	 	// 停止, 关闭PWM输出
#define  CMD_PWM_FREQ     		2	 	// 设置频率
#define  CMD_PWM_RATE     		3	 	// 设置占空比
#define  CMD_PWM_STATUS   		4	 	// 读取状态
#define  CMD_PWM_ENAMUL 		5  		// 同时使能多通道   
#define  CMD_PWM_DISMUL 		6  		// 同时停止多通道 
#define  CMD_PWM_PULNUM 		7  		// 读取当前发出脉冲个数
#define  CMD_PWM_PAUSE 		    8  		// 暂时停止PWM输出


// 应用PWM_Write()函数控制PWM输出后, 可以用以下指令用PWM_Ctrl()控制
#define  CMD_PWM_STOP      		8  		// 停止



// 定义PWM工作模式定义
#define  PWM_FREQ       0   // 连续脉冲频率输出, 持续输出
#define  PWM_FREQ_N     1   // 多个脉冲频率输出, 输出完设定的脉冲数后停止
#define  PWM_RATE       2   // 固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
#define  PWM_DMA        3   // 新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决定 

// 工作参数标志Flag定义
#define PWMCH1_EN_FLAG  0x0001  // PWM CH1使能标志：1, 使能; 0, 关闭
#define PWMCH2_EN_FLAG  0x0002  // PWM CH2使能标志：1, 使能; 0, 关闭
#define PWMCH3_EN_FLAG  0x0004  // PWM CH3使能标志：1, 使能; 0, 关闭
#define PWMCH4_EN_FLAG  0x0008  // PWM CH4使能标志：1, 使能; 0, 关闭

#define PWMCH1_PIN_FLAG 0x0010  // PWM CH1停止模式管脚输出电平标志: 0, 低电平; 1, 高电平
#define PWMCH2_PIN_FLAG 0x0020  // PWM CH2停止模式管脚输出电平标志: 0, 低电平; 1, 高电平
#define PWMCH3_PIN_FLAG 0x0040  // PWM CH3停止模式管脚输出电平标志: 0, 低电平; 1, 高电平
#define PWMCH4_PIN_FLAG 0x0080  // PWM CH4停止模式管脚输出电平标志: 0, 低电平; 1, 高电平

#define PWM_WRITE_EN_FLAG   0x8000   // 使能PWM脉冲输出由PWM_Write()函数控制
#define PWM_ISRHOOK_EN_FLAG 0x4000   // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数

// 钩子函数ISRHook()中id为PWM1-8索引定义: PWM1_ID-PWM8_ID; Flag是完成标志和出错标志, 定义如下
#define PWMCH1_OK_FLAG  0x0001  // PWM CH1发送脉冲完成标志;
#define PWMCH2_OK_FLAG  0x0002  // PWM CH2发送脉冲完成标志;
#define PWMCH3_OK_FLAG  0x0004  // PWM CH3发送脉冲完成标志;
#define PWMCH4_OK_FLAG  0x0008  // PWM CH4发送脉冲完成标志;

#define PWMCH1_ERR_FLAG  0x0010  // PWM CH1发送脉冲失败标志;
#define PWMCH2_ERR_FLAG  0x0020  // PWM CH2发送脉冲失败标志;
#define PWMCH3_ERR_FLAG  0x0040  // PWM CH3发送脉冲失败标志;
#define PWMCH4_ERR_FLAG  0x0080  // PWM CH4发送脉冲失败标志;


// PWM参数结构 
typedef struct
{
    INT32U Flag;      // 工作参数标志
    INT8U  Mode;      // PWM工作模式
    INT8U  TimerID;   // 选择定时器
    TIM_PIN TimPin;   // 所选定时器管脚定义
    INT32U Freq;      // PWM输出初始频率
    INT16U Rate[4];   // 4个通道,PWM输出占空比
    void (* pISRHook) (INT8U id, INT32U Flag); // PWM完成中断(或出错)函数钩子函数指针
}PWM_PARA;

#define PWM_CTRL_FREQ        0       // 控制更改PWM频率输出, 并且连续输出
#define PWM_CTRL_FREQ_N      1       // 控制更改PWM频率输出, 并且输出N个脉冲后停止
#define PWM_CTRL_RATE        2       // 控制更改PWM占空比输出
#define PWM_CTRL_FREQ_RATE   3       // 同时控制更改PWM频率和占空比输出

// PWM控制参数结构 
typedef struct
{
    INT8U  Mode;      // 控制操作模式
    INT8U  Chx;       // 选择通道
    INT32U Freq;      // PWM输出频率
    INT16U Rate[4];   // 4个通道,PWM输出占空比
    INT32U Num[4];    // 输出脉冲数量
}PWM_CTRL;

//-------------------------------------------------------------------------
// 应用PWM_Write()函数控制PWM输出后, 可以用以下指令用PWM_Ctrl()控制
// CMD_PWM_ENA: 使能, 允许PWM输出
// CMD_PWM_DIS: 停止, 关闭PWM输出; 关闭后只能再PWM_Write()重新控制输出
// CMD_PWM_STATUS: 读取状态   
// CMD_PWM_PULNUM: 读取当前发出脉冲个数
// CMD_PWM_PAUSE:  暂时停止PWM输出, 可以再发CMD_PWM_ENA使能继续输出

// 函数PWM_Write()参数定义
// 脉冲及数量数据格式定义
#define PWM_CMD_TYPE_MASK           0xC0000000  // 命令类型屏蔽位
#define PWM_CMD01_TYPE              0x40000000  // 连续输出不同频率脉冲命令位
#define PWM_CMD10_TYPE              0x80000000  // 连续输出相同频率脉冲命令位
#define PWM_CMD_SIZE_FLAG           0x00007FFF  // 脉冲数量标志位

#define PWM_DATA_TYPE               0x00000000  // 数据位
#define PWM_DATA_FREQ_FLAG          0x000FFFFF  // 频率值标志位
typedef union 
{
    INT32U  val;     
    struct // 命令数据结构: Type固定为01或者10, rev默认为0, Size为输出脉冲数量; 如果Type是00, 则表示bit19-bit0位是频率值
    {
        INT32U Size:                15; // 输出脉冲数量(bit14-bit0), 范围:2-32767 

        INT32U rev:                 15; // 保留默认是0(bit29-bit15);
        INT32U Type:                2;  // 数据类型定义(bit31,bit30): 01, 输出变化频率脉冲: 从下一个数据开始往后, 连续输出Size个脉冲, 每个脉冲频率由后面Size个Freq数据指定; 注意本数据Size部分范围必须是2-32767, 一般用于脉冲频率加减速输出;
                                        //                            10, 输出固定频率脉冲: 固定频率是下一个频率数据(只有固定的一个), 并且连续输出Size个;   注意本数据Size部分范围必须是2-32767, 但一般Size要大一些(建议大于16)用这种格式定义,
                                        //                                否则会大量占用CPU资源; 一般用于固定频率脉冲输出
    }Cmd;
}PWM_FREQ_TypeDef;

typedef union 
{
    INT16U  val;     
    struct // 命令数据结构: Type固定为01或者10, rev默认为0, Size为输出脉冲数量; 如果Type是00, 则表示bit13-bit0位是占空比值
    {
        INT16U Size:                14; // 输出脉冲数量(bit13-bit0), 范围:2-16383 

        INT16U Type:                2;  // 数据类型定义(bit15,bit14): 01, 输出变化占空比脉冲: 从下一个数据开始往后, 连续输出Size个脉冲, 每个脉冲占空比由后面Size个数据指定; 注意本数据Size部分范围必须是2-16383, 一般用于脉冲占空比加减速输出;
                                        //                            10, 输出固定占空比脉冲: 固定占空比是下一个数据(只有固定的一个), 并且连续输出Size个;   注意本数据Size部分范围必须是2-16383, 但一般Size要大一些(建议大于16)用这种格式定义,
                                        //                                否则会大量占用CPU资源; 一般用于固定占空比脉冲输出
    }Cmd;
}PWM_RATE_TypeDef;

#define PWM_FREQ_FLAG       0x0001  // 可变频率脉冲输出标志 
#define PWM_RATE_FLAG       0x0002  // 可变占空比脉冲输出标志
#define PWM_DATA_CONV_FLAG  0x8000  // 输入数据转换完成标志


// PWM写函数PWM_Write()参数结构 
typedef struct
{
    INT32U  Flag;      // 控制标志位
    INT8U   ch;        // 选择PWM输出通道: PWM_CH1, PWM_CH2, PWM_CH3, PWM_CH4
    INT8U   chx;       // 选择PWM输出通道标志: PWM_CH1FLAG, PWM_CH2FLAG, PWM_CH3FLAG, PWM_CH4FLAG
    INT16U  Rate;      // PWM占空比, 暂时未用
    INT32U  Freq;      // 脉冲频率 
    INT32U  len;       // 数据缓存数量
    void *pData;       // 数据缓存指针
}PWM_WRITE;

/*************************************************************************************/
//
// 						PWM硬件驱动程序函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: PWM_Init;
*
* Description: PWM初始化函数;
* 
* Input:  id, PWM索引(STM32F1XX系列芯片: PWM1_ID~PWM4_ID; STM32F4XX系列芯片: PWM1_ID~PWM8_ID) 
*         *pPara, 初始化参数指针参数值;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S PWM_Init(INT8U id, PWM_PARA *pPara);

/***********************************************************************************
* Function: PWM_Ctrl;
*
* Description: PWM输出控制操作;
* 
* Input:  id, PWM索引(STM32F1XX系列芯片: PWM1_ID~PWM4_ID; STM32F4XX系列芯片: PWM1_ID~PWM8_ID) 
*         Cmd, 控制命令:  CMD_PWM_ENA, 使能;   
*                         CMD_PWM_DIS, 停止;
*                         CMD_PWM_FREQ, 设置PWM频率;  
*                         CMD_PWM_RATE, 设置PWM占空比;  
*                         CMD_PWM_STATUS, 读取PWM状态;
*                         CMD_PWM_PULNUM, 读取当前发出脉冲个数
*         pPara, 参数指针结构;
*
* Output: none;
*          		
* Return: 控制命令是CMD_PWM_STATUS时返回PWM状态;其它命令返回ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S PWM_Ctrl(INT8U id, INT8U Cmd, PWM_CTRL *pPara);

/***********************************************************************************
* Function: PWM_Write;
*
* Description: PWM写入控制函数;
* 
* Input:  id, PWM索引(STM32F1XX系列芯片: PWM1_ID~PWM4_ID; STM32F4XX系列芯片: PWM1_ID~PWM8_ID)  
*         *pPara, 控制参数指针参数值;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数使用DMA方式输出脉冲; 请在PWM_Init()初始化里设置PWM_WRITE_EN_FLAG标志位
************************************************************************************/
INT32S PWM_Write(INT8U id, PWM_WRITE *pPara);

/**********************************************************************************************/
// FCLK常量定义
/**********************************************************************************************/
#define  FCLK1_ID		  		0	   	// FCLK1索引
#define  FCLK2_ID		  		1	   	// FCLK2索引
#define  FCLK3_ID		  		2	   	// FCLK3索引
#define  FCLK4_ID		  		3	   	// FCLK4索引
//以下是STM32F4XX增加
#define  FCLK5_ID		  		4	   	// FCLK5索引
#define  FCLK6_ID		  		5	   	// FCLK6索引
#define  FCLK7_ID		  		6	   	// FCLK7索引
#define  FCLK8_ID		  		7	   	// FCLK8索引

// FCLK通道定义
#define  FCLK_CH1          		0      	// FCLK通道1
#define  FCLK_CH2          		1      	// FCLK通道2
#define  FCLK_CH3          		2  		// FCLK通道3
#define  FCLK_CH4          		3   	// FCLK通道4

// Modify 2020.4.8: 将通道标志改为bit4-bit7
#define  FCLK_CH1FLAG          	0x01   	// FCLK通道1标志位, 适用多通道操作 
#define  FCLK_CH2FLAG          	0x02   	// FCLK通道2标志位, 适用多通道操作 
#define  FCLK_CH3FLAG          	0x04   	// FCLK通道3标志位, 适用多通道操作 
#define  FCLK_CH4FLAG          	0x08   	// FCLK通道4标志位, 适用多通道操作 

//#define  FCLK_CH1FLAG          	0x10   	// FCLK通道1标志位, 适用多通道操作 
//#define  FCLK_CH2FLAG          	0x20   	// FCLK通道2标志位, 适用多通道操作 
//#define  FCLK_CH3FLAG          	0x40   	// FCLK通道3标志位, 适用多通道操作 
//#define  FCLK_CH4FLAG          	0x80   	// FCLK通道4标志位, 适用多通道操作 

//#define  FCLK_CH1FULL  	       	0x10   	// FCLK通道1缓存满标志位
//#define  FCLK_CH2FULL   	    0x20   	// FCLK通道2缓存满标志位
//#define  FCLK_CH3FULL     	   	0x40   	// FCLK通道3缓存满标志位
//#define  FCLK_CH4FULL       	0x80   	// FCLK通道4缓存满标志位

// FCLK 工作模式
#define  FCLK_MODE_COUNT       0  		// 计数模式(1路, CH1输入); 
#define  FCLK_MODE_DECODE      1  		// 正交编码器计数(CH1输入接A, CH2输入接B);
#define  FCLK_MODE_FREQ        2  		// 测频模式(CH1,CH2,CH3,CH4输入);
#define  FCLK_MODE_PWMRATE     3  		// 测PWM占空比模式(CH1输入);

// FCLK_Read函数控制命令定义
#define  CMD_FCLK_FREQ         0  // 按时间逆序读取FCLK(CH1~CH4)频率: 频率值按时间逆序输出, 即读取buf[0]是T时采集, 则buf[N]是T-N时采集; 
                                  // 当不要求所有脉冲频率都要读取时用这个指令, 即测量固定间隔时间点上的脉冲频率  
#define  CMD_FCLK_PWMRATE      1  // 读取FCLK(CH1) 的占空比: 
#define  CMD_FCLK_DECODE       2  // 读取FCLK(CH1 CH2)正交解码计数值
#define  CMD_FCLK_COUNT		   3  // 读取FCLK(CH1)计数值

#define  CMD_FCLK_FREQ_ORDER   4  // 按时间正序读取FCLK(CH1~CH4)频率：频率值按时间正序输出, 即读取buf[0]是T时采集, 则buf[N]是T+N时采集
                                  // 当需要读取全部脉冲频率值时, 用这个指令  

// FCLK_Ctrl 控制命令定义
#define   CMD_FCLK_ENA      0  // 使能单一通道;   
#define   CMD_FCLK_DIS      1  // 停止单一通道;  
#define   CMD_FCLK_STATUS   2  // 读取FCLK状态;
#define   CMD_FCLK_CLEAR    3  // 定时器值清零
#define   CMD_FCLK_CNT      4  // 读取测量脉冲频率或者占空比数量


// 工作参数标志Flag定义
#define FCLKCH1_EN_FLAG  0x00000001  // FCLK CH1使能标志：1, 使能; 0, 关闭
#define FCLKCH2_EN_FLAG  0x00000002  // FCLK CH2使能标志：1, 使能; 0, 关闭
#define FCLKCH3_EN_FLAG  0x00000004  // FCLK CH3使能标志：1, 使能; 0, 关闭
#define FCLKCH4_EN_FLAG  0x00000008  // FCLK CH4使能标志：1, 使能; 0, 关闭

#define FCLKCH1_PIN_FLAG 0x00000010  // FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLKCH2_PIN_FLAG 0x00000020  // FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLKCH3_PIN_FLAG 0x00000040  // FCLK CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLKCH4_PIN_FLAG 0x00000080  // FCLK CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿

#define FCLKCH1_PCS_FLAG 0x00000300  // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLKCH2_PCS_FLAG 0x00000C00  // FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLKCH3_PCS_FLAG 0x00003000  // FCLK CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLKCH4_PCS_FLAG 0x0000C000  // FCLK CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;

// 新增功能定义
#define FCLKCH1_DMA_FLAG 0x00010000  // FCLK CH1 DMA功能使能
#define FCLKCH2_DMA_FLAG 0x00020000  // FCLK CH2 DMA功能使能
#define FCLKCH3_DMA_FLAG 0x00040000  // FCLK CH3 DMA功能使能
#define FCLKCH4_DMA_FLAG 0x00080000  // FCLK CH4 DMA功能使能

// 缓存满标志定义
#define FCLKCH1_BUFFULL_FLAG 0x01000000  // FCLK CH1 缓存满标志
#define FCLKCH2_BUFFULL_FLAG 0x02000000  // FCLK CH2 缓存满标志
#define FCLKCH3_BUFFULL_FLAG 0x04000000  // FCLK CH3 缓存满标志
#define FCLKCH4_BUFFULL_FLAG 0x08000000  // FCLK CH4 缓存满标志

#define FCLK_ETR_FLAG    0x80000000  // FCLK的ETR脚作为时钟输入;
#define FCLK_MKY_FLAG    0x40000000  // FCLK的煤科院校准时钟;


// FCLK参数结构 
typedef struct
{
    INT32U Flag;      // 工作参数标志
    INT8U  Mode;      // FCLK工作模式
    INT8U  TimerID;   // 选择定时器
    TIM_PIN TimPin;   // 所选定时器管脚定义
    INT32U MinFreq;   // PWM输出初始频率
    INT16U *pBuf[4];  // 接收数据缓存指针
    INT16U BufLen[4]; // 接收缓存长度   
}FCLK_PARA;

/*************************************************************************************/
//
// 						FCLK硬件驱动程序函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: FCLK_Init;
*
* Description: FCLK初始化函数;
* 
* Input:  id, FCLK索引(STM32F1XX系列芯片: FCLK1_ID~FCLK4_ID; STM32F4XX系列芯片: FCLK1_ID~FCLK8_ID) 
*         *pPara, FCLK初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S FCLK_Init(INT8U id, FCLK_PARA *pPara);

/***********************************************************************************
* Function: FCLK_Ctrl;
*
* Description: FCLK输入控制操作;
* 
* Input:  id, FCLK索引(STM32F1XX系列芯片: FCLK1_ID~FCLK4_ID; STM32F4XX系列芯片: FCLK1_ID~FCLK8_ID) 
*         Cmd, 控制命令:  CMD_FCLK_ENA, 使能;   
*                         CMD_FCLK_DIS, 停止;
*                         CMD_FCLK_STATUS, 读取FCLK状态;
                          CMD_FCLK_CLEAR,  定时器值清零 
                          CMD_FCLK_CNT,    读取测量脉冲频率或者占空比数量
*         Chx, 通道号是FCLK_CH1FLAG~FCLK_CH4FLAG,可以多通道操作; 或者通道号是:FCLK_CH1~FCLK_CH4,只能单通道操作; 
*
* Output: none;
*          		
* Return: 控制命令是CMD_PWM_STATUS时返回FCLK状态; 控制命令是CMD_FCLK_CNT时返回数量值; 
*        其它命令返回ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   Cmd控制命令是CMD_FCLK_ENA/CMD_FCLK_DIS/CMD_FCLK_STATUS时通道号Chx是: FCLK_CH1FLAG~FCLK_CH4FLAG, 
*                      可以进行或操作, 实现多通道操作, 比如: (FCLK_CH1FLAG|FCLK_CH1FLAG);   
*         Cmd控制命令是CMD_FCLK_CLEAR, 通道号Chx无效,默认0;
*         Cmd控制命令是CMD_FCLK_CNT, 通道号Chx是:FCLK_CH1~FCLK_CH4,只能单通道操作, ; 
************************************************************************************/
INT32S FCLK_Ctrl(INT8U id, INT8U Cmd, INT8U Chx);

/***********************************************************************************
* Function: FCLK_Read;
*
* Description: FCLK读取数值;
* 
* Input:  id, FCLK索引(STM32F1XX系列芯片: FCLK1_ID~FCLK4_ID; STM32F4XX系列芯片: FCLK1_ID~FCLK8_ID) 
*         cmd, 读取命令: CMD_FCLK_FREQ, 读取FCLK_CH1, FCLK_CH2,FCLK_CH3,FCLK_CH4的频率, 单位：0.01hz
*                     	 CMD_FCLK_DECODE, 读取正交解码计数值, 此命令暂不支持;
*                        CMD_FCLK_PWMRATE, 读取FCLK_CH1的占空比, 单位：0.01%; 
*                        CMD_FCLK_COUNT, 读取计数值; 
*         chx, 通道号是: FCLK_CH1~FCLK_CH4, 只能单通道操作; 
*         *p,  数据缓存指针;
*         len, 数据长度; 
*         timeout, 超时返回;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S FCLK_Read(INT8U id, INT8U Cmd, INT8U Chx, INT32U *p, INT16U len, INT16U TimeOut);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/