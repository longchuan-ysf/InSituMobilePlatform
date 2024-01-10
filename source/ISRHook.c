/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: ISRHook.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2020.2.12			
* Email:   EmbedARM@126.com
* Modify:  1. ɾ��ԭ������DMA/SPI/I2C�жϹ��Ӻ���;
*          2. ɾ������SPI�жϹ��Ӻ���; 
*          2. ɾ������I2C�жϹ��Ӻ���; 
*
* Description: ���ļ���������ϵͳ�жϴ�����;
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
// �����ⲿͷ�ļ�
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
// ������ȫ�ֱ�������
*************************************************************************************/

/***********************************************************************************
* Function: Uart1_ISRHook,Uart2_ISRHook,Uart3_ISRHook,Uart4_ISRHook,Uart5_ISRHook,Uart6_ISRHook;
*
* Description: ���º�����Uart1,Uart2,Uart3,Uart4,Uart5�жϼ��������ݵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ������ֻ�ܸ��ݴ���״̬UartSR��д�������ݳ���, �����������ڲ��ж�ʵ��;
************************************************************************************/
#define USART_FLAG_RXNE ((INT16U)0x0020)
void Uart1_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
		printf("uart1 rx 0x%x\r\n",Data);
	}	
}

void Uart2_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
	}
}

void Uart3_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
	}
}

void Uart4_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
	}
}

void Uart5_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
		printf("uart5 rx 0x%x\r\n",Data);
	}
}

#if (MODULE_CLASS == STM32F407XX)
void Uart6_ISRHook(INT16U UartSR, INT16U Data)
{
    // ���±�д�Լ����жϴ������
    if(UartSR&USART_FLAG_RXNE) // ���յ�����
	{				
		UserVars.UartData = Data;  // ��ȡ���յ�������
	}
}
#endif

/***********************************************************************************
* Function: SPI1_ISRHook,SPI2_ISRHook,SPI2_ISRHook;
*
* Description: ���º�����SPI1,SPI2,SPI3���Ӻ���;
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
    // ���±�д�Լ����жϴ������
}

void SPI2_ISRHook(INT32U flag)
{
    // ���±�д�Լ����жϴ������
}

void SPI3_ISRHook(INT32U flag)
{
    // ���±�д�Լ����жϴ������
}

/************************************************************************************
//
//                 �жϵĹ��Ӻ���
//
*************************************************************************************/

/***********************************************************************************
* Function: RTC_ISRHook;
*
* Description: ���º�����RTC�жϵĹ��Ӻ���;
*           
* Input:  flag, �жϱ�־; cnt, RTC 32λ������ֵ
*
* Output: none;
*          		
* Return: none;
*
* Note:   ���ж�ֻ����STM32F10Xģ���ϴ���;
************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
void RTC_ISRHook(INT8U flag, INT32U cnt)
{

    // ���±�д�Լ����жϴ������
    #if (RTC_SECIT_EN > 0)  // RTC���ж�
	if (flag&RTC_IT_SEC)    // ���ж�
    {
        UserVars.Flag |= RTC_SECIT_FLAG; // ����RTC���жϱ�־
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC�������ж�\r\n");
        }
        #endif        
    }
    #endif
    
    #if (RTC_ALRIT_EN > 0)  // RTC�����ж�
    if (flag&RTC_IT_ALARM)  // �����ж�
    {
        UserVars.Flag |= RTC_ALRIT_FLAG; // ����RTC�����жϱ�־
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC�������ӱ����ж�\r\n");
        }
        #endif        
        
    }
    #endif
    
    /* �����������������ж�
    if (flag&RTC_IT_OW)     // ���������
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=RTC��������������ж�:%d\r\n", cnt);
        }
        #endif 
    } 
    */   

    
//// Modify 2019.12.1 ����
//#if (MODULE_CLASS == STM32F407XX)
//    #if (RTC_ALRIT_EN > 0)  // RTC�����ж�ʹ��
//    if (flag&RTC_IT_WKUPIT) // RTC�����ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC�����ж�\r\n");
//        }   
//        #endif
//    }
//    #endif

//    #if ( RTC_ALRAIT_EN > 0)  // RTC����A�ж�ʹ��
//    if (flag&RTC_IT_ALRA)     // RTC����A�ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC����A�ж�\r\n");
//        }   
//        #endif
//    }
//    #endif
//    
//    #if ( RTC_ALRBIT_EN > 0)  // RTC����B�ж�ʹ��
//    if (flag&RTC_IT_ALRB)     // RTC����B�ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC����B�ж�\r\n");
//        }   
//        #endif
//    } 
//    #endif
//    
//    #if (RTC_TSFIT_EN  > 0)  // RTCʱ����ж�ʹ��
//    if (flag&RTC_IT_TSF)     // RTCʱ����ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC����B�ж�\r\n");
//        }   
//        #endif
//    }  
//    #endif

