/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: rtc.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是RTC硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S RTC_Init(void);
*          2. INT32S RTC_Read(RTC_TIME *rtc);
*          3. INT32S RTC_Write(RTC_TIME *rtc);
*          4. INT32U RTC_Ctrl(INT8U Cmd, INT32U Para, RTC_TIME *rtc);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __RTC_H 
#define __RTC_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
#include "config.h"

/*************************************************************************************/
//  日期时间数据结构定义, 以下定义绝对不能修改
/*************************************************************************************/
typedef struct
{
	INT8U  year;
	INT8U  month;
	INT8U  day;
	INT8U  hour;
	INT8U  minute;
	INT8U  second;
	INT8U  week;
    INT8U  flag;   // 新增标志位
    INT16U ss;     // 新增亚秒值, Modify 2019.11.30
}RTC_TIME;

/************************************************************************************/
// STM32F4_M4 常量定义
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
#define RTC_IT_ALRA       0x0001  // RTC闹钟A中断(使能标志)
#define RTC_IT_ALRB       0x0002  // RTC闹钟B中断(使能标志)
#define RTC_IT_WKUPIT     0x0004  // RTC唤醒中断(使能标志)
#define RTC_IT_TSF        0x0008  // RTC时间戳中断(使能标志)
#define RTC_IT_TSFOVF     0x0010  // RTC时间戳溢出中断(使能标志)
#define RTC_IT_TAMP1      0x0020  // RTC入侵检测1中断(使能标志)
#define RTC_IT_TAMP2      0x0040  // RTC入侵检测2中断(使能标志)

// Flag标志位定义
#define RTC_OUT_BCD_FLAG        0x80000000     // RTC读写函数中日期和时间数据格式: BIT31=1,采用BCD格式输出; BIT31=0,采用BIN格式输出

// RTC时钟源选择, 以下4种只能选择一种
#define RTC_CLK_LSE_FLAG        0x40000000     // RTC时钟选择LSE标志, 外部必须是32768HZ无源晶振
#define RTC_CLK_LSI_FLAG        0x20000000     // RTC时钟选择LSI标志
#define RTC_CLK_HSEDIV_FLAG     0x10000000     // RTC时钟选择HSE分频标志
#define RTC_CLK_LSEBYP_FLAG     0x08000000     // RTC时钟选择LSE有源时钟标志,最高1MHZ, 内部必须旁路LSE振荡器

#define RTC_CR_COE_EN           0x00800000     // 使能校准输出(使能512Hz或1Hz时钟输出到RTC_AF1)                     
#define RTC_CR_OSEL_A           0x00200000     // 输出使能选择：闹钟A                     
#define RTC_CR_OSEL_B           0x00400000     // 输出使能选择：闹钟B                    
#define RTC_CR_OSEL_WUT         0x00600000     // 输出使能选择：唤醒输出                     
#define RTC_CR_POL_L            0x00100000     // 输出极性: bit20=1,低电平; bit20=0, 高电平                           
#define RTC_CR_COSEL_1HZ        0x00080000     // 校准输出选择: bit19=1, 1HZ输出; bit19=0, 512HZ输出; 
#define RTC_CR_TSIE_EN          0x00008000     // 使能时间戳中断                    
#define RTC_CR_WUTIE_EN         0x00004000     // 使能唤醒定时器中断                     
#define RTC_CR_ALRBIE_EN        0x00002000     // 使能闹钟B中断                    
#define RTC_CR_ALRAIE_EN        0x00001000     // 使能闹钟A中断                  
#define RTC_CR_TSE_EN           0x00000800     // 使能时间戳                        
#define RTC_CR_WUTE_EN          0x00000400     // 使能唤醒定时器                      
#define RTC_CR_ALRBE_EN         0x00000200     // 使能闹钟B                   
#define RTC_CR_ALRAE_EN         0x00000100     // 使能闹钟A                     
#define RTC_CR_DCE_EN           0x00000080     // 使能数字校准
#define RTC_CR_BYPSHAD_EN       0x00000020     // 旁路影子寄存器
#define RTC_CR_REFCKON_EN       0x00000010     // 使能参考时钟检验          
#define RTC_CR_TSEDGE           0x00000008     // 时间戳事件有效边沿: bit3=1, 下降边沿; bit3=0, 上升边沿;                         
                  
typedef struct
{
	INT32U Flag;              // 参数标志
    INT32U LSEVal;            // 低速外部时钟频率   
	//INT8U  WUCKSel;           // 唤醒时钟选择: 0, 选择RTC/16时钟; 1, 选择RTC/8时钟; 2, 选择RTC/4时钟; 3, 选择RTC/2时钟; 4, 选择1HZ; 6, 选择1HZ, WUT计数值增加2的16次方; 
}RTC_PARA;

