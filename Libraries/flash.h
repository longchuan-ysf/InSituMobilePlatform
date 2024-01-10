/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: flash.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���FLASHӲ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S Flash_Write(INT32U StartAddr, INT8U *p, INT16U len);
*          2. INT32S Flash_Read(INT32U StartAddr, INT8U *p, INT16U len);
*          3. INT32S Flash_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __FLASH_H 
#define __FLASH_H
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ������������
/************************************************************************************/

/************************************************************************************/
// Flash_Ctrl()����ָ���
/************************************************************************************/
#define CMD_FLASH_UNLOCK         0   // FLASH����
#define CMD_FLASH_LOCK           1   // FLASH����
#define CMD_FLASH_PAGE_ERASE     2   // FLASHҳ����

// STM32F M4����, ������������
#define FLASH_SECTOR_0     0  // Sector Number 0, 16KB   
#define FLASH_SECTOR_1     1  // Sector Number 1, 16KB   
#define FLASH_SECTOR_2     2  // Sector Number 2, 16KB   
#define FLASH_SECTOR_3     3  // Sector Number 3, 16KB   
#define FLASH_SECTOR_4     4  // Sector Number 4, 64KB   
#define FLASH_SECTOR_5     5  // Sector Number 5, 128KB  
#define FLASH_SECTOR_6     6  // Sector Number 6, 128KB   
#define FLASH_SECTOR_7     7  // Sector Number 7, 128KB 
#define FLASH_SECTOR_8     8  // Sector Number 8, 128KB  
#define FLASH_SECTOR_9     9  // Sector Number 9, 128KB   
#define FLASH_SECTOR_10    10 // Sector Number 10, 128KB  
#define FLASH_SECTOR_11    11 // Sector Number 11, 128KB 

/*************************************************************************************/
//
// 					 FLASHӲ��������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: Flash_Write;
*
* Description: ��FLASHд����;
* 
* Input:  StartAddr, д��FLASH����ʼ��ַ; p, д����ָ��; len, ���ݳ���
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   lenӦ����4�ı���;
************************************************************************************/
INT32S Flash_Write(INT32U StartAddr, INT8U *p, INT32U len);

/***********************************************************************************
* Function: Flash_Read;
*
* Description: ��ȡFLASH����;
* 
* Input:  StartAddr, ��FLASH����ʼ��ַ; p, ������ָ��; len, ���ݳ���
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   lenӦ����4�ı���;
************************************************************************************/
INT32S Flash_Read(INT32U StartAddr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Flash_Ctrl;
*
* Description: FLASH���ƺ���;
* 
* Input:  Cmd: �������CMD_FLASH_UNLOCK, FLASH����
*                        CMD_FLASH_LOCK, FLASH����
*                        CMD_FLASH_PAGE_ERASE, FLASHҳ����(2KB)
*         Para: ���Ʋ���; 
*                        ��������CMD_FLASH_UNLOCK��CMD_FLASH_LOCK, Para����Ϊ0;
*                        ��������CMD_FLASH_PAGE_ERASE, ParaΪ������ҳ���������;
*           
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ����CMD_FLASH_PAGE_ERASE����, STM32F1xxϵ��оƬ: ��ҳ(2KB)����;
*         STM32F4xxϵ��оƬ: ������(FLASH_SECTOR_0~FLASH_SECTOR_11)����;
************************************************************************************/
INT32S Flash_Ctrl(INT8U Cmd, INT32U Para);

#endif 

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/