//    #if (RTC_TAMP1IT_EN  > 0)  // RTC���ּ��1�ж�ʹ��
//    if (flag&RTC_IT_TAMP1)     // RTC���ּ��1�ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC���ּ��1�ж�\r\n");
//        }   
//        #endif
//    }   
//    #endif    
//    #if (RTC_TAMP2IT_EN  > 0)  // RTC���ּ��2�ж�ʹ��
//    if (flag&RTC_IT_TAMP1)     // RTC���ּ��2�ж�
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=RTC���ּ��2�ж�\r\n");
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
* Description: ��������TIM1��TIM8�жϹ��Ӻ���;
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM1����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1��ʱ���ж�\r\n");
        }
        #endif
    }
}

void TIM1_TRG_COM_ISRHook(INT32U flag)  // TIM1 Trig & Commutation Interrupts
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM1_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_CH1IT_FLAG)  // TIM1 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM1 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM1 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM1 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM1CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }
}

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
void TIM8_BRK_ISRHook(INT32U flag)	 // TIM8 Break  Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM8����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8��ʱ���ж�\r\n");
        }
        #endif 
    }
}

void TIM8_TRG_COM_ISRHook(INT32U flag) // TIM8 Trig & Commutation Interrupts
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM8_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
        
    if (flag&TIM_CH1IT_FLAG)  // TIM8 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM8 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM8 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM8 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM8CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }
}
#endif
/***********************************************************************************
* Function: TIM2_ISRHook, TIM3_ISRHook, TIM4_ISRHook, 
*			TIM5_ISRHook, TIM6_ISRHook, TIM7_ISRHook
*
* Description: ��������TIM2~TIM7�жϹ��Ӻ���;
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM2_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM2����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2��ʱ���ж�\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM2 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM2 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM2 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM2 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM2CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }   
}

void TIM3_ISRHook(INT32U flag)		 // TIM3 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM3_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM3����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3��ʱ���ж�\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM3 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM3 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM3 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM3 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM3CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }   
}

void TIM4_ISRHook(INT32U flag)		 // TIM4 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM4_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM4����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4��ʱ���ж�\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM4 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM4 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM4 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM4 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM4CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }     
}

void TIM5_ISRHook(INT32U flag)		 // TIM5 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM5_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM5����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5��ʱ���ж�\r\n");
        }
        #endif        
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM5 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM5 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif 
    }  
    if (flag&TIM_CH3IT_FLAG)  // TIM5 CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH3�Ӷ�ʱ��3�ж�\r\n");
        }
        #endif 
    }   
    if (flag&TIM_CH4IT_FLAG)  // TIM5 CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM5CH4�Ӷ�ʱ��4�ж�\r\n");
        }
        #endif 
    }   
}

void TIM6_ISRHook(INT32U flag)		 // TIM6 Global Interrupt
{
	TIM_CTRL TIMCtrl;
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM6_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM7_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    #if (DEBUG_ISRHOOK_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM7��ʱ���ж�\r\n");
    }
    #endif
}

/***********************************************************************************
* Function: TIM9_ISRHook, TIM10_ISRHook, TIM11_ISRHook, 
*			TIM12_ISRHook, TIM13_ISRHook, TIM14_ISRHook
*
* Description: ��������TIM9~TIM14�жϹ��Ӻ���;
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
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM9_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM9����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9��ʱ���ж�\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM12 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM12 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {        
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM9CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif
    }                   
}

void TIM10_ISRHook(INT32U flag)		 // TIM10 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM10_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM10����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM10��ʱ���ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM10CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
}

void TIM11_ISRHook(INT32U flag)		 // TIM11 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM11_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM11����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM11��ʱ���ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM11CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
}

void TIM12_ISRHook(INT32U flag)		 // TIM12 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM12_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM12����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12��ʱ���ж�\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM12 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif
    }
    if (flag&TIM_CH2IT_FLAG)  // TIM12 CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {        
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM12CH2�Ӷ�ʱ��2�ж�\r\n");
        }
        #endif
    }          
}

void TIM13_ISRHook(INT32U flag)		 // TIM13 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM13_ID] |= flag;    // ���жϱ�־����ȫ�ֱ���
    
    if (flag&TIM_IT_FLAG)     // TIM13����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM13��ʱ���ж�\r\n");
        }
        #endif
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM13 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM13CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif        
    }
}

void TIM14_ISRHook(INT32U flag)		 // TIM14 Global Interrupt
{
    // ���±�д�Լ����жϴ������
    UserVars.TIMx_ITFlag[TIM14_ID] |= flag;     // ���жϱ�־����ȫ�ֱ���    
    if (flag&TIM_IT_FLAG)     // TIM14����ʱ���жϱ�־(�����ж�) 
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM14��ʱ���ж�\r\n");
        }
        #endif 
    }
    if (flag&TIM_CH1IT_FLAG)  // TIM14 CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
    {
        #if (DEBUG_ISRHOOK_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=TIM14CH1�Ӷ�ʱ��1�ж�\r\n");
        }
        #endif 
    }
}
#endif


/***********************************************************************************
* Function: EXTI16_PVD_ISRHook, EXTI17_RTCAlarm_ISRHook, EXTI8_USBWakeUp_ISRHook,
*           EXTI19_NETWakeUp_ISRHook;
*
* Description: ���º�����EXTI16~EXTI19�жϵĹ��Ӻ���;
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
    // ���±�д�Լ����жϴ������
    #if (EXTI16_PVD_EN > 0)
    UserVars.EXTIFlag |= EXTI16_PVD_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI16 PVD�����ж�\r\n");
    }
    #endif  
    #endif     
}

// RTC�����ж�
void  EXTI17_RTCAlarm_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI17_RTCAlarm_EN > 0)
    UserVars.EXTIFlag |= EXTI17_RTCAlarm_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI17 RTCAlarm�����ж�\r\n");
    }
    #endif  
    #endif     
}

void  EXTI18_USBWakeUp_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI18_USBWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI18_USBWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI18 USBWakeUp�����ж�\r\n");
    }
    #endif  
    #endif      
}

void  EXTI19_NETWakeUp_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI19_NETWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI19_NETWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI19 NETWakeUp�����ж�\r\n");
    }
    #endif  
    #endif     
}

#if (MODULE_CLASS == STM32F407XX)
void  EXTI20_USBHSWakeUp_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI20_USBHSWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI21_USBHSWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI20 USBHSWakeUp�����ж�\r\n");
    }
    #endif  
    #endif      
}

// RTC���ֺ�ʱ����ж�
void  EXTI21_RTCTSE_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI21_RTCTSE_EN > 0)
    UserVars.EXTIFlag |= EXTI21_RTCTSE_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI21 RTCTSE�����ж�\r\n");
    }
    #endif  
    #endif    
}

// RTC�����ж�
void  EXTI22_RTCWakeUp_ISRHook(INT32U Flag)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI22_RTCWakeUp_EN > 0)
    UserVars.EXTIFlag |= EXTI22_RTCWakeUp_FLAG;
    #if (DEBUG_ISRHOOK_EN>0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI22 RTCWakeUp�����ж�\r\n");
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
* Description: ���º������ⲿIO 16���жϺ���;
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
    // ���±�д�Լ����жϴ������
    #if (EXTI0_EN > 0)
    UserVars.EXTIFlag |= EXTI0_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI0�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI1_ISRHook(void)
{  
	// ���±�д�Լ����жϴ������
    #if (EXTI1_EN > 0)
    UserVars.EXTIFlag |= EXTI1_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI1�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI2_ISRHook(void)
{ 
	// ���±�д�Լ����жϴ������
    #if (EXTI2_EN > 0)
    UserVars.EXTIFlag |= EXTI2_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI2�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI3_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI3_EN > 0)
    UserVars.EXTIFlag |= EXTI3_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI3�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI4_ISRHook(void)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI4_EN > 0)
    UserVars.EXTIFlag |= EXTI4_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI4�����ж�\r\n");
    }
    #endif  
    #endif    
}

void EXTI5_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI5_EN > 0)
    UserVars.EXTIFlag |= EXTI5_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI5�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI6_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI6_EN > 0)
    UserVars.EXTIFlag |= EXTI6_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI6�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI7_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI7_EN > 0)
    UserVars.EXTIFlag |= EXTI7_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI7�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI8_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI8_EN > 0)
    UserVars.EXTIFlag |= EXTI8_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI8�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI9_ISRHook(void)
{
    // ���±�д�Լ����жϴ������
    #if (EXTI9_EN > 0)
    UserVars.EXTIFlag |= EXTI9_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI9�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI10_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI10_EN > 0)
    UserVars.EXTIFlag |= EXTI10_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI10�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI11_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI11_EN > 0)
    UserVars.EXTIFlag |= EXTI112_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI11�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI12_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI12_EN > 0)
    UserVars.EXTIFlag |= EXTI12_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFOFLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI12�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI13_ISRHook(void)
{
	// ���±�д�Լ����жϴ������
    #if (EXTI13_EN > 0)
    UserVars.EXTIFlag |= EXTI13_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI13�����ж�\r\n");
    }
    #endif  
    #endif
}

void EXTI14_ISRHook(void)
{
 	// ���±�д�Լ����жϴ������
    #if (EXTI14_EN > 0)
    UserVars.EXTIFlag |= EXTI14_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI14�����ж�\r\n");
    }
    #endif  
    #endif   
}

void EXTI15_ISRHook(void)
{ 
	// ���±�д�Լ����жϴ������
    #if (EXTI15_EN > 0)
    UserVars.EXTIFlag |= EXTI15_ISR_FLAG;
    #if (DEBUG_ISRHOOK_EN > 0)
	if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=EXTI15�����ж�\r\n");
    }
    #endif  
    #endif
}

/***********************************************************************************
* Function: ADC_ISRHook;
*
* Description: ADC�жϴ�����ɻص�����;
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
	
	if ((UserVars.ADC.Flag&ADC_READ_FLAG)==0) // �����Ѿ�����ȡ
	{
        #if (AI1_EN == 1)   // �ж�AI1ʹ��
        UserVars.ADC.buf[AI1_ID] = pData->pBuf[AI1_ID]; // ��ȡAI1����ֵ
        #endif
        #if (AI2_EN == 1)   // �ж�AI2ʹ��
        UserVars.ADC.buf[AI2_ID] = pData->pBuf[AI2_ID]; // ��ȡAI2����ֵ
        #endif
        #if (AI3_EN == 1)   // �ж�AI3ʹ��
        UserVars.ADC.buf[AI3_ID] = pData->pBuf[AI3_ID]; // ��ȡAI3����ֵ
        #endif
        #if (AI4_EN == 1)   // �ж�AI4ʹ��
        UserVars.ADC.buf[AI4_ID] = pData->pBuf[AI4_ID]; // ��ȡAI4����ֵ
        #endif
        #if (AI5_EN == 1)   // �ж�AI5ʹ��
        UserVars.ADC.buf[AI5_ID] = pData->pBuf[AI5_ID]; // ��ȡAI5����ֵ
        #endif
        #if (AI6_EN == 1)   // �ж�AI6ʹ��
        UserVars.ADC.buf[AI6_ID] = pData->pBuf[AI6_ID]; // ��ȡAI6����ֵ
        #endif
        #if (AI7_EN == 1)   // �ж�AI7ʹ��
        UserVars.ADC.buf[AI7_ID] = pData->pBuf[AI7_ID]; // ��ȡAI7����ֵ
        #endif
        #if (AI8_EN == 1)   // �ж�AI8ʹ��
        UserVars.ADC.buf[AI8_ID] = pData->pBuf[AI8_ID]; // ��ȡAI8����ֵ
        #endif
        #if (AI9_EN == 1)   // �ж�AI9ʹ��
        UserVars.ADC.buf[AI9_ID] = pData->pBuf[AI9_ID]; // ��ȡAI9����ֵ
        #endif
        #if (AI10_EN == 1)  // �ж�AI10ʹ��
        UserVars.ADC.buf[AI10_ID] = pData->pBuf[AI10_ID]; // ��ȡAI10����ֵ
        #endif
        
		UserVars.ADC.len = pData->len;
		UserVars.ADC.Flag |= ADC_READ_FLAG;  // �������ݿ��Զ�ȡ��־;
	}
#endif
}

/***********************************************************************************
* Function: SysTickHandler_ISR,PendSVHandler_ISR,NMIHandler_ISR,FaultHandler_ISR;
*           MemFaultHandler_ISR,BusFaultHandler_ISR,UsageFaultHandler_ISR,SpuriousHandler_ISR
*
* Description: ϵͳ�쳣�жϴ�����;
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
* Description: ��������CAN1���������жϹ��Ӻ���;
*           
* Input:  val, ���ͻ����л��ж���������δ����;
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
* Description: ��������CAN1 RX0�����жϹ��Ӻ���;
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
* Description: ��������CAN1 RX1�����жϹ��Ӻ���;
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
* Description: ��������CAN1�����״̬�仯�жϹ��Ӻ���;
*           
* Input:  val, �������;
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
	 if (CAN1->MSR&CAN_MSR_WKUI) // �����ж�
	 {
		  CAN1->MSR |= CAN_MSR_WKUI;
	 }
  	 if (CAN1->MSR&CAN_MSR_SLAKI) // ˯��ȷ���ж�
	 {
		  CAN1->MSR |= CAN_MSR_SLAKI;
	 }
  	 if (CAN1->MSR&CAN_MSR_ERRI) // �����ж�
	 {
		  CAN1->MSR |= CAN_MSR_ERRI;

		  if (CAN1->ESR&CAN_ESR_EWGF)  // ���󾯸��־ (Error warning flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_EPVF)  // ���󱻶���־ (Error passive flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_BOFF)  // ���߱�־ (Bus-off flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_LEC)  // �ϴδ������ (Last error code)
		  {
			  
		  }
	 }
	 */
}

