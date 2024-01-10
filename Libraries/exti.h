/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: exti.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ����ⲿ�ж�/�¼�������(EXTI)Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S EXTI_Init(EXTI_PARA *pPara);
*          2. INT32S EXTI_Ctrl(INT8U id, INT8U Cmd);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __EXIT_H 
#define __EXIT_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ��������
/************************************************************************************/
// �ж�����ID���壺
#define EXTI0_ID		 0     // IO�ж�0����
#define EXTI1_ID		 1     // IO�ж�1����
#define EXTI2_ID		 2     // IO�ж�2����
#define EXTI3_ID		 3     // IO�ж�3����
#define EXTI4_ID		 4     // IO�ж�4����
#define EXTI5_ID		 5     // IO�ж�5����
#define EXTI6_ID		 6     // IO�ж�6����
#define EXTI7_ID		 7     // IO�ж�7����
#define EXTI8_ID		 8     // IO�ж�8����
#define EXTI9_ID 	     9     // IO�ж�9����
#define EXTI10_ID	     10    // IO�ж�10����
#define EXTI11_ID	     11    // IO�ж�11����
#define EXTI12_ID	     12    // IO�ж�12����
#define EXTI13_ID	     13    // IO�ж�13����
#define EXTI14_ID	     14    // IO�ж�14����
#define EXTI15_ID	     15    // IO�ж�15����

#define EXTI16_PVD_ID	            16    // IO�ж�16����, EXIT��16���ӵ�PVD���
#define EXTI17_RTCAlarm_ID	        17    // IO�ж�17����, EXIT��17���ӵ�RTC�����¼�
#define EXTI18_USBWakeUp_ID	        18    // IO�ж�18����, EXIT��18���ӵ�USB OTG FS�����¼�
#define EXTI19_NETWakeUp_ID	        19    // IO�ж�19����, EXIT��19���ӵ���̫�������¼�
// ������STM32F4XXоƬ��������
#define EXTI20_USBHSWakeUp_ID       20   // IO�ж�20����, EXIT��20���ӵ�USB OTG HS�����¼�
#define EXTI21_RTCTSE_ID	        21   // IO�ж�21����, EXIT��21���ӵ�RTC���ֺ�ʱ����¼�
#define EXTI22_RTCWakeUp_ID	        22   // IO�ж�22����, EXIT��22���ӵ�RTC�����¼�

// �ж�ģʽ����
#define EXTI_RISING            0    // �������жϺ��¼�;
#define EXTI_FALLING           1    // �½����жϺ��¼�;
#define EXTI_RISING_FALLING    2    // �������½��ض��жϺ��¼�;

// EXInt_Ctrl��������Cmd����
#define EXTI_CMD_DIS           0    // �ر��жϺ��¼���������
#define EXTI_CMD_INT_ENA       1    // ���ж�����
#define EXTI_CMD_EVENT_ENA     2    // ���¼���������

// EXTI_Init() ��ʼ���������ݽṹ
typedef struct
{   
    INT8U  id;             // �ж�idѡ��,EXTI0_ID~EXTI15_ID, EXTI16_PVD_ID, EXTI17_RTCAlarm_ID, EXTI18_USBWakeUp_ID, EXTI19_NETWakeUp_ID;
                           //            STM32F4XXоƬ��������: EXTI20_USBHSWakeUp_ID, EXTI21_RTCTSE_ID, EXTI22_RTCWakeUp_ID    
    INT8U  Mode;           // �ж�ģʽ����: EXTI_RISING, EXTI_FALLING, EXTI_RISING_FALLING 
    INT8U  IOx;            // ѡ��IO�˿�: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
}EXTI_PARA;

/*************************************************************************************/
//
// 					 �ⲿ�ж�/�¼�������(EXTI)Ӳ��������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: EXTI_Init;
*
* Description: �ⲿIO�жϳ�ʼ������;
* 
* Input:  *pPara, �жϳ�ʼ������ָ��
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ��ʼ���������û�������ж�, ��Ҫ����EXTI_Ctrl()�����ж�;
************************************************************************************/
INT32S EXTI_Init(EXTI_PARA *pPara);

/***********************************************************************************
* Function: EXTI_Ctrl;
*
* Description: �ⲿIO�ж�ʹ�ܿ��ƺ���;
* 
* Input:  id,  �ж�������EXTI0_ID~EXTI15_ID, EXTI16_PVD_ID, EXTI17_RTCAlarm_ID, EXTI18_USBWakeUp_ID, EXTI19_NETWakeUp_ID;
*              STM32F4XXоƬ��������: EXTI20_USBHSWakeUp_ID, EXTI21_RTCTSE_ID, EXTI22_RTCWakeUp_ID 
*
*		  Cmd: EXTI_CMD_DIS:       �ر��жϺ��¼���������
*              EXTI_CMD_INT_ENA:   ���ж�����
*              EXTI_CMD_EVENT_ENA: ���¼���������
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S EXTI_Ctrl(INT8U id, INT8U Cmd);
#endif

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/