/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastPWMCLK.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责TIM定时器, PWM信号输出及FCLK脉冲输入任务处理;
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

/************************************************************************************/
// 测试说明
/************************************************************************************/
/*
1. PWM测试: 
   (1). IO配置说明: 在IO配置文件中配置PWM_CH1~CH4管脚, 以PWM1为例 IO配置: 
        // PWM1(TIM3) 管脚功能映射设置: 
        #define PWM1_REMAP      TIM_REMAP_3 // PWM1(TIM3)管脚重映射(只支持STM32F107VC/103VE/103ZE工控模块)
        #define PWM1_CH1        PC6         // PWM1(TIM3) CH1管脚定义,可选以下端口: PA6, PB4, PC6
        #define PWM1_CH2        PC7         // PWM1(TIM3) CH2管脚定义,可选以下端口: PA7, PB5, PC7
        #define PWM1_CH3        PC8         // PWM1(TIM3) CH3管脚定义,可选以下端口: PB0, PC8
        #define PWM1_CH4        PC9         // PWM1(TIM3) CH4管脚定义,可选以下端口: PB1, PC9
        #define PWM1_ETR        IO_NONE     // PWM1(TIM3) ETR管脚定义,可选以下端口: PD2
 
        这些IO配置只需按工控模块各自默认设置即可, 不需要更改;
   
   (2). 功能参数配置说明: 在配置文件中做如下配置, 以PWM1为例:       
        #define PWM1_EN             1		   // PWM1使能, 1：打开使能， 0：关闭
        // 定义PWM输出模式设置
        #define PWM1_MODE           PWM_FREQ   // 可以选择: 0(PWM_FREQ):   连续脉冲频率输出, 持续输出
                                               //           1(PWM_FREQ_N): 多个脉冲频率输出, 输出完设定的脉冲数后停止
                                               //           2(PWM_RATE):   固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
                                               //           3(PWM_DMA):    新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决 
        
        #define PWM1_FREQ		    1000  	   // 初始频率
        #define PWM1_TIM            TIM3_ID    // 选择定时器, 这个设置不可更改
        // 通道使能
        #define PWM1CH1_EN		    1		   // PWM1CH1：1, 使能; 0, 关闭
        #define PWM1CH2_EN		    1		   // PWM1CH2：1, 使能; 0, 关闭
        #define PWM1CH3_EN		    1		   // PWM1CH3：1, 使能; 0, 关闭
        #define PWM1CH4_EN		    1		   // PWM1CH4：1, 使能; 0, 关闭   
   
        在这些配置中一般只需更改PWM1_MODE模式及通道使能既可，其它按默认配置;
        
   (3). 本例程实现如下功能(以PWM1为例):   
        测试连续脉冲频率输出模式(PWM1_MODE配置0):
        用示波器测量PWM输出端口: 输出方波, 脉冲每隔3秒增加1KHZ, 频率变化范围：1KHZ~10KHZ;
         
        测试多个脉冲频率输出模式(PWM1_MODE配置1):
        用示波器PWM输出端口: 输出方波, 频率1KHZ, 每隔3秒发送FREQ_N(8)个脉冲;      
   
        测试固定频率占空比可调连续脉冲输出模式(PWM1_MODE配置2): 
        用示波器在PWM输出端口测试信号: 输出PWM, 频率1KHZ,占空比0%-100%可调, 每隔3秒占空比增加10%;         
   
        测试利用函数PWM_Write()实现DMA方式输出多个脉冲频率模式(PWM1_MODE配置3):
        用示波器PWM输出端口: 间隔3S,输出连续18个脉冲;      
   
   (4). 根据以上(1)(2)配置, 在APP_Init.c中调用PWM_APPInit()函数初始化; 
   
   (5). 在本文件中调用PWM_Start(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode), 启动PWM1输出;
        间隔3秒调用PWM_Test(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode), 控制PWM1输出信号;
        
                     
2. FCLK测试: 
   (1). IO配置说明: 在IO配置文件中配置FCLK1_CH1~CH4管脚, 以FCLK1为例 IO配置: 
        // FCLK1(TIM4)管脚功能映射设置: 
        #define FCLK1_REMAP    TIM_REMAP_1  // FCLK1(TIM4)管脚重映射(只支持STM32F107VC/103VE/103ZE工控模块)
        #define FCLK1_CH1      PD12         // FCLK1(TIM4) CH1管脚定义,可选以下端口: PB6,  PD12
        #define FCLK1_CH2      PD13         // FCLK1(TIM4) CH2管脚定义,可选以下端口: PB7,  PD13
        #define FCLK1_CH3      PD14         // FCLK1(TIM4) CH3管脚定义,可选以下端口: PB8,  PD14
        #define FCLK1_CH4      PD15         // FCLK1(TIM4) CH4管脚定义,可选以下端口: PB9,  PD15
        #define FCLK1_ETR      IO_NONE      // FCLK1(TIM4) ETR管脚定义,可选以下端口: PE0      
         
        这些IO配置只需按工控模块各自默认设置即可, 不需要更改;
   
   (2). 功能参数配置说明: 在配置文件中做如下配置, 以FCLK1为例:       
        #define FCLK1_EN           1	       // FCLK1使能, 1：打开使能， 0：关闭
        #define FCLK1_MODE	       2		   // 模式选择: 0(FCLK_MODE_COUNT), 计数模式(1路, CH1输入有效); 
                                               //           1(FCLK_MODE_DECODE), 正交编码器计数(CH1接A，CH2接B);
                                               //           2(FCLK_MODE_FREQ), 测频模式(4路, CH1, CH2, CH3, CH4输入都有效); 
                                               //           3(FCLK_MODE_PWMRATE), 测PWM占空比模式(1路, CH1输入有效); 
        #define FCLK1_TIM          TIM4_ID     // 选择定时器, 这个设置不可更改

        #define FCLK1CH1_EN		   1	       // FCLK1：1, 使能; 0, 关闭
        #define FCLK1CH2_EN		   1		   // FCLK2：1, 使能; 0, 关闭
        #define FCLK1CH3_EN		   1	       // FCLK3：1, 使能; 0, 关闭
        #define FCLK1CH4_EN		   1		   // FCLK4：1, 使能; 0, 关闭
   
        在这些配置中一般只需更改FCLK1_MODE模式及FCLK1CH1_EN~FCLK1CH4_EN既可，其它按默认配置;
        
   (3). 本例程实现如下功能(以FCLK1为例):   
        测试计数模式(FCLK1_MODE配置0): 
        在FCLK1CH1端口加1KHZ(或其它频率)脉冲测试信号: 每隔3秒测量出脉冲数量;
   
        测试正交编码器计数模式(FCLK1_MODE配置1): 
        在FCLK1CH1,FCLK1CH2端口加正交编码脉冲(A、B)测试信号: 实时测量编码器脉冲计数数量;     

        测试测频模式(FCLK1_MODE配置2): 
        在FCLK1CH1~CH4端口加1KHZ(或其它频率)脉冲测试信号: 每隔3秒测量出输入脉冲频率;
        
        测试PWM占空比模式(FCLK1_MODE配置3): 
        在FCLK1CH1端口加1KHZ(或其它频率)脉冲测试信号, 并且脉宽可调: 每隔3秒测量出脉冲信号的占空比;     
   
   (4). 根据以上(1)(2)配置, 在APP_Init.c中调用FCLK_APPInit()函数初始化; 
   
   (5). 在本文件中调用FCLK_Ctrl(FCLK1_ID, CMD_FCLK_ENA, FCLK1CH_EN), 使能FCLK1工作;
        间隔3秒调用FCLK_Test(FCLK1_ID, FCLK1_MODE), 实现FCLK1模式0,2,3测试;
        间隔20毫秒调用FCLK_Read(id, CMD_FCLK_DECODE, 0, (INT32U *)&cnt1, 1, 0), 实现FCLK1模式1测试;
   
   (6). 通过串口调试输出观察测量结果; 
 
3. TIMER定时器测试: 
   (1). 功能参数配置说明: 在配置文件中做如下配置, 以TIM1为例:       
        #define TIM1_EN       1		  // TIM1使能, 1：打开使能， 0：关闭
        #define TIM1_MODE     1		  // TIM1工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM1_T,TIM1_T1-TIM1_T4设置; 
                                      //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                      // 再通过参数CMD_TIM_READ读取计数值
        #define TIM1CH1_EN    1		  // TIM1子定时器1使能, 1：打开使能， 0：关闭
        #define TIM1CH2_EN    0		  // TIM1子定时器2使能, 1：打开使能， 0：关闭
        #define TIM1CH3_EN    0		  // TIM1子定时器3使能, 1：打开使能， 0：关闭
        #define TIM1CH4_EN    0		  // TIM1子定时器4使能, 1：打开使能， 0：关闭

        // TIM1所有定时器(包含子定时器)使能 
        #define TIM1CH_EN	   (TIM1_EN|(TIM1CH1_EN<<1)|(TIM1CH2_EN<<2)|(TIM1CH3_EN<<3)|(TIM1CH4_EN<<4))  // TIM1所有定时器(包含子定时器)：BIT0:TIM1(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

        // 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
        #define TIM1_T        1000000	  // TIM1主定时器定时时间, 单位us
                              
        #define TIM1_T1       1000000     // TIM1子定时器1定时时间, 单位us
        #define TIM1_T2       1000000	  // TIM1子定时器2定时时间, 单位us
        #define TIM1_T3       1000000	  // TIM1子定时器3定时时间, 单位us
        #define TIM1_T4       500000	  // TIM1子定时器4定时时间, 单位us

        #define TIM1_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                                // 默认计数单位是1us
   
        在这些配置中一般只需更改TIM1_MODE模式, TIM1CH1_EN~TIM1CH4_EN, TIM1_T, TIM1_T1~T4既可，其它按默认配置;
        
   (3). 本例程实现如下功能(以TIM1为例):  
        测试定时中断模式(TIM1_MODE配置0):
        实现功能: 间隔1秒, 在ISRHook.c中 TIM1_UP_ISRHook, TIM1_CC_ISRHook产生相应中断, 并通过调试串口打印中断结果;
   
        测试定时计数模式(TIM1_MODE配置1): 
        实现功能: 间隔3秒, 测量延时函数Delay_ms(20)的计数值, 定时器默认设置1us计数值, 一般20ms计数值会在20000左右;

   (4). 根据以上(1)(2)配置, 在APP_Init.c中调用TIM_APPInit()函数初始化; 

   (5). 在定时中断模式中, 调用TIM_Start()启动所有定时器工作;
        
        在定时计数模式, 间隔3秒调用TIM_ReadCount(), 应用下面程序实现测量20ms间隔计数值
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM2_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM2_ID, CMD_TIM_READ, 0); // 读取20ms计数值
   
   (6). 通过串口调试输出观察结果;         
*/
/************************************************************************************/
// 引用外部头文件
#include "config.h"
#if (TASK_PWMFCLK_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"
#include "motor.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/


