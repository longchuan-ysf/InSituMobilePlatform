/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: adc.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���ģ��/����ת��(ADC)Ӳ����������ͷ�ļ�;
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
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// ADC��������
#define ADC1_ID		0 
#define ADC2_ID    	1 
#define ADC3_ID    	2 

// ����ģ��������˿���Ŷ���, ���ܸ���
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
#define AI_ID_NONE  0xFF  // �޶��� 


// ����ת������
#define ADC_SAMP1T17US	 0  // ADC����ת��ʱ��Ϊ14����(1.5+12.5)  :  1.17us
#define ADC_SAMP1T67US	 1  // ADC����ת��ʱ��Ϊ20����(7.5+12.5)  �� 1.67us
#define ADC_SAMP2T17US	 2  // ADC����ת��ʱ��Ϊ26����(13.5+12.5) �� 2.17us
#define ADC_SAMP2T58US	 3  // ADC����ת��ʱ��Ϊ31����(28.5+12.5) �� 2.58us
#define ADC_SAMP4T5US	 4  // ADC����ת��ʱ��Ϊ54����(41.5+12.5) �� 4.5us
#define ADC_SAMP5T67US	 5  // ADC����ת��ʱ��Ϊ68����(55.5+12.5) �� 5.67us
#define ADC_SAMP7T0US	 6  // ADC����ת��ʱ��Ϊ84����(71.5+12.5) �� 7us
#define ADC_SAMP21T0US	 7  // ADC����ת��ʱ��Ϊ252����(239.5+12.5)��21us

// ģ��ģ����������(������ģ��ģ��ܽ�)����, ���ܸ���
#define AIN0           0      // AIN0��Ӧ���
#define AIN1           1      // AIN1��Ӧ���
#define AIN2           2      // AIN2��Ӧ���
#define AIN3           3      // AIN3��Ӧ���
#define AIN4           4      // AIN4��Ӧ���
#define AIN5           5      // AIN5��Ӧ���
#define AIN6           6      // AIN6��Ӧ���
#define AIN7           7      // AIN7��Ӧ���
#define AIN8           8      // AIN8��Ӧ���
#define AIN9           9      // AIN9��Ӧ���
#define AIN10          10     // AIN10��Ӧ���
#define AIN11          11     // AIN11��Ӧ���
#define AIN12          12     // AIN12��Ӧ���
#define AIN13          13     // AIN13��Ӧ���
#define AIN14          14     // AIN14��Ӧ���
#define AIN15          15     // AIN15��Ӧ���

// ����ADCת��ֵ�����ʽ
#define ADC_ISROUT    0     // ѡ���ж����AD����ֵ
#define ADC_READOUT   1     // ѡ��ADC_Read()������ȡ����ֵ

// Flag������־����
#define ADC_ISROUT_FLAG      0x8000   // �����жϺ������Ӻ������AD��������
// STM32F103XX��STM32F107XXϵ��ģ��ʹ�������־
#define ADC_TIM5CH1_FLAG     0x0001   // ʹ��TIM5�Ӷ�ʱ��1��ʱAD����
#define ADC_TIM5CH2_FLAG     0x0002   // ʹ��TIM5�Ӷ�ʱ��2��ʱAD����
#define ADC_TIM5CH3_FLAG     0x0004   // ʹ��TIM5�Ӷ�ʱ��3��ʱAD����
#define ADC_TIM5CH4_FLAG     0x0008   // ʹ��TIM5�Ӷ�ʱ��4��ʱAD����
#define ADC_TIM5MAIN_FLAG    0x0010   // ʹ��TIM5����ʱ����ʱAD����

// STM32F407XXϵ��ģ��ʹ�������־
#define ADC_TIM14MAIN_FLAG   0x0020   // ʹ��TIM14����ʱ����ʱAD����
#define ADC_TIM14CH1_FLAG    0x0040   // ʹ��TIM14�Ӷ�ʱ��1��ʱAD����

typedef struct
{
	INT16U  len;		        // ADC���ݳ���
	INT16S  *pBuf;              // ADC��������ָ��
}ADC_VAR;


// ADC�����ṹ 
typedef struct
{
    INT16U Flag;                 // ������־
    INT8U  Mode;                 // ����ģʽ���ο�����ģʽ����
    INT8U  AINum;                // AIx����ͨ�����Ӷ˿�����
    INT8U  *pAITab;              // AI����ͨ��˳��ת����ָ��
    
    INT8U  AvgNum;               // �����������������ƽ��ֵ, ��Χ 1~256, ע�⣺��ֵ̫���ռ�úܴ��ڴ�ռ�
    INT8U  Freq;                 // AD����Ƶ��, ÿ���Ӳ�������
    INT16U SampleTime;           // ADC����ת��ʱ��
    INT16S *pBuf;                // AD�ɼ����ݻ���ָ��
}ADC_PARA;

// ADC_Ctrl ���������
#define  CMD_ADC_ENA     0 // ADC��ʼת��
#define  CMD_ADC_DIS     1 // ADCֹͣת��
#define  CMD_ADC_SWSTART 2 // ADC����ת��



/*************************************************************************************/
//
// 					 ADCӲ��������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: ADC_Init;
*
* Description: ADC��ʼ������;
*              
* Input:  id, ADC������ʶ��ADC1_ID,ADC2_ID,ADC3_ID; Ĭ��ADC1_ID
*         *pPara, ADC��ʼ������;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ��ʼ����ɣ�ADC��û�п�ʼ����, �������ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0)ʹ��ADC
*         �ſ�ʼ������
************************************************************************************/
INT32S  ADC_Init (INT8U id, ADC_PARA *pPara);

/***********************************************************************************
* Function: ADC_Read;
*
* Description: ADC��ȡ����;
*              
* Input:  id, ADC��ʶ(ADC1_ID, ADC2_ID, ADC3_ID), ��ֻ֧��ADC1_ID;
*         *p, ��ȡ��������ָ��; len����ȡ���ݸ��� 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S ADC_Read(INT8U id, INT16S *p, INT8U len);

/***********************************************************************************
* Function: ADC_Ctrl;
*
* Description: ADC���ƺ���;
*              
* Input:  id, ADC��ʶ(ADC1_ID, ADC2_ID, ADC3_ID), ��ֻ֧��ADC1_ID
*         Cmd��ADC��������, CMD_ADC_ENA:��ʼת��; CMD_ADC_DIS: ֹͣת��;
*		  Para�����Ʋ���
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S ADC_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif 
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