/***********************************************************************************
* Function: CAN2TX_ISRHook;
*
* Description: ��������CAN2���������жϹ��Ӻ���;
*           
* Input:  val, ���ͻ����л��ж���������δ����;
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
* Description: ��������CAN2 RX0�����жϹ��Ӻ���;
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
* Description: ��������CAN2 RX1�����жϹ��Ӻ���;
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
* Description: ��������CAN2�����״̬�仯�жϹ��Ӻ���;
*           
* Input:  val, �������;
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
	 if (CAN1->MSR&CAN_MSR_WKUI) // �����ж�
	 {
		  CAN1->MSR |= CAN_MSR_WKUI;
	 }
  	 if (CAN1->MSR&CAN_MSR_SLAKI) // ˯��ȷ���ж�
	 {
		  CAN1->MSR |= CAN_MSR_SLAKI;
	 }
  	 if (CAN1->MSR&CAN_MSR_ERRI) // �����ж�
	 {
		  CAN1->MSR |= CAN_MSR_ERRI;

		  if (CAN1->ESR&CAN_ESR_EWGF)  // ���󾯸��־ (Error warning flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_EPVF)  // ���󱻶���־ (Error passive flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_BOFF)  // ���߱�־ (Bus-off flag)
		  {
			  
		  }
		  if (CAN1->ESR&CAN_ESR_LEC)  // �ϴδ������ (Last error code)
		  {
			  
		  }
	 }
	 */
}

