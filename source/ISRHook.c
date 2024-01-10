/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: ISRHook.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2020.2.12			
* Email:   EmbedARM@126.com
* Modify:  1. 删除原有所有DMA/SPI/I2C中断钩子函数;
*          2. 删除所有SPI中断钩子函数; 
*          2. 删除所有I2C中断钩子函数; 
*
* Description: 本文件负责整个系统中断处理函数;
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
// 引用外部头文件
/************************************************************************************/
#include "config.h"
#include "UserVars.h"
#include <stdio.h>
#include "ISRHook.h"
#include "vars.h"
#include "dma.h"
#include "GPIO_manager.h"
#if	(UCOS_II_EN == 1)
#include "OSVars.h"
#endif

/************************************************************************************/
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/

/***********************************************************************************
* Function: Uart1_ISRHook,Uart2_ISRHook,Uart3_ISRHook,Uart4_ISRHook,Uart5_ISRHook,Uart6_ISRHook;
*
* Description: 以下函数是Uart1,Uart2,Uart3,Uart4,Uart5中断及接收数据的钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   本函数只能根据串口状态UartSR编写接收数据程序, 发送数据由内部中断实现;
************************************************************************************/
#define USART_FLAG_RXNE ((INT16U)0x0020)
void Uart1_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
		printf("uart1 rx 0x%x\r\n",Data);
	}	
}

void Uart2_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
	}
}

void Uart3_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
	}
}

void Uart4_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
	}
}

void Uart5_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
		printf("uart5 rx 0x%x\r\n",Data);
	}
}

#if (MODULE_CLASS == STM32F407XX)
void Uart6_ISRHook(INT16U UartSR, INT16U Data)
{
    // 以下编写自己的中断处理程序
    if(UartSR&USART_FLAG_RXNE) // 接收到数据
	{				
		UserVars.UartData = Data;  // 读取接收到的数据
	}
}
#endif

/***********************************************************************************
* Function: SPI1_ISRHook,SPI2_ISRHook,SPI2_ISRHook;
*
* Description: 以下函数是SPI1,SPI2,SPI3钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void SPI1_ISRHook(INT32U flag)
{
    // 以下编写自己的中断处理程序
}

void SPI2_ISRHook(INT32U flag)
{
    // 以下编写自己的中断处理程序
}

void SPI3_ISRHook(INT32U flag)
{
    // 以下编写自己的中断处理程序
}

/************************************************************************************
//
//                 中断的钩子函数
//
*************************************************************************************/

/***********************************************************************************
* Function: RTC_ISRHook;
*
* Description: 以下函数是RTC中断的钩子函数;
*           
* Input:  flag, 中断标志; cnt, RTC 32位计数器值
*
* Output: none;
*          		
* Return: none;
*
* Note:   此中断只有在STM32F10X模块上存在;
************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
void RTC_ISRHook(INT8U flag, INT32U cnt)
{

    // 以下编写自己的中断处理程序
    #if (RTC_SECIT_EN > 0)  // RTC秒中断
	if (flag&RTC_IT_SEC)    // 秒中断
    {
        UserVars.Flag |= RTC_SECIT_FLAG; // 设置RTC秒中断标志
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC产生秒中断\r\n");
        }
        #endif        
    }
    #endif
    
    #if (RTC_ALRIT_EN > 0)  // RTC闹钟中断
    if (flag&RTC_IT_ALARM)  // 闹钟中断
    {
        UserVars.Flag |= RTC_ALRIT_FLAG; // 设置RTC闹钟中断标志
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC产生闹钟报警中断\r\n");
        }
        #endif        
        
    }
    #endif
    
    /* 不会产生计数器溢出中断
    if (flag&RTC_IT_OW)     // 计数器溢出
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC产生计数器溢出中断:%d\r\n", cnt);
        }
        #endif 
    } 
    */   

    
//// Modify 2019.12.1 新增
//#if (MODULE_CLASS == STM32F407XX)
//    #if (RTC_ALRIT_EN > 0)  // RTC唤醒中断使能
//    if (flag&RTC_IT_WKUPIT) // RTC唤醒中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC唤醒中断\r\n");
//        }   
//        #endif
//    }
//    #endif

//    #if ( RTC_ALRAIT_EN > 0)  // RTC闹钟A中断使能
//    if (flag&RTC_IT_ALRA)     // RTC闹钟A中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC闹钟A中断\r\n");
//        }   
//        #endif
//    }
//    #endif
//    
//    #if ( RTC_ALRBIT_EN > 0)  // RTC闹钟B中断使能
//    if (flag&RTC_IT_ALRB)     // RTC闹钟B中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC闹钟B中断\r\n");
//        }   
//        #endif
//    } 
//    #endif
//    
//    #if (RTC_TSFIT_EN  > 0)  // RTC时间戳中断使能
//    if (flag&RTC_IT_TSF)     // RTC时间戳中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC闹钟B中断\r\n");
//        }   
//        #endif
//    }  
//    #endif

//    #if (RTC_TAMP1IT_EN  > 0)  // RTC入侵检测1中断使能
//    if (flag&RTC_IT_TAMP1)     // RTC入侵检测1中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC入侵检测1中断\r\n");
//        }   
//        #endif
//    }   
//    #endif    
//    #if (RTC_TAMP2IT_EN  > 0)  // RTC入侵检测2中断使能
//    if (flag&RTC_IT_TAMP1)     // RTC入侵检测2中断
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC入侵检测2中断\r\n");
//        }   
//        #endif
//    } 
//    #endif
//#endif    
}
#endif

