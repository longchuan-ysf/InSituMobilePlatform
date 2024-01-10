/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: dac.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�������/ģ��ת��(DAC)Ӳ����������ͷ�ļ�;
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
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// DAC��������
#define DAC1_ID     0  
#define DAC2_ID     1 

// DAC����ģʽ����
#define DAC_MODE_MTOUT	    0	// �ֶ����
#define DAC_MODE_ATOUT_N	1	// �������1~N�������е����ݺ�ֹͣ
#define DAC_MODE_ATOUT	    2	// ������������е�����, ��ֹͣ;

// DAC����״̬
#define DAC_WORK        0x0001  // DAC���ڹ��� 
#define DAC_STOP        0x0000  // DACֹͣ���� 

// DAC�ܽŶ���
#define DAC1_PIN        PA4  // DAC1�ܽŶ��� 
#define DAC2_PIN        PA5  // DAC2�ܽŶ��� 

// ADC��ʼ�������ṹ
typedef struct
{   
    INT16U Flag;           // ������־
    INT8U  Mode;           // ����ģʽ
    INT8U  pin;            // DAC�ܽ�
    INT16U *pbuf;          // ����ָ��
    INT16U len;            // ���泤��
    INT32U Freq;           // ����Ƶ��
}DAC_PARA;

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// DAC_Ctrl ���������
#define CMD_DAC_DIS           0		 // ֹͣDAC
#define CMD_DAC_ENA           1		 // ʹ��DAC
#define CMD_DAC_FREQ          2		 // ����DAC����Ƶ��
#define CMD_DAC_STATUS        3		 // ��ȡDAC״̬, ����0, ֹͣ; ����1, ����ִ�����
#define CMD_DAC_RST           4		 // ��λDAC�Ĵ���Ϊ��ʼ״̬
#define CMD_DAC_CLOSE         5		 // �ر�DACʱ��,Ҳ���ǹر�DAC����,����ʡ�� 
   
/*************************************************************************************/
//
// 					 DACӲ��������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: DAC_Init;
*
* Description: DAC��ʼ������;
*              
* Input:  id, ADC����(DAC1_ID~DAC2_ID);
*         DAC_PARA *pPara, DAC���ò���ָ��
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S DAC_Init (INT8U id, DAC_PARA *pPara);

/***********************************************************************************
* Function: DAC_Write;
*
* Description: �ֶ�����DAC���������ֱ����DACд����ת���ɵ�ѹ���;
* 
* Input:  id, ADCʶ���(DAC1_ID~DAC2_ID);
*         val, д�������, ������ֵ��Χ:0x0000~0x0fff;
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
* Description: DAC�������;
* 
* Input:  id, ADCʶ���: DAC1_ID~DAC2_ID;
*         Cmd,  ADC�������
*         CMD_DAC_DIS,    ֹͣDAC; 
*         CMD_DAC_ENA,    ʹ��DAC; 
*         CMD_DAC_FREQ,   ����DAC����Ƶ��, Para�����õ�Ƶ��;
*         CMD_DAC_STATUS, ��ȡDAC״̬, ����DAC_STOP, ֹͣ; ����DAC_WORK, ����ִ�����; 
*         CMD_DAC_RST,    ��λDAC�Ĵ���Ϊ��ʼ״̬; ParaĬ��Ϊ0;
*         CMD_DAC_CLOSE,  �ر�DACʱ��,Ҳ���ǹر�DAC����,����ʡ�� ; 
*         Para��ADC������Ʋ���, ParaĬ��Ϊ0;
*
* Output: none;
*          		
* Return: �޷��ص��������ERR_TRUE; �з��ص��������Ӧ����;
*
* Note:   none;
************************************************************************************/
INT32S DAC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif 


