/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: APP_Init.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ����������ܵ�Ӳ����ʼ������ͷ�ļ�, ����STM32F107VC_Conifg.h������ý��г�ʼ��
*
* Others: �ο�API_Init()����;
*
* Function List: void  API_Init(void);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __API_INIT_H 
#define __API_INIT_H 	 

#include "UserVars.h"
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
/***********************************************************************************
* Function: APP_ParaInit;
*
* Description: �ָ�����Ĭ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaInit(USER_VARS *p);
/***********************************************************************************
* Function: APP_ParaRead;
*
* Description: ��ȡ�洢��������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaRead(USER_VARS *p); 
/***********************************************************************************
* Function: APP_ParaSave;
*
* Description: �洢��������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void APP_ParaSave(USER_VARS *p);

/***********************************************************************************
* Function: API_Init;
*
* Description: �������ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  API_Init(void);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