/***********************************************************************************
* Function: TIM1_BRK_ISRHook, TIM1_UP_ISRHook, TIM1_TRG_COM_ISRHook, TIM1_CC_ISRHook, 
*			TIM8_BRK_ISRHook, TIM8_UP_ISRHook, TIM8_TRG_COM_ISRHook, TIM8_CC_ISRHook
*
* Description: 本函数是TIM1、TIM8中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void TIM1_BRK_ISRHook(INT32U flag)   // TIM1 Break  Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // 将中断标志存入全局变量
    if (flag&TIM_BRKIT_FLAG)  // TIM1 Break Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1 Break Interrupts\r\n");
        }
        #endif
    }
}    

void TIM1_UP_ISRHook(INT32U flag)	  // TIM1 Update Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM1主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1定时器中断\r\n");
        }
        #endif
    }
}

void TIM1_TRG_COM_ISRHook(INT32U flag)  // TIM1 Trig & Commutation Interrupts
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_COMIT_FLAG)  // TIM1 Commutation Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1 Commutation Interrupts\r\n");
        }
        #endif
    }
    
    if (flag&TIM_TRGIT_FLAG)  // TIM1 Trigger Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1 Trigger Interrupts\r\n");
        }
        #endif
    } 
}

void TIM1_CC_ISRHook(INT32U flag)		  // TIM1 Capture Compare Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_CH1IT_FLAG)  // TIM1 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM1 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM1 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM1 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH4子定时器4中断\r\n");
        }
        #endif 
    }
}

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
void TIM8_BRK_ISRHook(INT32U flag)	 // TIM8 Break  Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_BRKIT_FLAG)  // TIM8 Break Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8 Break Interrupts\r\n");
        }
        #endif        
    }
}

void TIM8_UP_ISRHook(INT32U flag)		 // TIM8 Update Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM8主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8定时器中断\r\n");
        }
        #endif 
    }
}

void TIM8_TRG_COM_ISRHook(INT32U flag) // TIM8 Trig & Commutation Interrupts
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_COMIT_FLAG)  // TIM8 Commutation Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8 Commutation Interrupts\r\n");
        }
        #endif         
    }
    
    if (flag&TIM_TRGIT_FLAG)  // TIM8 Trigger Interrupts
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8 Trigger Interrupts\r\n");
        }
        #endif         
    } 
}

void TIM8_CC_ISRHook(INT32U flag)		 // TIM8 Capture Compare Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // 将中断标志存入全局变量
        
    if (flag&TIM_CH1IT_FLAG)  // TIM8 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM8 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM8 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM8 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH4子定时器4中断\r\n");
        }
        #endif 
    }
}
#endif
/***********************************************************************************
* Function: TIM2_ISRHook, TIM3_ISRHook, TIM4_ISRHook, 
*			TIM5_ISRHook, TIM6_ISRHook, TIM7_ISRHook
*
* Description: 本函数是TIM2~TIM7中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void TIM2_ISRHook(INT32U flag)		 // TIM2 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM2_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM2主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2定时器中断\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM2 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM2 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM2 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM2 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH4子定时器4中断\r\n");
        }
        #endif 
    }   
}

void TIM3_ISRHook(INT32U flag)		 // TIM3 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM3_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM3主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3定时器中断\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM3 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM3 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM3 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM3 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH4子定时器4中断\r\n");
        }
        #endif 
    }   
}

void TIM4_ISRHook(INT32U flag)		 // TIM4 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM4_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM4主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4定时器中断\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM4 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM4 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM4 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM4 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH4子定时器4中断\r\n");
        }
        #endif 
    }     
}

void TIM5_ISRHook(INT32U flag)		 // TIM5 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM5_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM5主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5定时器中断\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM5 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH1子定时器1中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM5 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH2子定时器2中断\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM5 CH3子定时器3中断标志(捕获/比较3中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH3子定时器3中断\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM5 CH4子定时器4中断标志(捕获/比较4中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH4子定时器4中断\r\n");
        }
        #endif 
    }   
}

void TIM6_ISRHook(INT32U flag)		 // TIM6 Global Interrupt
{
	TIM_CTRL TIMCtrl;
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM6_ID] |= flag;     // 将中断标志存入全局变量
	if(UserVars.Tim6Pul!=ALL_FF_32)
	{
		if(UserVars.Tim6Pul)
		{
			UserVars.Tim6Pul--;
		}
		else
		{	
			TIMCtrl.Chx = TIM6_EN;
			TIMCtrl.t = TIM6_T;  	
			Timer_Ctrl(TIM6_ID,CMD_TIM_DIS,(TIM_CTRL *)&TIMCtrl.Chx);
			printf("Close Tim6!!\r\n");
			IOFunction_Write(StirPUL,0);
			return;
		}
		
	}
    IOFunction_Ctrl(StirPUL,CMD_IO_NEG,0);
}

void TIM7_ISRHook(INT32U flag)		 // TIM7 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM7_ID] |= flag;     // 将中断标志存入全局变量
    #if (DEBUG_ISRHOOK_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM7定时器中断\r\n");
    }
    #endif
}

/***********************************************************************************
* Function: TIM9_ISRHook, TIM10_ISRHook, TIM11_ISRHook, 
*			TIM12_ISRHook, TIM13_ISRHook, TIM14_ISRHook
*
* Description: 本函数是TIM9~TIM14中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
void TIM9_ISRHook(INT32U flag)		 // TIM9 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM9_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM9主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9定时器中断\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM12 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9CH1子定时器1中断\r\n");
        }
        #endif
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM12 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {        
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9CH2子定时器2中断\r\n");
        }
        #endif
    }                   
}

void TIM10_ISRHook(INT32U flag)		 // TIM10 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM10_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM10主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM10定时器中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM10CH1子定时器1中断\r\n");
        }
        #endif 
    }
}

void TIM11_ISRHook(INT32U flag)		 // TIM11 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM11_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM11主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM11定时器中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM11CH1子定时器1中断\r\n");
        }
        #endif 
    }
}

void TIM12_ISRHook(INT32U flag)		 // TIM12 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM12_ID] |= flag;     // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM12主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12定时器中断\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM12 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12CH1子定时器1中断\r\n");
        }
        #endif
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM12 CH2子定时器2中断标志(捕获/比较2中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {        
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12CH2子定时器2中断\r\n");
        }
        #endif
    }          
}

void TIM13_ISRHook(INT32U flag)		 // TIM13 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM13_ID] |= flag;    // 将中断标志存入全局变量
    
    if (flag&TIM_IT_FLAG)     // TIM13主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM13定时器中断\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM13 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM13CH1子定时器1中断\r\n");
        }
        #endif        
    }
}

void TIM14_ISRHook(INT32U flag)		 // TIM14 Global Interrupt
{
    // 以下编写自己的中断处理程序
    UserVars.TIMx_ITFlag[TIM14_ID] |= flag;     // 将中断标志存入全局变量    
    if (flag&TIM_IT_FLAG)     // TIM14主定时器中断标志(更新中断) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM14定时器中断\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1子定时器1中断标志(捕获/比较1中断)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM14CH1子定时器1中断\r\n");
        }
        #endif 
    }
}
#endif


/***********************************************************************************
* Function: EXTI16_PVD_ISRHook, EXTI17_RTCAlarm_ISRHook, EXTI8_USBWakeUp_ISRHook,
*           EXTI19_NETWakeUp_ISRHook;
*
* Description: 以下函数是EXTI16~EXTI19中断的钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void EXTI16_PVD_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI16_PVD_EN > 0)
    UserVars.EXTIFlag |= EXTI16_PVD_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI16 PVD产生中断\r\n");
    }
    #endif  
    #endif     
}

// RTC闹钟中断
void  EXTI17_RTCAlarm_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI17_RTCAlarm_EN > 0)
    UserVars.EXTIFlag |= EXTI17_RTCAlarm_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI17 RTCAlarm产生中断\r\n");
    }
    #endif  
    #endif     
}

void  EXTI18_USBWakeUp_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI18_USBWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI18_USBWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI18 USBWakeUp产生中断\r\n");
    }
    #endif  
    #endif      
}

void  EXTI19_NETWakeUp_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI19_NETWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI19_NETWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI19 NETWakeUp产生中断\r\n");
    }
    #endif  
    #endif     
}

#if (MODULE_CLASS == STM32F407XX)
void  EXTI20_USBHSWakeUp_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI20_USBHSWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI21_USBHSWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI20 USBHSWakeUp产生中断\r\n");
    }
    #endif  
    #endif      
}

// RTC入侵和时间戳中断
void  EXTI21_RTCTSE_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI21_RTCTSE_EN > 0)
    UserVars.EXTIFlag |= EXTI21_RTCTSE_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI21 RTCTSE产生中断\r\n");
    }
    #endif  
    #endif    
}

// RTC唤醒中断
void  EXTI22_RTCWakeUp_ISRHook(INT32U Flag)
{
    // 以下编写自己的中断处理程序
    #if (EXTI22_RTCWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI22_RTCWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI22 RTCWakeUp产生中断\r\n");
    }
    #endif  
    #endif
}
#endif

 
/***********************************************************************************
* Function: EXTI0_ISRHook, EXTI1_ISRHook, EXTI2_ISRHook, EXTI3_ISRHook;
*           EXTI4_ISRHook, EXTI5_ISRHook, EXTI6_ISRHook, EXTI7_ISRHook,
*           EXTI8_ISRHook, EXTI9_ISRHook, EXTI10_ISRHook, EXTI11_ISRHook,
*           EXTI12_ISRHook, EXTI13_ISRHook, EXTI14_ISRHook, EXTI15_ISRHook,
*
* Description: 以下函数是外部IO 16个中断函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void EXTI0_ISRHook(void)
{ 
    // 以下编写自己的中断处理程序
    #if (EXTI0_EN > 0)
    UserVars.EXTIFlag |= EXTI0_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI0产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI1_ISRHook(void)
{  
	// 以下编写自己的中断处理程序
    #if (EXTI1_EN > 0)
    UserVars.EXTIFlag |= EXTI1_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI1产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI2_ISRHook(void)
{ 
	// 以下编写自己的中断处理程序
    #if (EXTI2_EN > 0)
    UserVars.EXTIFlag |= EXTI2_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI2产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI3_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI3_EN > 0)
    UserVars.EXTIFlag |= EXTI3_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI3产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI4_ISRHook(void)
{
    // 以下编写自己的中断处理程序
    #if (EXTI4_EN > 0)
    UserVars.EXTIFlag |= EXTI4_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI4产生中断\r\n");
    }
    #endif  
    #endif    
}

void EXTI5_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI5_EN > 0)
    UserVars.EXTIFlag |= EXTI5_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI5产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI6_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI6_EN > 0)
    UserVars.EXTIFlag |= EXTI6_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI6产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI7_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI7_EN > 0)
    UserVars.EXTIFlag |= EXTI7_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI7产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI8_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI8_EN > 0)
    UserVars.EXTIFlag |= EXTI8_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI8产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI9_ISRHook(void)
{
    // 以下编写自己的中断处理程序
    #if (EXTI9_EN > 0)
    UserVars.EXTIFlag |= EXTI9_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI9产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI10_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI10_EN > 0)
    UserVars.EXTIFlag |= EXTI10_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI10产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI11_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI11_EN > 0)
    UserVars.EXTIFlag |= EXTI112_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI11产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI12_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI12_EN > 0)
    UserVars.EXTIFlag |= EXTI12_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFOFLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI12产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI13_ISRHook(void)
{
	// 以下编写自己的中断处理程序
    #if (EXTI13_EN > 0)
    UserVars.EXTIFlag |= EXTI13_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI13产生中断\r\n");
    }
    #endif  
    #endif
}

void EXTI14_ISRHook(void)
{
 	// 以下编写自己的中断处理程序
    #if (EXTI14_EN > 0)
    UserVars.EXTIFlag |= EXTI14_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI14产生中断\r\n");
    }
    #endif  
    #endif   
}

void EXTI15_ISRHook(void)
{ 
	// 以下编写自己的中断处理程序
    #if (EXTI15_EN > 0)
    UserVars.EXTIFlag |= EXTI15_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI15产生中断\r\n");
    }
    #endif  
    #endif
}

/***********************************************************************************
* Function: ADC_ISRHook;
*
* Description: ADC中断处理完成回调函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void  ADC_ISRHook(ADC_VAR *pData)
{
#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxADC, pData);
#else
	INT8U i;
	
	if ((UserVars.ADC.Flag&ADC_READ_FLAG)==0) // 数据已经被读取
	{
        #if (AI1_EN == 1)   // 判断AI1使能
        UserVars.ADC.buf[AI1_ID] = pData->pBuf[AI1_ID]; // 读取AI1采样值
        #endif
        #if (AI2_EN == 1)   // 判断AI2使能
        UserVars.ADC.buf[AI2_ID] = pData->pBuf[AI2_ID]; // 读取AI2采样值
        #endif
        #if (AI3_EN == 1)   // 判断AI3使能
        UserVars.ADC.buf[AI3_ID] = pData->pBuf[AI3_ID]; // 读取AI3采样值
        #endif
        #if (AI4_EN == 1)   // 判断AI4使能
        UserVars.ADC.buf[AI4_ID] = pData->pBuf[AI4_ID]; // 读取AI4采样值
        #endif
        #if (AI5_EN == 1)   // 判断AI5使能
        UserVars.ADC.buf[AI5_ID] = pData->pBuf[AI5_ID]; // 读取AI5采样值
        #endif
        #if (AI6_EN == 1)   // 判断AI6使能
        UserVars.ADC.buf[AI6_ID] = pData->pBuf[AI6_ID]; // 读取AI6采样值
        #endif
        #if (AI7_EN == 1)   // 判断AI7使能
        UserVars.ADC.buf[AI7_ID] = pData->pBuf[AI7_ID]; // 读取AI7采样值
        #endif
        #if (AI8_EN == 1)   // 判断AI8使能
        UserVars.ADC.buf[AI8_ID] = pData->pBuf[AI8_ID]; // 读取AI8采样值
        #endif
        #if (AI9_EN == 1)   // 判断AI9使能
        UserVars.ADC.buf[AI9_ID] = pData->pBuf[AI9_ID]; // 读取AI9采样值
        #endif
        #if (AI10_EN == 1)  // 判断AI10使能
        UserVars.ADC.buf[AI10_ID] = pData->pBuf[AI10_ID]; // 读取AI10采样值
        #endif
        
		UserVars.ADC.len = pData->len;
		UserVars.ADC.Flag |= ADC_READ_FLAG;  // 设置数据可以读取标志;
	}
#endif
}

/***********************************************************************************
* Function: SysTickHandler_ISR,PendSVHandler_ISR,NMIHandler_ISR,FaultHandler_ISR;
*           MemFaultHandler_ISR,BusFaultHandler_ISR,UsageFaultHandler_ISR,SpuriousHandler_ISR
*
* Description: 系统异常中断处理函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void  SysTickHandler_ISR(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
    {
	    OS_CPU_SysTickHandler();
    }
#else

#endif
}

void  PendSVHandler_ISR(void)
{
#if	(UCOS_II_EN == 1)
	  OS_CPU_PendSVHandler();
#else

#endif
}
void NMIHandler_ISR(void)
{
	while(1);
}         

void FaultHandler_ISR(void)
{
	while(1);
}         

void MemFaultHandler_ISR(void)
{
	while(1);
}         
void BusFaultHandler_ISR(void)
{
	while(1);
}         
void UsageFaultHandler_ISR(void)
{
	while(1);
}         
void SpuriousHandler_ISR(void)
{
	while(1);
}         

/************************************************************************************ Function: CAN1TX_ISRHook;
*
* Description: 本函数是CAN1发送邮箱中断钩子函数;
*           
* Input:  val, 发送缓存中还有多少条数据未发送;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN1TX_ISRHook(INT32U val)
{
    #if (DEBUG_ISRHOOK_EN > 0)
	//if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN1TX DataNum, %02X\r\n", val);
    //}
    #endif   	
}
/***********************************************************************************
* Function: CAN1RX0_ISRHook;
*
* Description: 本函数是CAN1 RX0接收中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN1RX0_ISRHook(INT32U val)
{
    #if (DEBUG_ISRHOOK_EN > 0)	
    //if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN1RX0 DataNum, %02X\r\n", val);
    //}
    #endif   	
}

/***********************************************************************************
* Function: CAN1RX1_ISRHook;
*
* Description: 本函数是CAN1 RX1接收中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN1RX1_ISRHook(INT32U val)
{
    #if (DEBUG_ISRHOOK_EN > 0)
	//if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN1RX1 DataNum, %02X\r\n", val);
    //}    
    #endif	
}

/***********************************************************************************
* Function: CAN1SCE_ISRHook;
*
* Description: 本函数是CAN1错误和状态变化中断钩子函数;
*           
* Input:  val, 出错代码;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN1SCE_ISRHook(INT32U val)
{		
    #if (DEBUG_ISRHOOK_EN > 0)
    //if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN1 error code = %02X\r\n", val);
    //}
    #endif
	 
	 /*
	 if (CAN1->MSR&CAN_MSR_WKUI) // 唤醒中断
	 {
		  CAN1->MSR |= CAN_MSR_WKUI;
	 }
  	 if (CAN1->MSR&CAN_MSR_SLAKI) // 睡眠确认中断
	 {
		  CAN1->MSR |= CAN_MSR_SLAKI;
	 }
  	 if (CAN1->MSR&CAN_MSR_ERRI) // 错误中断
	 {
		  CAN1->MSR |= CAN_MSR_ERRI;

		  if (CAN1->ESR&CAN_ESR_EWGF)  // 错误警告标志 (Error warning flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_EPVF)  // 错误被动标志 (Error passive flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_BOFF)  // 离线标志 (Bus-off flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_LEC)  // 上次错误代码 (Last error code)
		  {
			  
		  }
	 }
	 */
}

