/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: crc.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���CRC������������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32U CRC32(INT32U *p, INT16U len);
*          2. INT16U CRC16(INT8U *p, INT16U len);
*          3. INT16U CRC16_2(INT8U *p1, INT16U len1, INT8U *p2, INT16U len2);
*          4. INT8U  CRC8(INT8U *p, INT16U len);
*          5. INT32S CRC_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __CRC_H 
#define __CRC_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// CRC�����
#define CRC_CMD_SetCRC32   0 	//	Computes the 32-bit CRC of a given data word(32-bit).
#define CRC_CMD_SetCRC8	   1 	//	Stores a 8-bit data in the Independent Data(ID) register.
#define CRC_CMD_GetCRC8	   2 	//	Returns the 8-bit data stored in the Independent Data(ID) register
#define CRC_CMD_GetCRC32   3 	//	Returns the current 32-bit CRC value.
#define CRC_CMD_ResetCRC32 4	// Resets the CRC Data register (DR)

/*************************************************************************************/
//
// 					 CRCӲ��������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: CRC32;
*
* Description: ����32-bit CRC����;
*              
* Input:  *p,  Ҫ����CRC32������ָ��;
*         len�����ݳ���;
*
* Output: none;
*
* Return: CRCУ����;
*
* Note:   none;
************************************************************************************/
INT32U CRC32(INT32U *p, INT16U len);

/***********************************************************************************
* Function: CRC16;
*
* Description: CRC16���㺯��;
*              
* Input:  *p,  Ҫ����CRC16������ָ��;
*         len�����ݳ���;
*
* Output: none;
*
* Return: CRCУ����;
*
* Note:   none;
************************************************************************************/
INT16U CRC16(INT8U *p, INT16U len);

/***********************************************************************************
* Function: CRC16_2;
*
* Description: ������CRC16���㺯��;
*              
* Input:  *p1,*p2  Ҫ����CRC16������ָ��;
*         len1��len2 ���ݳ���;
*
* Output: none;
*
* Return: CRCУ����;
*
* Note:   *p1, len1��һ������ǰ; *p2, len2��һ�����ں�;
************************************************************************************/
INT16U CRC16_2(INT8U *p1, INT16U len1, INT8U *p2, INT16U len2);

/***********************************************************************************
* Function: CRC8;
*
* Description: CRC8���㺯��;
*              
* Input:  *p,  Ҫ����CRC8������ָ��;
*         len�����ݳ���;
*
* Output: none;
*
* Return: CRCУ����;
*
* Note:   none;
************************************************************************************/
INT8U CRC8(INT8U *p, INT16U len);

/***********************************************************************************
* Function: CRC_Ctrl;
*
* Description: CRC������Ʋ���;
*              
* Input:  Cmd,  CRC��������;
*         Para��CRC������Ʋ���;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S CRC_Ctrl(INT8U Cmd, INT32U Para);
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/