/************************************************************************************/
// PWM输出测试设置
/************************************************************************************/
#define  FREQ_N         8  // 发送脉冲波形个数

/************************************************************************************/
// FCLK测试
/************************************************************************************/
/***********************************************************************************
* Function: FCLK_Test;
*
* Description: FCLK测试例程
* 
* Input:  id, FCLK索引(FCLK1_ID, FCLK2_ID, FCLK3_ID, FCLK4_ID, FCLK5_ID, FCLK6_ID, FCLK7_ID, FCLK8_ID);
*         Mode, PWM输出模式(FCLK_MODE_COUNT, FCLK_MODE_FREQ, FCLK_MODE_PWMRATE);
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((FCLK1_EN > 0)||(FCLK2_EN > 0)||(FCLK3_EN > 0)||(FCLK4_EN > 0)||(FCLK5_EN > 0)||(FCLK6_EN > 0)||(FCLK7_EN > 0)||(FCLK8_EN > 0)) 
void FCLK_Test(INT8U id, INT8U Mode)
{
#define MAX_DATA_NUM	4   // 最大读取数据数量
    INT32U buf[MAX_DATA_NUM], i, cnt;
	INT32S flag;
    INT8U FClkEn;
	
	if (Mode == FCLK_MODE_PWMRATE)  // 测量占空比模式
	{   
        UserVars.FCLK[id].Mode = FCLK_MODE_PWMRATE;
        flag = FCLK_Read(id, CMD_FCLK_PWMRATE, FCLK_CH1, buf, MAX_DATA_NUM, 0); // 连续读取MAX_DATA_NUM个占空比值存入buf
        if (flag == ERR_TRUE)
        {
             UserVars.FCLK[id].Rate = buf[0];
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {                 
                 printf("AT+FCLK%d=D", id+1);            // 打印输出占空比值
                 for (i=0; i<MAX_DATA_NUM; i++)
                 {
                     printf(",%d.%d", buf[i]/100,(buf[i]%100)/10);
                 }
                 printf("\r\n");
             }
             #endif
        }
        else
        {
             UserVars.FCLK[id].Rate = 0;
             #if (DEBUG_APP_EN == 1) 
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+ERROR=FCLK%d测量PWM占空比失败\r\n",id+1);
             }
             #endif
        }
    }
	else if (Mode == FCLK_MODE_FREQ)  // 测量频率模式
	{
        UserVars.FCLK[id].Mode = FCLK_MODE_FREQ;        
        if (id == FCLK1_ID)
        {
            #if (FCLK1_EN > 0)
            FClkEn = FCLK1CH_EN;
            #endif
        }
        #if (FCLK2_EN > 0)
        else if (id == FCLK2_ID)
        {
           FClkEn = FCLK2CH_EN;
        }
        #endif
        #if (FCLK3_EN > 0)
        else if (id == FCLK3_ID)
        {
           FClkEn = FCLK3CH_EN;
        }
        #endif
        #if (FCLK4_EN > 0)
        else if (id == FCLK4_ID)
        {
           FClkEn = FCLK4CH_EN;
        }
        #endif
#if (MODULE_CLASS == STM32F407XX)       
        #if (FCLK5_EN > 0)
        else if (id == FCLK5_ID)
        {
           FClkEn = FCLK5CH_EN;
        }
        #endif
        #if (FCLK6_EN > 0)
        else if (id == FCLK6_ID)
        {
           FClkEn = FCLK6CH_EN;
        }
        #endif
        #if (FCLK7_EN > 0)
        else if (id == FCLK7_ID)
        {
           FClkEn = FCLK7CH_EN;
        }
        #endif
        #if (FCLK8_EN > 0)
        else if (id == FCLK8_ID)
        {
           FClkEn = FCLK8CH_EN;
        }
        #endif
#endif        
        if (FClkEn&FCLK_CH1FLAG)             // 通道CH1使能
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH1, buf, MAX_DATA_NUM, 0); // 连续读取CH1通道MAX_DATA_NUM个频率值存入buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH1] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)        // 打印输出频率值
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F1", id+1); 
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                 
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH1] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH1测量频率失败\r\n", id+1);
                 }
                 #endif
            }
        }            
		if (FClkEn&FCLK_CH2FLAG)             // 通道CH2使能, 信号从DI2输入
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH2, buf, MAX_DATA_NUM, 0);    // 连续读取CH2通道MAX_DATA_NUM个频率值存入buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH2] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // 打印输出频率值
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F2", id+1); 
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH2] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH2测量频率失败\r\n", id+1);
                 }
                 #endif
            }
		}
        
        if (FClkEn&FCLK_CH3FLAG)                // 通道CH3使能, 信号从DI3输入
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH3, buf, MAX_DATA_NUM, 0);    // 连续读取CH3通道MAX_DATA_NUM个频率值存入buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH3] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // 打印输出频率值
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F3", id+1);
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                 
            }
            else
            {
                 UserVars.FCLK[id].Freq[FCLK_CH3] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH3测量频率失败\r\n", id+1);
                 }
                 #endif
            }
        }
        
        if (FClkEn&FCLK_CH4FLAG)	                    // 通道CH4使能, 信号从DI4输入        
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH4, buf, MAX_DATA_NUM, 0);    // 连续读取CH4通道MAX_DATA_NUM个频率值存入buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH4] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // 打印输出频率值
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F4", id+1);
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH4] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH4测量频率失败\r\n", id+1);
                 }
                 #endif
            }    
        }
        /*
         #if (DEBUG_APP_EN == 1)            // 打印输出频率值
         if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
         {
             printf("AT+FCLK%d=F", id+1);
             for (i=0; i<4; i++)
             {
                 printf(",%d", UserVars.FCLK[id].Freq[i]/100);
             }
             printf("\r\n");
         }
         #endif
        */
    }
    else if (Mode == FCLK_MODE_COUNT) // 读取计数值模式
	{
        UserVars.FCLK[id].Mode = FCLK_MODE_COUNT;
        flag = FCLK_Read(id, CMD_FCLK_COUNT, FCLK_CH1, &cnt, 0, 0);   // 读取计数器值
        FCLK_Ctrl(id, CMD_FCLK_CLEAR, 0);   // 清0计数值
        if (flag == ERR_TRUE)
        {             
             UserVars.FCLK[id].cnt = cnt;
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+FCLK%d=N,%d\r\n", id+1,cnt);
             }
             #endif
        }
        else
        {
             UserVars.FCLK[id].cnt = 0;
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+ERROR=FCLK%d测量计数值失败\r\n", id+1);
             }
             #endif
        }
	}
}
#endif