/***********************************************************************************
* Function: CAN2TX_ISRHook;
*
* Description: 本函数是CAN2发送邮箱中断钩子函数;
*           
* Input:  val, 发送缓存中还有多少条数据未发送;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN2TX_ISRHook(INT32U val)
{
    #if (DEBUG_ISRHOOK_EN > 0)
	//if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN2TX DataNum, %02X\r\n", val);
    //}
    #endif 
}

/***********************************************************************************
* Function: CAN2RX0_ISRHook;
*
* Description: 本函数是CAN2 RX0接收中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN2RX0_ISRHook(INT32U val)
{
	#if (DEBUG_ISRHOOK_EN > 0)
    //if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN2RX0 DataNum, %02X\r\n", val);
    //}
    #endif    	
}

/***********************************************************************************
* Function: CAN2RX1_ISRHook;
*
* Description: 本函数是CAN2 RX1接收中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN2RX1_ISRHook(INT32U val)
{
    #if (DEBUG_ISRHOOK_EN > 0)
	//if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN2RX1 DataNum, %02X\r\n", val);
    //} 
    #endif 
}

/***********************************************************************************
* Function: CAN2SCE_ISRHook;
*
* Description: 本函数是CAN2错误和状态变化中断钩子函数;
*           
* Input:  val, 出错代码;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void CAN2SCE_ISRHook(INT32U val)
{		
    #if (DEBUG_ISRHOOK_EN > 0)
    //if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    //{
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=CAN2 error code: %02X\r\n", val);
    //}
    #endif 
	 /*
	 if (CAN1->MSR&CAN_MSR_WKUI) // 唤醒中断
	 {
		  CAN1->MSR |= CAN_MSR_WKUI;
	 }
  	 if (CAN1->MSR&CAN_MSR_SLAKI) // 睡眠确认中断
	 {
		  CAN1->MSR |= CAN_MSR_SLAKI;
	 }
  	 if (CAN1->MSR&CAN_MSR_ERRI) // 错误中断
	 {
		  CAN1->MSR |= CAN_MSR_ERRI;

		  if (CAN1->ESR&CAN_ESR_EWGF)  // 错误警告标志 (Error warning flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_EPVF)  // 错误被动标志 (Error passive flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_BOFF)  // 离线标志 (Bus-off flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_LEC)  // 上次错误代码 (Last error code)
		  {
			  
		  }
	 }
	 */
}