// RTC_TIME数据结构中, 新增Flag标志定义如下: 
#define RTC_DATA_BCD_FLAG       0x01  // bit0=1, BCD码数据格式; bit0=0, BIN码数据格式;

// 设置闹钟(CMD_RTC_SET_ALRMA_RTC/CMD_RTC_SET_ALRMB_RTC), 参数Para定义
#define RTC_ALARM_SS_FLAG       ((INT32U)0x0001)  // 闹钟亚秒屏蔽标志
#define RTC_ALARM_SECOND_FLAG   ((INT32U)0x0002)  // 闹钟秒屏蔽标志
#define RTC_ALARM_MINUTE_FLAG   ((INT32U)0x0004)  // 闹钟分钟屏蔽标志
#define RTC_ALARM_HOUR_FLAG     ((INT32U)0x0008)  // 闹钟小时屏蔽标志
#define RTC_ALARM_DAY_FLAG      ((INT32U)0x0010)  // 闹钟日屏蔽标志
#define RTC_ALARM_WDSEL_FLAG    ((INT32U)0x0020)  // 闹钟星期选择标志
#define RTC_ALARM_IT_FLAG       ((INT32U)0x0040)  // 使能闹钟中断标志
#define RTC_ALARM_OSEL_A_FLAG   ((INT32U)0x0080)  // 选择闹钟A输出
#define RTC_ALARM_OSEL_B_FLAG   ((INT32U)0x0100)  // 选择闹钟B输出
#define RTC_ALARM_OPOL_FLAG     ((INT32U)0x0200)  // 闹钟输出极性选择: Para&(~RTC_ALARM_OPOL_FLAG), 高定平; Para|RTC_ALARM_OPOL_FLAG, 低电平; 
#define RTC_ALARM_OTYPE_FLAG    ((INT32U)0x0400)  // 闹钟输出极性选择: Para&(~RTC_ALARM_OTYPE_FLAG), 开漏输出; Para|RTC_ALARM_OTYPE_FLAG, 推挽输出; 
#define RTC_ALARM_MASKSS_FLAG   ((INT32U)0xF000)  // 闹钟亚秒屏蔽位; 


// RTC_Ctrl() Cmd命令
#define CMD_RTC_CTRL            0    // 设置RTC控制参数命令, Para是命令参数
#define CMD_RTC_GET_TSDTR       1    // 读取时间戳时间和日期, 返回值在*rtc里
#define CMD_RTC_SET_ALRMA_RTC   2    // 设置闹钟A, 配置参数在Para里, 时间参数在*rtc里 
#define CMD_RTC_SET_ALRMB_RTC   3    // 设置闹钟B, 配置参数在Para里, 时间参数在*rtc里 
#define CMD_RTC_CLR_ALRMA_RTC   4    // 清除闹钟A  
#define CMD_RTC_CLR_ALRMB_RTC   5    // 清除闹钟B  

#define CMD_RTC_SET_WUTR        6    // 设置唤醒寄存器, Para参数范围: 1~65535
//#define CMD_RTC_SET_IT          7    // 设置RTC中断  
//#define CMD_RTC_CLR_IT          8    // 清除RTC中断  


#define CMD_RTC_SET_ALRMAR      17    // 设置闹钟A寄存器, 参数在Para里 
#define CMD_RTC_SET_ALRMBR      18    // 设置闹钟B寄存器, 参数在Para里
#define CMD_RTC_GET_ALRMAR      19    // 读取闹钟A寄存器, 参数在Para里 
#define CMD_RTC_GET_ALRMBR      20    // 读取闹钟B寄存器, 参数在Para里
#define CMD_RTC_GET_SSR         21    // 读取亚秒寄存器   
#define CMD_RTC_GET_TSSSR       22   // 当发生时间戳事件, 读取时间戳亚秒寄存器  
#define CMD_RTC_SET_CALIBR      23    // 设置校准寄存器
#define CMD_RTC_SET_CALR        24    // 设置校准寄存器
#define CMD_RTC_GET_CALIBR      25    // 读取校准寄存器
#define CMD_RTC_GET_CALR        26    // 读取校准寄存器
#define CMD_RTC_SET_TAFCR       27    // 设置RTC入侵和复用功能配置寄存器
#define CMD_RTC_GET_TAFCR       28    // 读取RTC入侵和复用功能配置寄存器
#define CMD_RTC_SET_SHIFTR      29    // 设置平移寄存器  