/***********************************************************************************
* Function: PWM_Start;
*
* Description: PWM启动运行;
* 
* Input:  id, PWM索引(PWM1_ID, PWM2_ID, PWM3_ID, PWM4_ID);
*         Mode, PWM输出模式(PWM_FREQ, PWM_FREQ_N, PWM_RATE);
*         pPara, PWM参数指针;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN > 0)||(PWM2_EN > 0)||(PWM3_EN > 0)||(PWM4_EN > 0)||(PWM5_EN > 0)||(PWM6_EN > 0)||(PWM7_EN > 0)||(PWM8_EN > 0))
void PWM_Start(INT8U id, INT8U Mode, PWM_CTRL *pPara)
{    
    if (id == PWM1_ID)
    {
        #if (PWM1_EN > 0)
        pPara->Freq = PWM1_FREQ;       // 设置默认频率
        pPara->Chx = PWM1CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM1CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM1CH2_RATE;
        pPara->Rate[2] = PWM1CH3_RATE;
        pPara->Rate[3] = PWM1CH4_RATE;
        #endif
    } 
    #if (PWM2_EN > 0)    
    else if (id == PWM2_ID)
    {
        pPara->Freq = PWM2_FREQ;       // 设置默认频率
        pPara->Chx = PWM2CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM2CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM2CH2_RATE;
        pPara->Rate[2] = PWM2CH3_RATE;
        pPara->Rate[3] = PWM2CH4_RATE;
    }   
    #endif    
    #if (PWM3_EN > 0)
    else if (id == PWM3_ID)
    {
        pPara->Freq = PWM3_FREQ;       // 设置默认频率
        pPara->Chx = PWM3CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM3CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM3CH2_RATE;
        pPara->Rate[2] = PWM3CH3_RATE;
        pPara->Rate[3] = PWM3CH4_RATE;
    }        
    #endif
    #if (PWM4_EN > 0)
    else if (id == PWM4_ID)
    {
        pPara->Freq = PWM4_FREQ;       // 设置默认频率
        pPara->Chx = PWM4CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM4CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM4CH2_RATE;
        pPara->Rate[2] = PWM4CH3_RATE;
        pPara->Rate[3] = PWM4CH4_RATE;
    }        
    #endif

#if (MODULE_CLASS == STM32F407XX)
    #if (PWM5_EN > 0)
    else if (id == PWM5_ID)
    {
        pPara->Freq = PWM5_FREQ;       // 设置默认频率
        pPara->Chx = PWM5CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM5CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM5CH2_RATE;
    }        
    #endif

    #if (PWM6_EN > 0)
    else if (id == PWM6_ID)
    {
        pPara->Freq = PWM6_FREQ;       // 设置默认频率
        pPara->Chx = PWM6CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM6CH1_RATE;  // 设置每个通道输出PWM占空比
        pPara->Rate[1] = PWM6CH2_RATE;
    }        
    #endif
    
    #if (PWM7_EN > 0)
    else if (id == PWM7_ID)
    {
        pPara->Freq = PWM7_FREQ;       // 设置默认频率
        pPara->Chx = PWM7CH_EN;        // 设置使能通道 

        pPara->Rate[0] = PWM7CH1_RATE;  // 设置每个通道输出PWM占空比
        //pPara->Rate[1] = PWM7CH2_RATE;
    }        
    #endif
#endif
    
    if (Mode == PWM_FREQ)    // 连续脉冲频率输出模式, 持续输出
    {
        pPara->Mode = PWM_CTRL_FREQ;   // 设置控制更改PWM频率输出, 并且连续输出 
    }    
    else if (Mode == PWM_FREQ_N)  // 多个脉冲频率输出, 输出完设定的脉冲数后停止
    {
        pPara->Mode = PWM_CTRL_FREQ_N; // 控制更改PWM频率输出, 并且输出N个脉冲后停止
        pPara->Num[0] = FREQ_N;        // 设置每个通道输出脉冲个数
        pPara->Num[1] = FREQ_N;
        pPara->Num[2] = FREQ_N;
        pPara->Num[3] = FREQ_N;
    }    
    
    else if (Mode == PWM_RATE)     // 固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定, 占空比0%-100%可调, 持续输出
    {
        pPara->Mode = PWM_CTRL_RATE;    // 控制更改PWM占空比输出
    }    
    PWM_Ctrl(id, CMD_PWM_ENA, pPara);  // 按参数设置使能PWM输出      
}
#endif
/***********************************************************************************
* Function: PWM_Test;
*
* Description: PWM测试函数, 根据配置不同, 做不同测试;
* 
* Input:  id, PWM索引(PWM1_ID, PWM2_ID, PWM3_ID, PWM4_ID);
*         Mode, PWM输出模式(PWM_FREQ, PWM_FREQ_N, PWM_RATE);
*         pPara, PWM参数指针;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN > 0)||(PWM2_EN > 0)||(PWM3_EN > 0)||(PWM4_EN > 0)||(PWM5_EN > 0)||(PWM6_EN > 0)||(PWM7_EN > 0)||(PWM8_EN > 0))
void PWM_Test(INT8U id, INT8U Mode, PWM_CTRL *pPara)
{    
    if (Mode == PWM_FREQ)  // 测试连续脉冲频率输出, 每个3秒更换PWM频率
    {      
        pPara->Freq += 1000;         // 每次增加1KHZ
        if (pPara->Freq>10000)         // 大于10KHZ
        {
            pPara->Freq = 1000;        // 重新设置1000HZ
        }	
        PWM_Ctrl(id, CMD_PWM_FREQ, pPara);  // 按参数修改PWM输出频率   
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,500,0\r\n", id+1,pPara->Freq);
        }
        #endif
    }	
    else if (Mode == PWM_FREQ_N)  // 测试多个脉冲频率输出: 输出方波, 频率1KHZ, 每次发送8个脉冲;
    {
        pPara->Mode = PWM_CTRL_FREQ_N; // 控制更改PWM频率输出, 并且输出N个脉冲后停止
        
        if (id == PWM1_ID)
        {        
            #if (PWM1_EN > 0)
            pPara->Freq = PWM1_FREQ;       // 设置默认频率
            pPara->Chx = PWM1CH_EN;        // 设置使能通道 
            #endif
        }
        #if (PWM2_EN > 0)  
        else if (id == PWM2_ID)
        {
            pPara->Freq = PWM2_FREQ;       // 设置默认频率
            pPara->Chx = PWM2CH_EN;        // 设置使能通道 
        }
        #endif
        #if (PWM3_EN > 0)  
        else if (id == PWM3_ID)
        {
            pPara->Freq = PWM3_FREQ;       // 设置默认频率
            pPara->Chx = PWM3CH_EN;        // 设置使能通道 
        }
        #endif
        #if (PWM4_EN > 0)  
        else if (id == PWM4_ID)
        {
            pPara->Freq = PWM4_FREQ;       // 设置默认频率
            pPara->Chx = PWM4CH_EN;        // 设置使能通道 
        }
        #endif
#if (MODULE_CLASS == STM32F407XX)
        #if (PWM5_EN > 0)  
        else if (id == PWM5_ID)
        {
            pPara->Freq = PWM5_FREQ;       // 设置默认频率
            pPara->Chx = PWM5CH_EN;        // 设置使能通道 
        }
        #endif
        #if (PWM6_EN > 0)  
        else if (id == PWM6_ID)
        {
            pPara->Freq = PWM6_FREQ;       // 设置默认频率
            pPara->Chx = PWM6CH_EN;        // 设置使能通道 
        }
        #endif
        #if (PWM7_EN > 0)  
        else if (id == PWM7_ID)
        {
            pPara->Freq = PWM7_FREQ;       // 设置默认频率
            pPara->Chx = PWM7CH_EN;        // 设置使能通道 
        }
        #endif        
#endif        
        
        
        pPara->Num[0] = FREQ_N;        // 设置每个通道输出脉冲个数
        pPara->Num[1] = FREQ_N;
        pPara->Num[2] = FREQ_N;
        pPara->Num[3] = FREQ_N;
        while(PWM_Ctrl(id, CMD_PWM_STATUS, 0) != 0); // 等待输出脉冲完成
        PWM_Ctrl(id, CMD_PWM_ENA, pPara);  // 按参数设置使能PWM输出 
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,500,%d\r\n", id+1,pPara->Freq, FREQ_N);
        }
        #endif
    }	
    else if (Mode == PWM_RATE)    // 测试固定频率占空比可调连续脉冲输出: 输出PWM, 频率1KHZ,占空比0%-100%可调, 每个3秒占空比增加10%;
    {
        pPara->Rate[0] += 100;       // 增加10%占空比 
        if (pPara->Rate[0]>1000)     // 大于100%
        {
            pPara->Rate[0] = 0;      // 重新设置0%
        }
        pPara->Rate[1] += 100;       // 增加10%占空比 
        if (pPara->Rate[1]>1000)     // 大于100%
        {
            pPara->Rate[1] = 0;      // 重新设置0%
        }
        pPara->Rate[2] += 100;       // 增加10%占空比 
        if (pPara->Rate[2]>1000)     // 大于100%
        {
            pPara->Rate[2] = 0;      // 重新设置0%
        }
        pPara->Rate[3] += 100;       // 增加10%占空比 
        if (pPara->Rate[3]>1000)     // 大于100%
        {
            pPara->Rate[3] = 0;      // 重新设置0%
        }        
        PWM_Ctrl(id, CMD_PWM_RATE, pPara);  // 按参数设置使能PWM输出 
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,%d,0\r\n", id+1,pPara->Freq, pPara->Rate[0]);
        }
        #endif
    }
}
#endif

#if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0))
void TIM_Start(void)
{
    TIM_CTRL TIMCtrl;
    #if ((TIM1_EN == 1)&&(TIM1_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM1CH_EN;
        TIMCtrl.t = TIM1_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM1_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM1_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM1_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM1_T4;          // 设置子定时器4定时时间
       
        Timer_Ctrl(TIM1_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM2_EN == 1)&&(TIM2_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM2CH_EN;
        TIMCtrl.t = TIM2_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM2_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM2_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM2_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM2_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM3_EN == 1)&&(TIM3_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM3CH_EN;
        TIMCtrl.t = TIM3_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM3_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM3_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM3_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM3_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM3_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM4_EN == 1)&&(TIM4_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM4CH_EN;
        TIMCtrl.t = TIM4_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM4_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM4_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM4_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM4_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM4_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif    
    
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM5CH_EN;
        TIMCtrl.t = TIM5_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM5_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM5_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM5_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM5_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM6_EN == 1)&&(TIM6_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM6_EN;
        TIMCtrl.t = TIM6_T;            // 设置主定时器定时时间
        Timer_Ctrl(TIM6_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif   
    #if ((TIM7_EN == 1)&&(TIM7_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM7_EN;
        TIMCtrl.t = TIM7_T;            // 设置主定时器定时时间
        Timer_Ctrl(TIM7_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif     

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
	#if ((TIM8_EN == 1)&&(TIM8_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM8CH_EN;
        TIMCtrl.t = TIM8_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM8_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM8_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM8_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM8_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM8_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
#endif

#if (MODULE_CLASS == STM32F407XX)
    #if ((TIM9_EN == 1)&&(TIM9_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM9CH_EN;
        TIMCtrl.t = TIM9_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM9_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM9_T2;          // 设置子定时器2定时时间
        
        Timer_Ctrl(TIM9_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #if ((TIM10_EN == 1)&&(TIM10_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM10CH_EN;
        TIMCtrl.t = TIM10_T;           // 设置主定时器定时时间
        TIMCtrl.t1 = TIM10_T1;         // 设置子定时器1定时时间
        
        Timer_Ctrl(TIM10_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #if ((TIM11_EN == 1)&&(TIM11_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM11CH_EN;
        TIMCtrl.t = TIM11_T;           // 设置主定时器定时时间
        TIMCtrl.t1 = TIM11_T1;         // 设置子定时器1定时时间
        
        Timer_Ctrl(TIM11_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif  
    #if ((TIM12_EN == 1)&&(TIM12_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM12CH_EN;
        TIMCtrl.t = TIM12_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM12_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM12_T2;          // 设置子定时器2定时时间
        
        Timer_Ctrl(TIM12_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif    
    #if ((TIM13_EN == 1)&&(TIM13_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM13CH_EN;
        TIMCtrl.t = TIM13_T;           // 设置主定时器定时时间
        TIMCtrl.t1 = TIM13_T1;         // 设置子定时器1定时时间
        
        Timer_Ctrl(TIM13_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM14CH_EN;
        TIMCtrl.t = TIM14_T;           // 设置主定时器定时时间
        TIMCtrl.t1 = TIM14_T1;         // 设置子定时器1定时时间
        
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
#endif
}
#endif

#if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
void TIM_ReadCount(void)
{
    INT32U  cnt;
    
    // TIM1读取计数值
    #if ((TIM1_EN == 1)&&(TIM1_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM1_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM1_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM1_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM1=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM2读取计数值
    #if ((TIM2_EN == 1)&&(TIM2_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM2_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM2_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM2计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM2=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM3读取计数值
    #if ((TIM3_EN == 1)&&(TIM3_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM3_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM3_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM3_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM3计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM3=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM4读取计数值    
    #if ((TIM4_EN == 1)&&(TIM4_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM4_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM4_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM4_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM4计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM4=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM5读取计数值
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM5_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM5_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM5计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM5=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM6读取计数值
    #if ((TIM6_EN == 1)&&(TIM6_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM6_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM6_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM6_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM6计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM6=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif
    
    // TIM7读取计数值
    #if ((TIM7_EN == 1)&&(TIM7_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM7_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM7_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM7_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM7计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM7=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif    
  
#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
	// TIM8读取计数值
    #if ((TIM8_EN == 1)&&(TIM8_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM8_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM8_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM8_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM8计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM8=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif  
#endif

#if (MODULE_CLASS == STM32F407XX)   
    // TIM9读取计数值
    #if ((TIM9_EN == 1)&&(TIM9_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM9_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM9_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM9_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM9计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM9=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif       
    // TIM10读取计数值
    #if ((TIM10_EN == 1)&&(TIM10_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM10_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM10_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM10_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM10计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM10=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif  
    // TIM11读取计数值
    #if ((TIM11_EN == 1)&&(TIM11_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM11_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM11_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM11_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM11计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM11=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif      
    // TIM12读取计数值
    #if ((TIM12_EN == 1)&&(TIM12_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM12_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM12_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM12_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM12计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM12=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif       
    // TIM13读取计数值
    #if ((TIM13_EN == 1)&&(TIM13_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM13_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM13_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM13_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM13计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM13=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif       
    // TIM14读取计数值
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_COUNT)) // 定时器工作在定时计数模式
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, 0);   // 使能定时器
        Delay_ms(20);                          // 延时20ms
        Timer_Ctrl(TIM14_ID, CMD_TIM_DIS, 0);   // 关闭定时器 
        cnt = Timer_Ctrl(TIM14_ID, CMD_TIM_READ, 0); // 读取20ms计数值
        #if (DEBUG_APP_EN == 1)
        //printf("TIM14计数值: %d\r\n", cnt);     // 打印输出计数值
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM14=%d\r\n", cnt);         // 打印输出计数值
        }
        #endif
    #endif  
#endif
}
#endif


#if (MODULE_CLASS == STM32F407XX)
#define PWM_MAX_FREQ  200000     // STM32F407XX系列模块在DMA模式PWM最大脉冲频率是200KHZ 
#endif

#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
#define PWM_MAX_FREQ  100000     // STM32F107XX和STM32F103XX系列模块在DMA模式PWM最大脉冲频率是100KHZ 
#endif

#if ((PWM1_EN > 0)&&(PWM1_MODE==PWM_DMA))
#define PWM1_DATA_LEN   12
PWM_FREQ_TypeDef  PWM1Data[PWM1_DATA_LEN+1];  // PWM1输出脉冲数据
// PWM1输出脉冲数据初始化
void PWM1Data_Init(void)
{    
    // 设置连续输出4个不同频率脉冲命令
    PWM1Data[0].val = PWM_CMD01_TYPE+4;  
    PWM1Data[1].val = PWM_MAX_FREQ/5;    // 第1个脉冲频率        
    PWM1Data[2].val = PWM_MAX_FREQ/5*2;  // 第2个脉冲频率
    PWM1Data[3].val = PWM_MAX_FREQ/5*3;  // 第3个脉冲频率
    PWM1Data[4].val = PWM_MAX_FREQ/5*4;  // 第4个脉冲频率
    
    // 设置连续输出10个相同频率脉冲命令
    PWM1Data[5].val = PWM_CMD10_TYPE+10;
    PWM1Data[6].val = PWM_MAX_FREQ;   // 这10个(第5个-第14个)脉冲频率  

    // 设置连续输出4个不同频率脉冲命令
    PWM1Data[7].val = PWM_CMD01_TYPE+4;  
    PWM1Data[8].val = PWM_MAX_FREQ/5*4;    // 第15个脉冲频率
    PWM1Data[9].val = PWM_MAX_FREQ/5*3;    // 第16个脉冲频率
    PWM1Data[10].val = PWM_MAX_FREQ/5*2;   // 第17个脉冲频率
    PWM1Data[11].val = PWM_MAX_FREQ/5;     // 第18个脉冲频率
    
    // 最后一个数据设置为0, 表示结束
    PWM1Data[PWM1_DATA_LEN].val = 0;
}
#endif

#if ((PWM2_EN > 0)&&(PWM2_MODE==PWM_DMA))
#define PWM2_DATA_LEN   12
PWM_FREQ_TypeDef  PWM2Data[PWM2_DATA_LEN+1];  // PWM2输出脉冲数据
// PWM2输出脉冲数据初始化
void PWM2Data_Init(void)
{    
    // 设置连续输出4个不同频率脉冲命令
    PWM2Data[0].val = PWM_CMD01_TYPE+4;  
    PWM2Data[1].val = PWM_MAX_FREQ/5;    // 第1个脉冲频率        
    PWM2Data[2].val = PWM_MAX_FREQ/5*2;  // 第2个脉冲频率
    PWM2Data[3].val = PWM_MAX_FREQ/5*3;  // 第3个脉冲频率
    PWM2Data[4].val = PWM_MAX_FREQ/5*4;  // 第4个脉冲频率
    
    // 设置连续输出10个相同频率脉冲命令
    PWM2Data[5].val = PWM_CMD10_TYPE+10;
    PWM2Data[6].val = PWM_MAX_FREQ;   // 这10个(第5个-第14个)脉冲频率  

    // 设置连续输出4个不同频率脉冲命令
    PWM2Data[7].val = PWM_CMD01_TYPE+4;  
    PWM2Data[8].val = PWM_MAX_FREQ/5*4;    // 第15个脉冲频率
    PWM2Data[9].val = PWM_MAX_FREQ/5*3;    // 第16个脉冲频率
    PWM2Data[10].val = PWM_MAX_FREQ/5*2;   // 第17个脉冲频率
    PWM2Data[11].val = PWM_MAX_FREQ/5;     // 第18个脉冲频率
    
    // 最后一个数据设置为0, 表示结束
    PWM2Data[PWM2_DATA_LEN].val = 0;
}
#endif

#if ((PWM3_EN > 0)&&(PWM3_MODE==PWM_DMA))
#define PWM3_DATA_LEN   12
PWM_FREQ_TypeDef  PWM3Data[PWM3_DATA_LEN+1];  // PWM3输出脉冲数据
// PWM3输出脉冲数据初始化
void PWM3Data_Init(void)
{    
    // 设置连续输出4个不同频率脉冲命令
    PWM3Data[0].val = PWM_CMD01_TYPE+4;  
    PWM3Data[1].val = PWM_MAX_FREQ/5;    // 第1个脉冲频率        
    PWM3Data[2].val = PWM_MAX_FREQ/5*2;  // 第2个脉冲频率
    PWM3Data[3].val = PWM_MAX_FREQ/5*3;  // 第3个脉冲频率
    PWM3Data[4].val = PWM_MAX_FREQ/5*4;  // 第4个脉冲频率
    
    // 设置连续输出10个相同频率脉冲命令
    PWM3Data[5].val = PWM_CMD10_TYPE+10;
    PWM3Data[6].val = PWM_MAX_FREQ;   // 这10个(第5个-第14个)脉冲频率  

    // 设置连续输出4个不同频率脉冲命令
    PWM3Data[7].val = PWM_CMD01_TYPE+4;  
    PWM3Data[8].val = PWM_MAX_FREQ/5*4;    // 第15个脉冲频率
    PWM3Data[9].val = PWM_MAX_FREQ/5*3;    // 第16个脉冲频率
    PWM3Data[10].val = PWM_MAX_FREQ/5*2;   // 第17个脉冲频率
    PWM3Data[11].val = PWM_MAX_FREQ/5;     // 第18个脉冲频率
    
    // 最后一个数据设置为0, 表示结束
    PWM3Data[PWM3_DATA_LEN].val = 0;
}
#endif

#if ((PWM4_EN > 0)&&(PWM4_MODE==PWM_DMA))
#define PWM4_DATA_LEN   12
PWM_FREQ_TypeDef  PWM4Data[PWM4_DATA_LEN+1];  // PWM4输出脉冲数据
// PWM4输出脉冲数据初始化
void PWM4Data_Init(void)
{    
    // 设置连续输出4个不同频率脉冲命令
    PWM4Data[0].val = PWM_CMD01_TYPE+4;  
    PWM4Data[1].val = PWM_MAX_FREQ/5;    // 第1个脉冲频率        
    PWM4Data[2].val = PWM_MAX_FREQ/5*2;  // 第2个脉冲频率
    PWM4Data[3].val = PWM_MAX_FREQ/5*3;  // 第3个脉冲频率
    PWM4Data[4].val = PWM_MAX_FREQ/5*4;  // 第4个脉冲频率
    
    // 设置连续输出10个相同频率脉冲命令
    PWM4Data[5].val = PWM_CMD10_TYPE+10;
    PWM4Data[6].val = PWM_MAX_FREQ;   // 这10个(第5个-第14个)脉冲频率  

    // 设置连续输出4个不同频率脉冲命令
    PWM4Data[7].val = PWM_CMD01_TYPE+4;  
    PWM4Data[8].val = PWM_MAX_FREQ/5*4;    // 第15个脉冲频率
    PWM4Data[9].val = PWM_MAX_FREQ/5*3;    // 第16个脉冲频率
    PWM4Data[10].val = PWM_MAX_FREQ/5*2;   // 第17个脉冲频率
    PWM4Data[11].val = PWM_MAX_FREQ/5;     // 第18个脉冲频率
    
    // 最后一个数据设置为0, 表示结束
    PWM4Data[PWM4_DATA_LEN].val = 0;
}
#endif


void App_TaskPWMFClk(void *p_arg)
{	 
	INT16U rcnt, val;
	INT32U cnt;
    INT16U cnt1,cnt2,cnt3,cnt4;
    INT32S QEICount1,QEICount2,QEICount3,QEICount4,flag;
	INT32U Dir = 0;
	(void)p_arg;
	
	
	cnt = 0;
	QEICount1 = 0;
    QEICount2 = 0;
    QEICount3 = 0;
    QEICount4 = 0;
	cnt1 = 0;
	cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
	
    #if (PWM1_EN > 0)
        #if (PWM1_MODE==PWM_DMA)    // DMA输出控制模式
        UserVars.PWM1WritePara.Flag = PWM_FREQ_FLAG; // 选择可变频率脉冲输出
        UserVars.PWM1WritePara.ch = PWM_CH1;         // 选择模式
        UserVars.PWM1WritePara.Freq = 0;             // 频率设置, 这个模式下默认0
        UserVars.PWM1WritePara.Rate = 0;             // 占空比设置, 这个模式下默认0  
        UserVars.PWM1WritePara.len = PWM1_DATA_LEN;  // 数据长度
        UserVars.PWM1WritePara.pData = PWM1Data;     // 设置PWM数据指针
        PWM1Data_Init();                             // 初始化PWM数据  
        #else
        PWM_Start(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode);   // 启动PWM1输出
        #endif
    #endif
    
    #if (PWM2_EN > 0)
        #if (PWM2_MODE==PWM_DMA)   // DMA输出控制模式
        UserVars.PWM2WritePara.Flag = PWM_FREQ_FLAG; // 选择可变频率脉冲输出
        UserVars.PWM2WritePara.ch = PWM_CH1;         // 选择模式
        UserVars.PWM2WritePara.Freq = 0;             // 频率设置, 这个模式下默认0
        UserVars.PWM2WritePara.Rate = 0;             // 占空比设置, 这个模式下默认0  
        UserVars.PWM2WritePara.len = PWM2_DATA_LEN;  // 数据长度
        UserVars.PWM2WritePara.pData = PWM2Data;     // 设置PWM数据指针
        PWM2Data_Init();                             // 初始化PWM数据   
        #else
        PWM_Start(PWM2_ID, PWM2_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM2_ID].Mode);   // 启动PWM2输出
        #endif
    #endif
    #if (PWM3_EN > 0)
        #if (PWM3_MODE==PWM_DMA)   // DMA输出控制模式
        UserVars.PWM3WritePara.Flag = PWM_FREQ_FLAG; // 选择可变频率脉冲输出
        UserVars.PWM3WritePara.ch = PWM_CH1;         // 选择模式
        UserVars.PWM3WritePara.Freq = 0;             // 频率设置, 这个模式下默认0
        UserVars.PWM3WritePara.Rate = 0;             // 占空比设置, 这个模式下默认0  
        UserVars.PWM3WritePara.len = PWM3_DATA_LEN;  // 数据长度
        UserVars.PWM3WritePara.pData = PWM3Data;     // 设置PWM数据指针
        PWM3Data_Init();                             // 初始化PWM数据   
        #else
        PWM_Start(PWM3_ID, PWM3_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM3_ID].Mode);   // 启动PWM3输出
        #endif   
    #endif
    #if (PWM4_EN > 0)
        #if (PWM4_MODE==PWM_DMA)   // DMA输出控制模式
        UserVars.PWM4WritePara.Flag = PWM_FREQ_FLAG; // 选择可变频率脉冲输出
        UserVars.PWM4WritePara.ch = PWM_CH1;         // 选择模式
        UserVars.PWM4WritePara.Freq = 0;             // 频率设置, 这个模式下默认0
        UserVars.PWM4WritePara.Rate = 0;             // 占空比设置, 这个模式下默认0  
        UserVars.PWM4WritePara.len = PWM4_DATA_LEN;  // 数据长度
        UserVars.PWM4WritePara.pData = PWM4Data;     // 设置PWM数据指针
        PWM4Data_Init();                             // 初始化PWM数据   
        #else
        PWM_Start(PWM4_ID, PWM4_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM4_ID].Mode);   // 启动PWM4输出
        #endif    
    #endif
#if (MODULE_CLASS == STM32F407XX)
    #if (PWM5_EN > 0)
    PWM_Start(PWM5_ID, PWM5_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM5_ID].Mode);   // 启动PWM5输出
    #endif
    #if (PWM6_EN > 0)
    PWM_Start(PWM6_ID, PWM6_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM6_ID].Mode);   // 启动PWM6输出
    #endif
    #if (PWM7_EN > 0)
    PWM_Start(PWM7_ID, PWM7_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM7_ID].Mode);   // 启动PWM7输出
    #endif
    #if (PWM8_EN > 0)
    PWM_Start(PWM8_ID, PWM8_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM8_ID].Mode);   // 启动PWM8输出
    #endif
#endif   
    
    #if (FCLK1_EN > 0) 
    FCLK_Ctrl(FCLK1_ID, CMD_FCLK_ENA, FCLK1CH_EN);  // 使能工作
    #endif
    #if (FCLK2_EN > 0) 
    FCLK_Ctrl(FCLK2_ID, CMD_FCLK_ENA, FCLK2CH_EN);  // 使能工作
    #endif
    #if (FCLK3_EN > 0) 
    FCLK_Ctrl(FCLK3_ID, CMD_FCLK_ENA, FCLK3CH_EN);  // 使能工作
    #endif
    #if (FCLK4_EN > 0) 
    FCLK_Ctrl(FCLK4_ID, CMD_FCLK_ENA, FCLK4CH_EN);  // 使能工作
    #endif
    
#if (MODULE_CLASS == STM32F407XX) 
    #if (FCLK5_EN > 0) 
    FCLK_Ctrl(FCLK5_ID, CMD_FCLK_ENA, FCLK5CH_EN);  // 使能工作
    #endif
    #if (FCLK6_EN > 0) 
    FCLK_Ctrl(FCLK6_ID, CMD_FCLK_ENA, FCLK6CH_EN);  // 使能工作
    #endif
    #if (FCLK7_EN > 0) 
    FCLK_Ctrl(FCLK7_ID, CMD_FCLK_ENA, FCLK7CH_EN);  // 使能工作
    #endif
    #if (FCLK8_EN > 0) 
    FCLK_Ctrl(FCLK8_ID, CMD_FCLK_ENA, FCLK8CH_EN);  // 使能工作
    #endif
#endif


    #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
    //TIM_Start(); // 启动所有定时器工作
    #endif    
    //Motor_Enable(StirFryMotor,Dir,0,20);
	while (1) 
	{
		UserVars.TaskRunStatus |= TASK_PWMFCLK_FLAG;  // 设置本任务运行状态标志
		Delay_ms(20);                                 // 延时20ms	
		
        cnt++;
		if ((cnt%150)==0)          // 每隔3秒执行一次
        {
			
            #if (PWM1_EN > 0)
                #if (PWM1_MODE==PWM_DMA)   // DMA输出控制模式
                //Delay_ms(10);
                PWM_Write(PWM1_ID, &UserVars.PWM1WritePara.Flag);
                #else
//				UserVars.PWMPara[PWM1_ID].Mode = PWM_FREQ_N;
//                PWM_Test(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode);  // PWM1输出测试
				
				Motor_Enable(PWM1_ID,Dir,UserVars.PWMPara[PWM1_ID].Freq,10);
				Dir=!Dir;
				UserVars.PWMPara[PWM1_ID].Freq += 1000;         // 每次增加1KHZ
				if (UserVars.PWMPara[PWM1_ID].Freq>10000)         // 大于10KHZ
				{
					UserVars.PWMPara[PWM1_ID].Freq = 1000;        // 重新设置1000HZ
				}	
                #endif
            #endif
            #if (PWM2_EN > 0)
                #if (PWM2_MODE==PWM_DMA)   // DMA输出控制模式
                //Delay_ms(10);
                PWM_Write(PWM2_ID, &UserVars.PWM2WritePara.Flag);
                #else
                PWM_Test(PWM2_ID, PWM2_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM2_ID].Mode);  // PWM2输出测试
                #endif            
            #endif
            #if (PWM3_EN > 0)
                #if (PWM3_MODE==PWM_DMA)   // DMA输出控制模式
                //Delay_ms(10);
                PWM_Write(PWM3_ID, &UserVars.PWM3WritePara.Flag);
                #else
                PWM_Test(PWM3_ID, PWM3_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM3_ID].Mode);  // PWM3输出测试
                #endif              
            #endif
            #if (PWM4_EN > 0)
                #if (PWM4_MODE==PWM_DMA)   // DMA输出控制模式
                //Delay_ms(10);
                PWM_Write(PWM4_ID, &UserVars.PWM4WritePara.Flag);
                #else
                PWM_Test(PWM4_ID, PWM4_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM4_ID].Mode);  // PWM4输出测试
                #endif 
            #endif
            
            #if (MODULE_CLASS == STM32F407XX) 
                #if (PWM5_EN > 0)
                PWM_Test(PWM5_ID, PWM5_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM5_ID].Mode);  // PWM5输出测试
                #endif
                #if (PWM6_EN > 0)
                PWM_Test(PWM6_ID, PWM6_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM6_ID].Mode);  // PWM6输出测试
                #endif
                #if (PWM7_EN > 0)
                PWM_Test(PWM7_ID, PWM7_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM7_ID].Mode);  // PWM7输出测试
                #endif
                #if (PWM8_EN > 0)
                PWM_Test(PWM8_ID, PWM8_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM8_ID].Mode);  // PWM8输出测试
                #endif
            #endif
            
            // 脉冲方向,使能管脚间隔3秒切换输出电平
//            #ifdef PWM1_DIR
//            IO_Ctrl(PWM1_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM1=DIR,%d\r\n", IO_Read(PWM1_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM1_ENA
//            IO_Ctrl(PWM1_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM1=ENA,%d\r\n", IO_Read(PWM1_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM2_DIR
//            IO_Ctrl(PWM2_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM2=DIR,%d\r\n", IO_Read(PWM2_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM2_ENA
//            IO_Ctrl(PWM2_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM2=ENA,%d\r\n", IO_Read(PWM2_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM3_DIR
//            IO_Ctrl(PWM3_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {            
//                printf("AT+PWM3=DIR,%d\r\n", IO_Read(PWM3_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM3_ENA
//            IO_Ctrl(PWM3_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM3=ENA,%d\r\n", IO_Read(PWM3_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM4_DIR
//            IO_Ctrl(PWM4_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM4=DIR,%d\r\n", IO_Read(PWM4_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM4_ENA
//            IO_Ctrl(PWM4_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM4=ENA,%d\r\n", IO_Read(PWM4_ENA));
//            }
//            #endif
//            #endif
            
             
            #if (FCLK1_EN > 0)                  
            FCLK_Test(FCLK1_ID, FCLK1_MODE);    // FCLK1输入测试  
            #endif
            #if (FCLK2_EN > 0)                  
            FCLK_Test(FCLK2_ID, FCLK2_MODE);    // FCLK2输入测试  
            #endif
            #if (FCLK3_EN > 0)                  
            FCLK_Test(FCLK3_ID, FCLK3_MODE);    // FCLK3输入测试  
            #endif
            #if (FCLK4_EN > 0)                  
            FCLK_Test(FCLK4_ID, FCLK4_MODE);    // FCLK4输入测试  
            #endif
            
            #if (MODULE_CLASS == STM32F407XX)
                #if (FCLK5_EN > 0)                  
                FCLK_Test(FCLK5_ID, FCLK5_MODE);    // FCLK5输入测试  
                #endif
                #if (FCLK6_EN > 0)                  
                FCLK_Test(FCLK6_ID, FCLK6_MODE);    // FCLK6输入测试  
                #endif
                #if (FCLK7_EN > 0)                  
                FCLK_Test(FCLK7_ID, FCLK7_MODE);    // FCLK7输入测试  
                #endif
                #if (FCLK8_EN > 0)                  
                FCLK_Test(FCLK8_ID, FCLK8_MODE);    // FCLK8输入测试  
                #endif
            #endif
            
            #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
            ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
            TIM_ReadCount();
            #endif
        }
        
        
        // 每隔20ms执行一次
        #if ((FCLK1_EN > 0)&&(FCLK1_MODE == FCLK_MODE_DECODE)) // FCLK1使能且是正交编码模式
        flag = FCLK_Read(FCLK1_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt1;
            cnt1 = rcnt;
            QEICount1 += (INT16S)val;
            
            UserVars.FCLK[FCLK1_ID].QEICount = QEICount1;
        }
        else
        {
            UserVars.FCLK[FCLK1_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK1=N,%d\r\n", QEICount1);
            }
            #endif
        }  
        #endif
        #if ((FCLK2_EN > 0)&&(FCLK2_MODE == FCLK_MODE_DECODE)) // FCLK2使能且是正交编码模式
        flag = FCLK_Read(FCLK2_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt2;
            cnt2 = rcnt;
            QEICount2 += (INT16S)val;
            
            UserVars.FCLK[FCLK2_ID].QEICount = QEICount2;
        }
        else
        {
            UserVars.FCLK[FCLK2_ID].QEICount = 0;
        }            
        if ((cnt%50)==0)
        {
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK2=N,%d\r\n", QEICount2);
            }
            #endif
        } 
        #endif
        #if ((FCLK3_EN > 0)&&(FCLK3_MODE == FCLK_MODE_DECODE)) // FCLK3使能且是正交编码模式
        flag = FCLK_Read(FCLK3_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt3;
            cnt3 = rcnt;
            QEICount3 += (INT16S)val;
            
            UserVars.FCLK[FCLK3_ID].QEICount = QEICount3;
        }
        else
        {
            UserVars.FCLK[FCLK3_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {            
                printf("AT+FCLK3=N,%d\r\n", QEICount3);
            }
        } 
        #endif
        #if ((FCLK4_EN > 0)&&(FCLK4_MODE == FCLK_MODE_DECODE)) // FCLK4使能且是正交编码模式
        flag = FCLK_Read(FCLK4_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt4;
            cnt4 = rcnt;
            QEICount4 += (INT16S)val;
            
            UserVars.FCLK[FCLK4_ID].QEICount = QEICount4;
        }
        else
        {
            UserVars.FCLK[FCLK4_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK4=N,%d\r\n", QEICount4);
            }
        } 
        #endif

    }
}

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/


//void PWMData_Init(INT8U id)
//{
//    if (id == 0)
//    {    
//        /*
//        PWMData1[0].val = 0;
//        PWMData1[0].Cmd.Type = 1;
//        PWMData1[0].Cmd.Size = 4;
//        
//        PWMData1[1].val = 200000;
//        PWMData1[2].val = 150000;
//        PWMData1[3].val = 100000;
//        PWMData1[4].val = 50000;
//        
//        PWMData1[5].val = 0;
//        PWMData1[5].Cmd.Type = 2;
//        PWMData1[5].Cmd.Size = 5;
//        PWMData1[6].val = 200000;

//        
//        PWMData1[7].val = 0;
//        PWMData1[7].Cmd.Type = 1;
//        PWMData1[7].Cmd.Size = 4;
//        PWMData1[8].val = 50000;
//        PWMData1[9].val = 100000;
//        PWMData1[10].val = 150000;
//        PWMData1[11].val = 200000;
//        */
//        
//        
//        PWMData1[0].val = 0;
//        PWMData1[0].Cmd.Type = 1;
//        PWMData1[0].Cmd.Size = 4;
//        
//        PWMData1[1].val = 100000;
//        PWMData1[2].val = 80000;
//        PWMData1[3].val = 60000;
//        PWMData1[4].val = 50000;
//        
//        PWMData1[5].val = 0;
//        PWMData1[5].Cmd.Type = 2;
//        PWMData1[5].Cmd.Size = 5;
//        PWMData1[6].val = 100000;

