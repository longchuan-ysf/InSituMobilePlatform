/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: sd.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���FATFS�ļ�ϵͳSD���ӿ���������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S SD_Init(SD_PARA *pPara);
*          2. INT8U  SD_Read(INT8U *p, INT32U sector, INT8U count);
*          3. INT8U  SD_Write(INT8U *p, INT32U sector, INT8U count);
*          4. INT32S SD_Ctrl(INT8U Cmd,  INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __SD_H
#define __SD_H
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// ��������
/************************************************************************************/
#define SD_NOINIT		0x01	// ������������û�б���ʼ����־
#define SD_NODISK		0x02	// û��SD����־
#define SD_PROTECT	    0x04	// д������־ 
#define SD_POWER		0x08	// �򿪵�Դ��־

#define SD_SPI_MODE     0  // SD��: SPI����ģʽ
#define SD_SDIO_MODE    1  // SD��: SDIO����ģʽ

// SD�����ƹܽŲ����ṹ 
typedef struct
{
    INT8U  INR;   // ���뿨�ܽŶ���
    INT8U  WP;    // д�����ܽŶ���
    INT8U  CS;    // Ƭѡ�ܽŶ���
    INT8U  CPWR;  // ��Դ���ƹܽŶ���
}SDCTRL_PIN;

// SD����ʼ����������  
typedef struct
{	
    INT16U Flag;          // ������־
    INT8U  Mode;          // SD����ģʽ
    INT8U  SPIx_ID;       // ѡ��SPI ID
	SDCTRL_PIN Pin;       // SD�����ƹܽ�
}SD_PARA;


// SD_Ctrl()���ƺ��������
#define CMD_SD_SYNC          0  // SD���ͬ������: ���SD�Ƿ�����γ�, ������򿪵�Դ����ʼ��, �γ���رյ�Դ
#define CMD_SD_STATUS        1  // ��ȡSD��״̬
#define CMD_SD_SECTOR_COUNT  2  // ��ȡSD����������
#define CMD_SD_SECTOR_SIZE   3  // ��ȡSD��������С
#define CMD_SD_TYPE          4  // ��ȡSD������

/*************************************************************************************/
//
// 				FATFS�ļ�ϵͳSD���ӿ���������;
//
/*************************************************************************************/

/***********************************************************************************
* Function: SD_Init;
*
* Description: SD����ʼ������;
*              
* Input:  *pPara ��ʼ������;  
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SD_Init(SD_PARA *pPara);

/***********************************************************************************
* Function: SD_Read;
*
* Description: FatFS�ӿڶ�ȡSD���������ݺ���;
*              
* Input:  *p, ��ȡ���ݻ���ָ��;
*         sector, ��ȡ������ʼ���  
*         count, ��ȡ�������� (1..255)    
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U SD_Read(INT8U *p, INT32U sector, INT8U count);

/***********************************************************************************
* Function: SD_Write;
*
* Description: FatFS�ӿ�д��SD���������ݺ���;
*              
* Input:  *p, д�����ݻ���ָ��;
*         sector, д��������ʼ���  
*         count, д���������� (1..255)  
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U SD_Write(INT8U *p, INT32U sector, INT8U count);

/***********************************************************************************
* Function: SD_Ctrl;
*
* Description: FatFS�ӿ�SD�����ƺ���;
*              
* Input:  Cmd,  ��������, ����:
*         CMD_SD_SYNC:           SD���ͬ������: ���SD�Ƿ�����γ�, ������򿪵�Դ����ʼ��, �γ���رյ�Դ
*         CMD_SD_STATUS:         ��ȡSD��״̬
*         CMD_SD_SECTOR_COUNT:   ��ȡSD����������
*         CMD_SD_BLOCK_SIZE:     ��ȡSD�����С
*         CMD_SD_SECTOR_SIZE:    ��ȡSD��������С
*         CMD_SD_TYPE:           ��ȡSD������
*         Para, ����,Ĭ��0,��ʱδ��
*
* Output: none;
*
* Return: ���ݲ�ͬ����ز�ͬ��ֵ
*         ��Cmd��CMD_SD_SYNC��CMD_SD_STATUSʱ:
*         ����SD��״̬:   
*         STA_NOINIT(bit0=1)�� SD��û�г�ʼ�� 
*         STA_NODISK(bit1=1)�� û�з���SD�� 
*         STA_PROTECT(bit2=1)��SD��д���� 
*
* Note:   none;
************************************************************************************/
INT32S SD_Ctrl(INT8U Cmd,  INT32U Para);

#endif