/***********************************************************************************
* Function: USBD_ISRHook;
*
* Description: USB Device中断钩子函数;
*              
* Input:  flag, 中断标志;
*
* Output: none;
*
* Return: ERR_TRUE,成功; ERR_FALSE,失败;
*
* Note:   none;
************************************************************************************/
INT32S USBD_ISRHook(INT32U flag)		 // USB Device中断钩子函数
{
    INT32S rst;

    rst = ERR_TRUE;
    
    #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB设备模式使能及USB Mass Storage使能   
    if (flag == USBD_SPIFLASH_READY)   // 在USB Mass Storage模式下, 询问SPI Flash是否被占用
    {
        if (UserVars.LibSys.Flag&SPIFLASH_FATFS_FLAG)   //判断是否被FATFS占用 
        {
            rst = ERR_FALSE;                            // 返回失败
        }
        else
        {
            UserVars.LibSys.Flag |= SPIFLASH_USB_FLAG;  // 设置USB占用标志
        }
    }
    else if (flag == SD_FATFS_FLAG)   // 在USB Mass Storage模式下, 询问SD卡是否被占用
    {
        if (UserVars.LibSys.Flag&SD_FATFS_FLAG)   //判断是否被FATFS占用 
        {
            rst = ERR_FALSE;                      // 返回失败
        }
        else
        {
            UserVars.LibSys.Flag |= SD_USB_FLAG;  // 设置USB占用标志
        }
    } 
    else if (flag == NFLASH_FATFS_FLAG)   // 在USB Mass Storage模式下, 询问Nand Flash是否被占用
    {
        if (UserVars.LibSys.Flag&NFLASH_FATFS_FLAG)   //判断是否被FATFS占用 
        {
            rst = ERR_FALSE;                            // 返回失败
        }
        else
        {
            UserVars.LibSys.Flag |= NFLASH_USB_FLAG;  // 设置USB占用标志
        }
    }
    #endif
    
    if (flag == USBD_CONNECT_IT)     //  USB连接中断标志
    {
         UserVars.Flag |= USBD_CONNECT_FLAG;
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB CONNECT\r\n");
         }
         #endif 
    }
    else if (flag == USBD_DISCONNECT_IT)    // USB断开连接中断标志
    {
         UserVars.Flag &= ~USBD_CONNECT_FLAG;
         #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB设备模式使能及USB Mass Storage使能   
         UserVars.LibSys.Flag &= ~(NFLASH_USB_FLAG|SD_USB_FLAG|SPIFLASH_USB_FLAG); // 清除NFLASH/SD卡/SPIFLASH被USB占用标志
         #endif
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB DISCONNECT\r\n");
         }
         #endif     
    }
    
    
    else if (flag == USBD_RESET_IT)    //  USB复位中断标志
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB RESET\r\n");
         }
         #endif     
    }
    else if (flag == USBD_RESUME_IT)    // USB恢复重新开始中断标志
    {
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB RESUME\r\n");
         }
         #endif         
    }
    else if (flag == USBD_SUSPEND_IT)    // USB挂起中断标志
    {
         UserVars.Flag &= ~USBD_CONNECT_FLAG;
         #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB设备模式使能及USB Mass Storage使能   
         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             UserVars.LibSys.Flag &= ~(NFLASH_USB_FLAG|SD_USB_FLAG|SPIFLASH_USB_FLAG); // 清除NFLASH/SD卡/SPIFLASH被USB占用标志
         }
         #endif
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB SUSPEND\r\n");
         }
         #endif        
    } 
    
    /*
    else if (flag == USBD_SETUP_IT)    // USB设置中断标志
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USBD: SETUP\r\n");
         }
         #endif 
    }    
    else if (flag == USBD_DATAIN_IT)          // USB IN端点中断
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DATA IN\r\n");
         }
         #endif     
    }
    else if (flag == USBD_DATAOUT_IT)    // USB OUT端点中断
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DATA OUT\r\n");
         }
         #endif   
    }*/
    /*
    else if (flag == USBD_SOF_IT)    // USB SOF中断标志
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=SOF\r\n");
         }
         #endif 
    }
    else if (flag == USBD_ISOIN_IT)    // USB ISOIN中断标志
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=ISOIN\r\n");
         }
         #endif 
    }
    else if (flag == USBD_ISOOUT_IT)    // USB ISOOUT中断标志
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=ISOOUT\r\n");
         }   
         #endif 
    } */
    
    return rst;
}