//        
//        PWMData1[7].val = 0;
//        PWMData1[7].Cmd.Type = 1;
//        PWMData1[7].Cmd.Size = 4;
//        PWMData1[8].val = 50000;
//        PWMData1[9].val = 70000;
//        PWMData1[10].val = 90000;
//        PWMData1[11].val = 100000;
//        
//    }
//    if (id == 1)
//    {    
//        /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 1000;
//        PWMData2[2].val = 1500;
//        PWMData2[3].val = 2000;
//        PWMData2[4].val = 3000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 4;
//        PWMData2[6].val = 5000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 3000;
//        PWMData2[9].val = 2000;
//        PWMData2[10].val = 1500;
//        PWMData2[11].val = 1000;
//        */
//        /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 10000;
//        PWMData2[2].val = 15000;
//        PWMData2[3].val = 20000;
//        PWMData2[4].val = 30000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 4;
//        PWMData2[6].val = 50000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 30000;
//        PWMData2[9].val = 20000;
//        PWMData2[10].val = 15000;
//        PWMData2[11].val = 10000;
//        */
//        
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 100000;
//        PWMData2[2].val = 80000;
//        PWMData2[3].val = 60000;
//        PWMData2[4].val = 50000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 10;
//        PWMData2[6].val = 100000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 50000;
//        PWMData2[9].val = 70000;
//        PWMData2[10].val = 90000;
//        PWMData2[11].val = 100000;
//        
//        
//       /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 200000;
//        PWMData2[2].val = 150000;
//        PWMData2[3].val = 100000;
//        PWMData2[4].val = 50000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 10;
//        PWMData2[6].val = 200000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 50000;
//        PWMData2[9].val = 100000;
//        PWMData2[10].val = 150000;
//        PWMData2[11].val = 200000;
//        */
//    }
//}