/***********************************************************************************
* Function: USBD_ISRHook;
*
* Description: USB Device�жϹ��Ӻ���;
*              
* Input:  flag, �жϱ�־;
*
* Output: none;
*
* Return: ERR_TRUE,�ɹ�; ERR_FALSE,ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S USBD_ISRHook(INT32U flag)		 // USB Device�жϹ��Ӻ���
{
    INT32S rst;

    rst = ERR_TRUE;
    
    #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB�豸ģʽʹ�ܼ�USB Mass Storageʹ��   
    if (flag == USBD_SPIFLASH_READY)   // ��USB Mass Storageģʽ��, ѯ��SPI Flash�Ƿ�ռ��
    {
        if (UserVars.LibSys.Flag&SPIFLASH_FATFS_FLAG)   //�ж��Ƿ�FATFSռ�� 
        {
            rst = ERR_FALSE;                            // ����ʧ��
        }
        else
        {
            UserVars.LibSys.Flag |= SPIFLASH_USB_FLAG;  // ����USBռ�ñ�־
        }
    }
    else if (flag == SD_FATFS_FLAG)   // ��USB Mass Storageģʽ��, ѯ��SD���Ƿ�ռ��
    {
        if (UserVars.LibSys.Flag&SD_FATFS_FLAG)   //�ж��Ƿ�FATFSռ�� 
        {
            rst = ERR_FALSE;                      // ����ʧ��
        }
        else
        {
            UserVars.LibSys.Flag |= SD_USB_FLAG;  // ����USBռ�ñ�־
        }
    } 
    else if (flag == NFLASH_FATFS_FLAG)   // ��USB Mass Storageģʽ��, ѯ��Nand Flash�Ƿ�ռ��
    {
        if (UserVars.LibSys.Flag&NFLASH_FATFS_FLAG)   //�ж��Ƿ�FATFSռ�� 
        {
            rst = ERR_FALSE;                            // ����ʧ��
        }
        else
        {
            UserVars.LibSys.Flag |= NFLASH_USB_FLAG;  // ����USBռ�ñ�־
        }
    }
    #endif
    
    if (flag == USBD_CONNECT_IT)     //  USB�����жϱ�־
    {
         UserVars.Flag |= USBD_CONNECT_FLAG;
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB CONNECT\r\n");
         }
         #endif 
    }
    else if (flag == USBD_DISCONNECT_IT)    // USB�Ͽ������жϱ�־
    {
         UserVars.Flag &= ~USBD_CONNECT_FLAG;
         #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB�豸ģʽʹ�ܼ�USB Mass Storageʹ��   
         UserVars.LibSys.Flag &= ~(NFLASH_USB_FLAG|SD_USB_FLAG|SPIFLASH_USB_FLAG); // ���NFLASH/SD��/SPIFLASH��USBռ�ñ�־
         #endif
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB DISCONNECT\r\n");
         }
         #endif     
    }
    
    
    else if (flag == USBD_RESET_IT)    //  USB��λ�жϱ�־
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB RESET\r\n");
         }
         #endif     
    }
    else if (flag == USBD_RESUME_IT)    // USB�ָ����¿�ʼ�жϱ�־
    {
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB RESUME\r\n");
         }
         #endif         
    }
    else if (flag == USBD_SUSPEND_IT)    // USB�����жϱ�־
    {
         UserVars.Flag &= ~USBD_CONNECT_FLAG;
         #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB�豸ģʽʹ�ܼ�USB Mass Storageʹ��   
         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             UserVars.LibSys.Flag &= ~(NFLASH_USB_FLAG|SD_USB_FLAG|SPIFLASH_USB_FLAG); // ���NFLASH/SD��/SPIFLASH��USBռ�ñ�־
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
    else if (flag == USBD_SETUP_IT)    // USB�����жϱ�־
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USBD: SETUP\r\n");
         }
         #endif 
    }    
    else if (flag == USBD_DATAIN_IT)          // USB IN�˵��ж�
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DATA IN\r\n");
         }
         #endif     
    }
    else if (flag == USBD_DATAOUT_IT)    // USB OUT�˵��ж�
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=DATA OUT\r\n");
         }
         #endif   
    }*/
    /*
    else if (flag == USBD_SOF_IT)    // USB SOF�жϱ�־
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=SOF\r\n");
         }
         #endif 
    }
    else if (flag == USBD_ISOIN_IT)    // USB ISOIN�жϱ�־
    {
         #if (DEBUG_ISRHOOK_EN>0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
            DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=ISOIN\r\n");
         }
         #endif 
    }
    else if (flag == USBD_ISOOUT_IT)    // USB ISOOUT�жϱ�־
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
* Description: USB Host�жϹ��Ӻ���;
*              
* Input:  flag, �жϱ�־;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void USBH_ISRHook(INT32U flag)		 // USB Host�жϹ��Ӻ���
{    
    if (flag == USBH_CONNECT_IT)    //  USB�����жϱ�־
    {
         UserVars.Flag |= USBH_CONNECT_FLAG;
         #if (DEBUG_ISRHOOK_EN > 0)
	     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
         {
             DebugInfo.len += sprintf(&DebugInfo.buf[DebugInfo.len],"AT+INFO=USB CONNECT\r\n");
         }
         #endif
    }
    else if (flag == USBH_DISCONNECT_IT)    // USB�Ͽ������жϱ�־
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
    else if (flag == USBH_SOF_IT)    // USB SOF�жϱ�־
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
* Description: ���⺯�����õĽ������ϵͳ�жϵ��ú���;
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
* Description: ���⺯�����õ��˳�����ϵͳ�ж����Ϻ���;
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
* Description: �жϴ򿪹رտ��ƺ���;
*              
* Input:  flag: 1, ���ж�; 0, ���ж�;
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
        if (flag>0)  // ���ж�
        {
            #if (MODULE_CLASS == STM32F407XX)
            CPU_CRITICAL_EXIT();//CPU_SR_Restore(cpu_sr);
            #else
            CPU_CRITICAL_EXIT()//CPU_SR_Restore(cpu_sr);
            #endif
        }
        else		// �ر��ж�
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
* Description: ��ʱ����, ��ʱʱ�䷶Χ: 0~65535ms;
*              
* Input:  val, ��ʱʱ�����, ��λ��ms;
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
* Description: �����ϵͳ����SPI����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
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
* Description: �����ϵ�ͷ�SPI����Ȩ��;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S SPI_ReleaseOSSem(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
	{
		OSMboxPost(OSMboxSPI, (void *)1); // �ͷŷ���Ȩ��
	}
#endif
	return ERR_TRUE;
}


#if (MODULE_TYPE == STM32F103ZE)
/***********************************************************************************
* Function: FSMC_ISRHook;
*
* Description: ������FSMC�жϴ�����;
*           
* Input:  inr���ж���Դ, 2��BANK2�ж�; 3��BANK3�ж�; 4��BANK4�ж�;;
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
        if (flag&FSMC_BANK2IT_FLAG) // FSMC BANK2�ж�
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK2, OS_FLAG_SET, (INT8U *)&err);
        }
        /*
        else if (flag&FSMC_BANK3IT_FLAG) // FSMC BANK3�ж�
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK3, OS_FLAG_SET, (INT8U *)&err);
        }
        else if (flag&FSMC_BANK4IT_FLAG) // FSMC BANK4�ж�
        {
             OSFlagPost(OSFlagSys, OSFLAG_FSMC_BANK4, OS_FLAG_SET, (INT8U *)&err);
        }*/
    }