/***********************************************************************************
* Function: USBH_ISRHook;
*
* Description: USB Host中断钩子函数;
*              
* Input:  flag, 中断标志;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void USBH_ISRHook(INT32U flag)		 // USB Host中断钩子函数
{    
    if (flag == USBH_CONNECT_IT)    //  USB连接中断标志
    {
         UserVars.Flag |= USBH_CONNECT_FLAG;
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB CONNECT\r\n");
         }
         #endif
    }
    else if (flag == USBH_DISCONNECT_IT)    // USB断开连接中断标志
    {
         UserVars.Flag &= ~USBH_CONNECT_FLAG;
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB DISCONNECT\r\n");
         }
         #endif
    }
    /*
    else if (flag == USBH_SOF_IT)    // USB SOF中断标志
    {
         printf("AT+INFO=SOF\r\n");
    }*/
}




//void Error_Hook(INT8U err, INT8U *p)
//{
//    printf("ERROR:%d, %s\r\n", err, p);
//}

/***********************************************************************************
* Function: OSIntEnterHook;
*
* Description: 供库函数调用的进入操作系统中断调用函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void OSIntEnterHook(void)
{
#if	(UCOS_II_EN == 1)
	#if OS_CRITICAL_METHOD == 3                               /* Allocate storage for CPU status register  */
    static OS_CPU_SR  cpu_sr = 0;
	#endif
	

    if (UserVars.Flag&OS_START_FLAG)
	{
		#if (MODULE_CLASS == STM32F407XX)
        CPU_CRITICAL_ENTER();//cpu_sr = CPU_SR_Save();
		OSIntEnter();	
		CPU_CRITICAL_EXIT();//CPU_SR_Restore(cpu_sr);
        #else
        CPU_CRITICAL_ENTER()//cpu_sr = CPU_SR_Save();
		OSIntEnter();	
		CPU_CRITICAL_EXIT()//CPU_SR_Restore(cpu_sr);       
        #endif
	}