#define CMD_RTC_SET_BKP0R    30
#define CMD_RTC_SET_BKP1R    (CMD_RTC_SET_BKP0R+1)
#define CMD_RTC_SET_BKP2R    (CMD_RTC_SET_BKP0R+2)
#define CMD_RTC_SET_BKP3R    (CMD_RTC_SET_BKP0R+3)
#define CMD_RTC_SET_BKP4R    (CMD_RTC_SET_BKP0R+4)
#define CMD_RTC_SET_BKP5R    (CMD_RTC_SET_BKP0R+5)
#define CMD_RTC_SET_BKP6R    (CMD_RTC_SET_BKP0R+6)
#define CMD_RTC_SET_BKP7R    (CMD_RTC_SET_BKP0R+7)
#define CMD_RTC_SET_BKP8R    (CMD_RTC_SET_BKP0R+8)
#define CMD_RTC_SET_BKP9R    (CMD_RTC_SET_BKP0R+9)
#define CMD_RTC_SET_BKP10R    (CMD_RTC_SET_BKP0R+10)
#define CMD_RTC_SET_BKP11R    (CMD_RTC_SET_BKP0R+11)
#define CMD_RTC_SET_BKP12R    (CMD_RTC_SET_BKP0R+12)
#define CMD_RTC_SET_BKP13R    (CMD_RTC_SET_BKP0R+13)
#define CMD_RTC_SET_BKP14R    (CMD_RTC_SET_BKP0R+14)
#define CMD_RTC_SET_BKP15R    (CMD_RTC_SET_BKP0R+15)
#define CMD_RTC_SET_BKP16R    (CMD_RTC_SET_BKP0R+16)
#define CMD_RTC_SET_BKP17R    (CMD_RTC_SET_BKP0R+17)
#define CMD_RTC_SET_BKP18R    (CMD_RTC_SET_BKP0R+18)
#define CMD_RTC_SET_BKP19R    (CMD_RTC_SET_BKP0R+19)

#define CMD_RTC_GET_BKP0R    50
#define CMD_RTC_GET_BKP1R    (CMD_RTC_GET_BKP0R+1)
#define CMD_RTC_GET_BKP2R    (CMD_RTC_GET_BKP0R+2)
#define CMD_RTC_GET_BKP3R    (CMD_RTC_GET_BKP0R+3)
#define CMD_RTC_GET_BKP4R    (CMD_RTC_GET_BKP0R+4)
#define CMD_RTC_GET_BKP5R    (CMD_RTC_GET_BKP0R+5)
#define CMD_RTC_GET_BKP6R    (CMD_RTC_GET_BKP0R+6)
#define CMD_RTC_GET_BKP7R    (CMD_RTC_GET_BKP0R+7)
#define CMD_RTC_GET_BKP8R    (CMD_RTC_GET_BKP0R+8)
#define CMD_RTC_GET_BKP9R    (CMD_RTC_GET_BKP0R+9)
#define CMD_RTC_GET_BKP10R    (CMD_RTC_GET_BKP0R+10)
#define CMD_RTC_GET_BKP11R    (CMD_RTC_GET_BKP0R+11)
#define CMD_RTC_GET_BKP12R    (CMD_RTC_GET_BKP0R+12)
#define CMD_RTC_GET_BKP13R    (CMD_RTC_GET_BKP0R+13)
#define CMD_RTC_GET_BKP14R    (CMD_RTC_GET_BKP0R+14)
#define CMD_RTC_GET_BKP15R    (CMD_RTC_GET_BKP0R+15)
#define CMD_RTC_GET_BKP16R    (CMD_RTC_GET_BKP0R+16)
#define CMD_RTC_GET_BKP17R    (CMD_RTC_GET_BKP0R+17)
#define CMD_RTC_GET_BKP18R    (CMD_RTC_GET_BKP0R+18)
#define CMD_RTC_GET_BKP19R    (CMD_RTC_GET_BKP0R+19)

#define CMD_RTC_BKPR_SIZE     20

#endif

/************************************************************************************/
// STM32F1_M3 常量定义
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
// RTC时钟源选择, 以下3种只能选择一种
#define RTC_CLK_LSE_FLAG        0x40000000     // RTC时钟选择LSE标志
#define RTC_CLK_LSI_FLAG        0x20000000     // RTC时钟选择LSI标志
#define RTC_CLK_HSEDIV_FLAG     0x10000000     // RTC时钟选择HSE分频标志
#define RTC_CLK_LSEBYP_FLAG     0x08000000     // RTC时钟选择LSE有源时钟标志,最高1MHZ, 内部必须旁路LSE振荡器