#endif
}
/***********************************************************************************
* Function: FSMC_ISRRead;
*
* Description: ��ȡFSMC��Bank2, Bank3, Bank4״̬��������;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE: �ɹ�;  ERR_FALSE: ʧ��;
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
        if (flag&FSMC_BANK2IT_FLAG) // FSMC BANK2�ж�
        {
            OSFlagPend (OSFlagSys, OSFLAG_FSMC_BANK2, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 100, (INT8U *)&err);
        }
        /*
        else if (flag&FSMC_BANK3IT_FLAG) // FSMC BANK3�ж�
        {
             OSFlagPend (OSFlagSys, OSFLAG_FSMC_BANK3, OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, 100, (INT8U *)&err);
        }
        else if (flag&FSMC_BANK4IT_FLAG) // FSMC BANK4�ж�
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
        if (t==2000) // �ȴ�20ms
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
* Description: �����ϵͳ����NET����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
void NET_CreateOSSem(void)
{
#if	(UCOS_II_EN == 1)
    OSMboxNET  = OSMboxCreate((void*)1);  //  NET����Ȩ�ޱ���
#endif
}
/***********************************************************************************
* Function: NET_RequestOSSem;
*
* Description: �����ϵͳ����NET����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
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
* Description: �����ϵ�ͷ�NET����Ȩ��;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S NET_ReleaseOSSem(void)
{
#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxNET, (void *)1); // �ͷŷ���Ȩ��
#endif
	return ERR_TRUE;
}

/***********************************************************************************
* Function: NET_PendRXIntOSFlag;
*
* Description: �����ϵͳ������������жϱ�־;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
void NETInt_CreateOSSem(void)
{
#if	(UCOS_II_EN == 1)
    if (UserVars.Flag&OS_START_FLAG)
	{
		OSMboxNETInt  = OSMboxCreate((void*)0);  //  NET����Ȩ�ޱ���
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
* Description: �����ϵͳ������������жϱ�־;;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S  NET_PostRXIntOSFlag(void)
{
#if (UCOS_II_EN == 1)
	INT8U err;	
    if (UserVars.Flag&OS_START_FLAG)
	{
    	OSMboxPost(OSMboxNETInt, (void *)1); // �ͷŷ���Ȩ��
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
* Description: ��̬�ڴ����뺯��;
*              
* Input:  len, �����ڴ泤��, ��λ: �ֽ�;
*
* Output: none;
*
* Return: �ڴ���ʼ��ַָ��;
*
* Note:   �˺�������Ҫ����OSMboxMalloc����, ����ʼ��Ϊ1; ��������ڴ��ַΪ0, ������ʧ��;
************************************************************************************/
void *OSMalloc(INT16U len)
{
	INT8U *pMEM;
#if	(UCOS_II_EN == 1)
	INT8U  err;
	
	OSMboxPend(OSMboxMalloc, 0, &err);	 // ��ȡ����Ȩ��	 
	if(err != OS_ERR_NONE)
	{
		return 0;
	}	
#endif

	pMEM = (INT8U *)malloc(len);

#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxMalloc, (void *)1); // �ͷŷ���Ȩ��
#endif
	
	return pMEM;
}