#endif
}

/***********************************************************************************
* Function: OSIntExitHook;
*
* Description: 供库函数调用的退出操作系统中兜饔孟函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void OSIntExitHook(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
	{
    	OSIntExit();
	}
#endif
}	 

/***********************************************************************************
* Function: OSAllInt_Ctrl;
*
* Description: 中断打开关闭控制函数;
*              
* Input:  flag: 1, 打开中断; 0, 打开中断;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void OSAllInt_Ctrl(INT8U flag)
{
#if	(UCOS_II_EN == 1)	
	#if OS_CRITICAL_METHOD == 3                               /* Allocate storage for CPU status register  */
    static OS_CPU_SR  cpu_sr = 0;
	#endif
    
    if (UserVars.Flag&OS_START_FLAG)
    {	
        if (flag>0)  // 打开中断
        {
            #if (MODULE_CLASS == STM32F407XX)
            CPU_CRITICAL_EXIT();//CPU_SR_Restore(cpu_sr);
            #else
            CPU_CRITICAL_EXIT()//CPU_SR_Restore(cpu_sr);
            #endif
        }
        else		// 关闭中断
        {
            #if (MODULE_CLASS == STM32F407XX)
            CPU_CRITICAL_ENTER();//cpu_sr = CPU_SR_Save();
            #else
            CPU_CRITICAL_ENTER()//cpu_sr = CPU_SR_Save();
            #endif
        }
    }
#endif
}
/***********************************************************************************
* Function: OSDelay_ms;
*
* Description: 延时程序, 延时时间范围: 0~65535ms;
*              
* Input:  val, 延时时间变量, 单位：ms;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void OSDelay_ms(INT16U val)
{
    INT16U i;
    
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
    {    
        OSTimeDly(val/10);
    }
    else
    {
        for(i=0; i<val; i++)
        {
             Delay_us(1000);
        }
    }
#else
    for(i=0; i<val; i++)
    {
        Delay_us(1000);
    }    
#endif
}

/***********************************************************************************
* Function: SPI_RequestOSSem;
*
* Description: 向操作系统申请SPI访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
INT32S SPI_RequestOSSem(INT16U timeout)
{
#if	(UCOS_II_EN == 1)
	INT32S ret;
	INT8U err;
	if (UserVars.Flag&OS_START_FLAG)
	{
	    OSMboxPend(OSMboxSPI, (timeout+9)/10, &err);	  
		if (err== OS_ERR_NONE)   
		{					    	    
			ret = ERR_TRUE;
	    }
		else if (err == OS_ERR_TIMEOUT)
		{
			ret = ERR_TIMEOUT;
		}
		else
		{
			ret = ERR_FALSE;
		}
	}
	else
	{
		ret = ERR_TRUE;
	}
	return ret;
#else
    return ERR_TRUE;
#endif
}

/***********************************************************************************
* Function: SPI_ReleaseOSSem;
*
* Description: 向操作系释放SPI访问权限;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
INT32S SPI_ReleaseOSSem(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
	{
		OSMboxPost(OSMboxSPI, (void *)1); // 释放访问权限
	}
#endif
	return ERR_TRUE;
}


#if (MODULE_TYPE == STM32F103ZE)
/***********************************************************************************
* Function: FSMC_ISRHook;
*
* Description: 本函数FSMC中断处理函数;
*           
* Input:  inr：中断来源, 2：BANK2中断; 3：BANK3中断; 4：BANK4中断;;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void FSMC_ISRHook(INT16U flag)
{
    INT8U err;    
    
    UserVars.FSMC_ITFlag |= flag;
#if (UCOS_II_EN == 1)   	
    if (UserVars.Flag&OS_START_FLAG)
    {
        if (flag&FSMC_BANK2IT_FLAG) // FSMC BANK2中断
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK2, OS_FLAG_SET, (INT8U *)&err);
        }
        /*
        else if (flag&FSMC_BANK3IT_FLAG) // FSMC BANK3中断
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK3, OS_FLAG_SET, (INT8U *)&err);
        }
        else if (flag&FSMC_BANK4IT_FLAG) // FSMC BANK4中断
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK4, OS_FLAG_SET, (INT8U *)&err);
        }*/
    }
