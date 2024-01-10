/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: CH455.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���CH455��д���������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. void CH455_Read(void);
*          2. INT8U CH455_Read(void);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CH455_H 
#define __CH455_H

#include "const.h"
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
// ��EMB8628I��JP4����4*4����: ����L1-L4,C1-C4
// ����ֵ����
#define	 KEY_1				0x1F
#define	 KEY_2				0x1E
#define	 KEY_3				0x1D
#define	 KEY_A				0x1C
#define	 KEY_4				0x17
#define	 KEY_5				0x16
#define	 KEY_6				0x15
#define	 KEY_B				0x14
#define	 KEY_7				0x0F
#define	 KEY_8				0x0E
#define	 KEY_9				0x0D
#define	 KEY_C				0x0C
#define	 KEY_X				0x07
#define	 KEY_0				0x06
#define	 KEY_J				0x05
#define	 KEY_D				0x04

#define	 KEY_NO				0x00  // �ް���

// CH455���Ʒ�ʽ
#define CH455_MODE_I2C    0	 // CH455��I2C���߿���
#define CH455_MODE_IO	  1	 // CH455��IO(ģ��I2C����)����

//#define I2C_ID            I2C3_ID  // ѡ��I2C ID 

// ����ݵ�·ͼ�����ﶨ��IO�ܽ�
//#define KEY_SCL         PA8
//#define KEY_SDA         PC9
//#define K_INT           PD3 // CH455�ж���IO����

// CH455��ʼ�������ṹ
typedef struct
{   
    INT8U  Mode;           // ������־
    INT8U  I2C;             // I2Cѡ��ID
    INT8U  SDAPin;         // SDA�ܽ�
    INT8U  SCLPin;         // SCL�ܽ�
    INT8U  INTPin;         // INT�жϹܽ�
}CH455_PARA;

/************************************************************************************
//
//                 ����Ӳ����������
//
*************************************************************************************/

/***********************************************************************************
* Function: CH455_Init;
*
* Description: CH455��ʼ������;
*           
* Input:  *pPara: ��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S CH455_Init(CH455_PARA *pPara);

/***********************************************************************************
* Function: CH455_Read;
*
* Description: CH455��ȡ����ֵ����;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: ����ֵ4-7/12-15/20-23/28-31/36-39/44-47/52-55��0(�ް�������);
*
* Note:   none;
************************************************************************************/
INT8U CH455_Read(void);
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