/***********************************************************************************
* Function: OSFree;
*
* Description: ��̬�ڴ��ͷź���;
*              
* Input:  *p, �ͷ��ڴ���ʼ��ַָ��
*
* Output: none;
*
* Return: ERR_TRUE:�ͷųɹ�;  ERR_FALSE:�ͷ�ʧ��;
*
* Note:   �˺�������Ҫ����OSMboxFree����, ����ʼ��Ϊ1;
************************************************************************************/
INT32S OSFree(void *p)
{
#if	(UCOS_II_EN == 1)
	INT8U err;

	OSMboxPend(OSMboxFree, 0, &err);	 // ��ȡ����Ȩ��	 
	if(err != OS_ERR_NONE)
	{
	    return ERR_FALSE;
	}  
#endif	
	free(p); 
#if	(UCOS_II_EN == 1)
	OSMboxPost(OSMboxFree, (void *)1); // �ͷŷ���Ȩ��
#endif
	return ERR_TRUE;
}

/***********************************************************************************
* Function: PWM_ISRHook;
*
* Description: PWM�����ɻ�����жϵĹ��Ӻ���;
*           
* Input:  id: PWM����ID, PWM1_ID~PWM8_ID 
*         flag: �жϱ�־
*         PWMCH1_OK_FLAG: PWM CH1����������ɱ�־;
*         PWMCH2_OK_FLAG: PWM CH2����������ɱ�־;
*         PWMCH3_OK_FLAG: PWM CH3����������ɱ�־;
*         PWMCH4_OK_FLAG: PWM CH4����������ɱ�־;
*         PWMCH1_ERR_FLAG: PWM CH1��������ʧ�ܱ�־;
*         PWMCH2_ERR_FLAG: PWM CH2��������ʧ�ܱ�־;
*         PWMCH3_ERR_FLAG: PWM CH3��������ʧ�ܱ�־;
*         PWMCH4_ERR_FLAG: PWM CH4��������ʧ�ܱ�־;
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
* Description: ���º�����DMA1,DMA2�жϵĹ��Ӻ���;
*           
* Input:  ch: ͨ��1(DMA_CH1)~8(DMA_CH8)
*         flag: �ж����: DMA_IT_TC, ��������жϱ�־
*                         DMA_IT_HT, �봫������жϱ�־
*                         DMA_IT_TERR, ��������жϱ�־
*                         DMA_IT_FIFOERR, ������FIFO�����־   
*                         DMA_IT_DERR, ������ֱ�Ӵ����־
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
    
    // ���±�д�Լ����жϴ������
    if(flag&DMA_IT_TC) // ��������ж�
    {
        
    }
    if(flag&DMA_IT_HT) // �봫������ж�
    {
        
    }
    if(flag&DMA_IT_TERR) // ��������ж�
    {
        
    }
    #if (MODULE_CLASS == STM32F407XX)    
    if(flag&DMA_IT_FIFOERR) // ������FIFO�����־ 
    {
        
    }    
    if(flag&DMA_IT_DERR)   // ������ֱ�Ӵ����־
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
    
    // ���±�д�Լ����жϴ������
    if(flag&DMA_IT_TC) // ��������ж�
    {
        
    }
    if(flag&DMA_IT_HT) // �봫������ж�
    {
        
    }
    if(flag&DMA_IT_TERR) // ��������ж�
    {
        
    }
    #if (MODULE_CLASS == STM32F407XX)    
    if(flag&DMA_IT_FIFOERR) // ������FIFO�����־ 
    {
        
    }    
    if(flag&DMA_IT_DERR)   // ������ֱ�Ӵ����־
    {
        
    }
    #endif    
}

/***********************************************************************************
* Function: API_OSFlagPostHook;
*
* Description: ���������õȴ���־����;
*              
* Input:  flag: �ȴ���־, ��const.h�ж���
*
* Output: none;
*
* Return: none;
*
* Note:   �������ֻ�ṩ���������жϵ���, ���û���Ҫ�޸ĸú���;
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
* Description: �������ȡ�ȴ���־����;
*              
* Input:  flag: �ȴ���־, ��const.h�ж���
*         TimeOut: ��ʱʱ��, ��λms, ���Ϊ0������Ϊ0xFFFFFFFF, �������ߵȴ�
*
* Output: none;
*
* Return: ERR_TRUE: �ɹ�;  ERR_FALSE: ʧ��; ERR_TIMEOUT: ��ʱʧ��;
*
* Note:   �������ֻ�ṩ�����������, ���û���Ҫ�޸ĸú���;
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
        UserVars.LibSys.APIWaitFlag &= ~flag;  // �����־
        return ERR_TRUE;
    }
    else
    {
        return ERR_TIMEOUT;
    }        
#endif
}



/***********************************************************************************/
// �ļ�����
/***********************************************************************************/