#endif
}
/***********************************************************************************
* Function: FSMC_ISRRead;
*
* Description: 读取FSMC的Bank2, Bank3, Bank4状态输入引脚;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE: 成功;  ERR_FALSE: 失败;
*
* Note:   none;
************************************************************************************/
INT32S FSMC_ISRRead(INT16U flag)
{
    INT8U err;
    INT16U t;

#if (UCOS_II_EN == 1) 
    if (UserVars.Flag&OS_START_FLAG)
    {
        if (flag&FSMC_BANK2IT_FLAG) // FSMC BANK2中断
        {
            OSFlagPend (OSFlagSys, OSFLAG_FSMC_BANK2, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 100, (INT8U *)&err);
        }
        /*
        else if (flag&FSMC_BANK3IT_FLAG) // FSMC BANK3中断
        {
             OSFlagPend (OSFlagSys, OSFLAG_FSMC_BANK3, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 100, (INT8U *)&err);
        }
        else if (flag&FSMC_BANK4IT_FLAG) // FSMC BANK4中断
        {
              OSFlagPend (OSFlagSys, OSFLAG_FSMC_BANK4, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 100, (INT8U *)&err);
        }*/  
        if (err == OS_ERR_NONE)
        {
            return ERR_TRUE;
        }
        else
        {
            return ERR_FALSE;
        }
    }
#endif
     t = 0;
     while ((UserVars.FSMC_ITFlag&FSMC_BANK2IT_FLAG)==0)
     {
        Delay_us(10);
        t++;
        if (t==2000) // 等待20ms
        {
            return ERR_FALSE;
        }
     }
     UserVars.FSMC_ITFlag &= ~flag;
     return ERR_TRUE;
}

/***********************************************************************************
* Function: NET_CreateOSSem;
*
* Description: 向操作系统申请NET访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
void NET_CreateOSSem(void)
{
#if	(UCOS_II_EN == 1)
    OSMboxNET  = OSMboxCreate((void*)1);  //  NET访问权限保护
#endif
}
/***********************************************************************************
* Function: NET_RequestOSSem;
*
* Description: 向操作系统申请NET访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_RequestOSSem(INT16U timeout)
{
#if	(UCOS_II_EN == 1)
	INT32S ret;
	INT8U err;

    OSMboxPend(OSMboxNET, (timeout+9)/10, &err);	  
	if (err== OS_ERR_NONE)   
	{					    	    
		ret = ERR_TRUE;
    }
	else if (err == OS_ERR_TIMEOUT)
	{
		ret = ERR_TIMEOUT;
	}
	else
	{
		ret = ERR_FALSE;
	}
	
	return ret;
#else
    return ERR_TRUE;
#endif
}
/***********************************************************************************
* Function: NET_ReleaseOSSem;
*
* Description: 向操作系释放NET访问权限;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_ReleaseOSSem(void)
{
#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxNET, (void *)1); // 释放访问权限
#endif
	return ERR_TRUE;
}

/***********************************************************************************
* Function: NET_PendRXIntOSFlag;
*
* Description: 向操作系统接收网络接收中断标志;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
void NETInt_CreateOSSem(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
	{
		OSMboxNETInt  = OSMboxCreate((void*)0);  //  NET访问权限保护
	}
	else
	{
		#if (DEBUG_ISRHOOK_EN > 0)
	    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=NETInt_CreateOSSem: error!\r\n");
        }
        #endif
	}
#endif
}


INT32S NET_PendRXIntOSFlag(INT16U timeout)
{
#if	(UCOS_II_EN == 1)
	INT32S ret;
	INT8U err;

	//OSFlagPend (OSFlagSys, OSFLAG_NET_RXINT, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, (timeout+9)/10, (INT8U *)&err);
	if (UserVars.Flag&OS_START_FLAG)
	{
		OSMboxPend(OSMboxNETInt, (timeout+9)/10, &err);
		if (err== OS_ERR_NONE)   
		{					    	    
			ret = ERR_TRUE;
	    }
		else if (err == OS_ERR_TIMEOUT)
		{
			ret = ERR_TIMEOUT;
		}
		else
		{
			ret = ERR_FALSE;
		}
	}
	else
	{
		#if (DEBUG_ISRHOOK_EN > 0)
	    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
           DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=NET PendRXIntOSFlag: error!\r\n");
        }
        #endif
        ret = ERR_FALSE;
	}
	 
	return ret;
#else
    return ERR_TRUE;
#endif	
}
/***********************************************************************************
* Function: INT32S NET_PostRXIntOSFlag;
*
* Description: 向操作系统发送网络接收中断标志;;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
INT32S  NET_PostRXIntOSFlag(void)
{
#if (UCOS_II_EN == 1)
	INT8U err;	
    if (UserVars.Flag&OS_START_FLAG)
	{
    	OSMboxPost(OSMboxNETInt, (void *)1); // 释放访问权限
	}
    else
	{
        #if (DEBUG_ISRHOOK_EN > 0)
	    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=NET PostRXIntOSFlag: error!\r\n");
        }
        #endif
    }
    
#else

#endif	 
	return ERR_TRUE;
}
#endif

/***********************************************************************************
* Function: OSMalloc;
*
* Description: 动态内存申请函数;
*              
* Input:  len, 申请内存长度, 单位: 字节;
*
* Output: none;
*
* Return: 内存起始地址指针;
*
* Note:   此函数必须要定义OSMboxMalloc邮箱, 并初始化为1; 如果返回内存地址为0, 则申请失败;
************************************************************************************/
void *OSMalloc(INT16U len)
{
	INT8U *pMEM;
#if	(UCOS_II_EN == 1)
	INT8U  err;
	
	OSMboxPend(OSMboxMalloc, 0, &err);	 // 获取访问权限	 
	if(err != OS_ERR_NONE)
	{
		return 0;
	}	
#endif

	pMEM = (INT8U *)malloc(len);

#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxMalloc, (void *)1); // 释放访问权限
#endif
	
	return pMEM;
}

/***********************************************************************************
* Function: OSFree;
*
* Description: 动态内存释放函数;
*              
* Input:  *p, 释放内存起始地址指针
*
* Output: none;
*
* Return: ERR_TRUE:释放成功;  ERR_FALSE:释放失败;
*
* Note:   此函数必须要定义OSMboxFree邮箱, 并初始化为1;
************************************************************************************/
INT32S OSFree(void *p)
{
#if	(UCOS_II_EN == 1)
	INT8U err;

	OSMboxPend(OSMboxFree, 0, &err);	 // 获取访问权限	 
	if(err != OS_ERR_NONE)
	{
	    return ERR_FALSE;
	}  
#endif	
	free(p); 
#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxFree, (void *)1); // 释放访问权限
#endif
	return ERR_TRUE;
}