#define RTC_IT_SEC     0x0001  // 秒中断标志
#define RTC_IT_ALARM   0x0002  // 闹钟中断标志
#define RTC_IT_OW      0x0004  // 计数器溢出中断

// RTC_Ctrl RTC控制函数命令
#define CMD_RTC_GET_COUNTER  0    // 读取RTC计数器值命令
#define CMD_RTC_SET_COUNTER  1    // 设置RTC计数器值命令
#define CMD_RTC_SET_ALMTIM   2    // 设置闹钟时间, 利用*rtc指针变量传入产生闹钟的时间
#define CMD_RTC_SET_ALMTIM_XS 3   // 设置在当前时间延后X秒产生闹钟, 利用变量Para传入延后的时间单位秒
#define CMD_RTC_SET_ALMCOUNT 4    // 设置闹钟计数值, 利用变量Para传入产生闹钟的计数值


#define CMD_RTC_SET_CAL      5    // 设置校准值
#define CMD_RTC_SET_1SPLUS   6    // 设置PC13(IO46)输出秒脉冲
#define CMD_RTC_SET_ALARM    7    // 设置PC13(IO46)输出闹钟脉冲
#define CMD_RTC_SET_COO      8    // 设置PC13(IO46)输出校准时钟脉冲
#define CMD_RTC_STOP_PC13    9    // 停止PC13输出脉冲

#define CMD_RTC_SECOND_INT   10   // Para是ENABLE设置秒中断, Para是DISABLE清除秒中断
#define CMD_RTC_ALARM_INT    11   // Para是ENABLE设置报警中断, Para是DISABLE清除报警中断

typedef struct
{
	INT32U Flag;            // 参数标志
    INT32U LSEVal;          // 低速外部时钟频率   
}RTC_PARA;



#endif
/************************************************************************************
//
//                 RTC硬件驱动程序
//
/*************************************************************************************

/*************************************************************************************
* Function: RTC_Init;
*
* Description: RTC初始化函数;
*              
* Input:  pPara, 参数指针;
*                 
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S RTC_Init(RTC_PARA *pPara);

/***********************************************************************************
* Function: RTC_Read;
*
* Description: 读时间;
*              
* Input:   none;
*
* Output:  *rtc, RTC时间数据指针;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   输出的时间数据是十六进制数而不是BCD码;
*         星期寄存器的数字范围是0～6，0表示星期日，1表示星期一，... 6表示星期六，7无定义
************************************************************************************/
INT32S RTC_Read(RTC_TIME *rtc);

/***********************************************************************************
* Function: RTC_Write;
*
* Description: 写时间;
*              
* Input:  *rtc, RTC时间数据指针;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   输入的时间数据是十六进制数而不是BCD码;
*         星期寄存器的数字范围是0～6，0表示星期日，1表示星期一，... 6表示星期六，7无定义
************************************************************************************/
INT32S RTC_Write(RTC_TIME *rtc);

/***********************************************************************************
* Function: RTC_Ctrl;
*
* Description: RTC控制函数;
*              
* Input:  Cmd,  控制命令: 
*         CMD_RTC_GET_COUNTER, 读取RTC计数器值命令
*         CMD_RTC_SET_COUNTER, 设置RTC计数器值命令
*         CMD_RTC_SET_ALMTIM,  设置闹钟时间
*         CMD_RTC_GET_ALMCOUNT 读取闹钟计数器值命令
*         CMD_RTC_SET_ALMCOUNT 设置闹钟计数值
*         CMD_RTC_SET_CAL,     设置校准值
*         CMD_RTC_SET_1SPLUS,  设置PC13(IO46)输出秒脉冲
*         CMD_RTC_SET_ALARM,   设置PC13(IO46)输出闹钟脉冲
*         CMD_RTC_SET_COO,     设置PC13(IO46)输出校准时钟脉冲
*         CMD_RTC_STOP_PC13,   停止PC13输出脉冲;
*         CMD_RTC_SECOND_INT,  Para是ENABLE设置秒中断, Para是DISABLE清除秒中断
*         CMD_RTC_ALARM_INT,   Para是ENABLE设置报警中断, Para是DISABLE清除报警中断
*         Para, 命令参数;
*
* Output: none;
*
* Return: 除返回数据指令外, 返回：ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S RTC_Ctrl(INT8U Cmd, INT32U Para, RTC_TIME *rtc);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