/***********************************************************************************
* Function: PWM_ISRHook;
*
* Description: PWM输出完成或出错中断的钩子函数;
*           
* Input:  id: PWM索引ID, PWM1_ID~PWM8_ID 
*         flag: 中断标志
*         PWMCH1_OK_FLAG: PWM CH1发送脉冲完成标志;
*         PWMCH2_OK_FLAG: PWM CH2发送脉冲完成标志;
*         PWMCH3_OK_FLAG: PWM CH3发送脉冲完成标志;
*         PWMCH4_OK_FLAG: PWM CH4发送脉冲完成标志;
*         PWMCH1_ERR_FLAG: PWM CH1发送脉冲失败标志;
*         PWMCH2_ERR_FLAG: PWM CH2发送脉冲失败标志;
*         PWMCH3_ERR_FLAG: PWM CH3发送脉冲失败标志;
*         PWMCH4_ERR_FLAG: PWM CH4发送脉冲失败标志;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void PWM_ISRHook(INT8U id, INT32U flag)
{
    UserVars.PWM_ITFlag[id] = flag;
    #if (DEBUG_ISRHOOK_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        //DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=PWM%d ITFlag,%02X\r\n", id+1, flag);
    }
    #endif    
}
/***********************************************************************************
* Function: DMA1_ISRHook, DMA2_ISRHook;
*
* Description: 以下函数是DMA1,DMA2中断的钩子函数;
*           
* Input:  ch: 通道1(DMA_CH1)~8(DMA_CH8)
*         flag: 中断类别: DMA_IT_TC, 传输完成中断标志
*                         DMA_IT_HT, 半传输完成中断标志
*                         DMA_IT_TERR, 传输出错中断标志
*                         DMA_IT_FIFOERR, 数据流FIFO错误标志   
*                         DMA_IT_DERR, 数据流直接错误标志
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void DMA1_ISRHook(INT8U ch, INT32U flag)
{
    #if (DEBUG_ISRHOOK_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DMA1CH%d, ITFlag=%02X\r\n", ch, flag);
    }
    #endif
    
    // 以下编写自己的中断处理程序
    if(flag&DMA_IT_TC) // 传输完成中断
    {
        
    }
    if(flag&DMA_IT_HT) // 半传输完成中断
    {
        
    }
    if(flag&DMA_IT_TERR) // 传输出错中断
    {
        
    }
    #if (MODULE_CLASS == STM32F407XX)    
    if(flag&DMA_IT_FIFOERR) // 数据流FIFO错误标志 
    {
        
    }    
    if(flag&DMA_IT_DERR)   // 数据流直接错误标志
    {
        
    }
    #endif    
}
void DMA2_ISRHook(INT8U ch, INT32U flag)
{
    #if (DEBUG_ISRHOOK_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DMA2CH%d, ITFlag=%02X\r\n", ch, flag);
    }
    #endif
    
    // 以下编写自己的中断处理程序
    if(flag&DMA_IT_TC) // 传输完成中断
    {
        
    }
    if(flag&DMA_IT_HT) // 半传输完成中断
    {
        
    }
    if(flag&DMA_IT_TERR) // 传输出错中断
    {
        
    }
    #if (MODULE_CLASS == STM32F407XX)    
    if(flag&DMA_IT_FIFOERR) // 数据流FIFO错误标志 
    {
        
    }    
    if(flag&DMA_IT_DERR)   // 数据流直接错误标志
    {
        
    }
    #endif    
}

/***********************************************************************************
* Function: API_OSFlagPostHook;
*
* Description: 驱动库设置等待标志函数;
*              
* Input:  flag: 等待标志, 在const.h中定义
*
* Output: none;
*
* Return: none;
*
* Note:   这个函数只提供给驱动库中断调用, 请用户不要修改该函数;
************************************************************************************/
void API_OSFlagPostHook(INT32U flag)
{    
#if (UCOS_II_EN == 1)   	
    INT8U err;  

    if (UserVars.Flag&OS_START_FLAG)
    {
         OSFlagPost(APIWaitOSFlag, flag, OS_FLAG_SET, (INT8U *)&err);
    }
#else
    UserVars.LibSys.APIWaitFlag |= flag;
#endif
}
/***********************************************************************************
* Function: API_OSFlagPendHook;
*
* Description: 驱动库读取等待标志函数;
*              
* Input:  flag: 等待标志, 在const.h中定义
*         TimeOut: 超时时间, 单位ms, 如果为0则设置为0xFFFFFFFF, 就是无线等待
*
* Output: none;
*
* Return: ERR_TRUE: 成功;  ERR_FALSE: 失败; ERR_TIMEOUT: 超时失败;
*
* Note:   这个函数只提供给驱动库调用, 请用户不要修改该函数;
************************************************************************************/
INT32S API_OSFlagPendHook(INT32U flag, INT32U TimeOut)
{
#if (UCOS_II_EN == 1) 
    INT8U err;

    if (UserVars.Flag&OS_START_FLAG)
    {
        OSFlagPend (APIWaitOSFlag, flag, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, TimeOut/10, (INT8U *)&err);
        if (err == OS_ERR_NONE)
        {
            return ERR_TRUE;
        }
        if (err == OS_ERR_TIMEOUT)
        {
            return ERR_TIMEOUT;
        }
        else
        {
            return ERR_FALSE;
        }
    }
#else
    if (TimeOut==0)
    {
        TimeOut = 0xFFFFFFFF;
    }        
    while(((UserVars.LibSys.APIWaitFlag&flag)==0)||(TimeOut>0))
    {
        Delay_ms(1);
    }        
    if (UserVars.LibSys.APIWaitFlag&flag)
    {
        UserVars.LibSys.APIWaitFlag &= ~flag;  // 清除标志
        return ERR_TRUE;
    }
    else
    {
        return ERR_TIMEOUT;
    }        
#endif
}



/***********************************************************************************/
// 文件结束
/***********************************************************************************/




