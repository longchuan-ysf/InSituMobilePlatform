/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: fsmc.h
* Project  : STM32F107VC/103VE/103ZE/407VEģ��������
* Processor: STM32F107VC/103VE/103ZE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���FSMC����Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S FSMC_Init(FSMC_PARA *pPara);
*          2. INT16U FSMC_Read(INT16U addr);
*          3. void FSMC_Write(INT16U addr, INT16U val);
*          4. INT32S FSMC_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __FSMC_H
#define __FSMC_H
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"

// FSMC�жϱ�־����
//#define FSMC_ITBANK1_FLAG   0x01
//#define FSMC_ITBANK2_FLAG   0x02
//#define FSMC_ITBANK3_FLAG   0x04
//#define FSMC_ITBANK4_FLAG   0x08

// Flag����
#define FSMC_SRAM_EN      0x0001   // ������չRAMʹ�ܱ�־
#define FSMC_NFLASH_EN    0x0002   // ������չNANDʹ�ܱ�־
#define FSMC_NET_EN       0x0004   // ������չNETʹ�ܱ�־
#define FSMC_EXBUS_EN     0x0008   // ������չ����ʹ�ܱ�־
#define FSMC_NFLASH_ECCEN 0x0010   // Nand flash ECCʹ�ܱ�־
#define FSMC_NFLASH_ITFLAG  0x0020   // Nand flash �жϲ�����־

// FSMC�жϱ�־����
#define FSMC_BANK2IT_FLAG   0x2000
#define FSMC_BANK3IT_FLAG   0x4000
#define FSMC_BANK4IT_FLAG   0x8000

// FSMC��ʼ����������  
typedef struct
{	
	INT16U Flag;          // ������־
    INT16U ECCSize;       // Nand Flash ECCҳ���С
    INT32U SRAMSize;      // ����SRAM����
    INT8U  EXBusAddrSet;  // �ⲿ���ߵ�ַ����ʱ��(��Χ��0~15)��ʵ�ʽ���ʱ��(EXBUS_ADDSET+1)��HCLK;
    INT8U  EXBusDataSet;  // �ⲿ�������ݱ���ʱ��(��Χ��1~255)��ʵ�ʱ���ʱ�䣺��(EXBUS_DATAST+3)��HCLK, д(DATAST+1)��HCLK;
    INT8U  EXBusTurn;     // �ⲿ���߻ָ�ʱ��(��Χ��0~15)��ʵ�ʻָ�ʱ��(EXBUS_TURN+1)��HCLK��1, ʹ��;  0, �ر�;
}FSMC_PARA;


// FSMC_Ctrl() ���������
#define CMD_FSMC_SRAM_TEST          0 	 // SRAM����

/*************************************************************************************/
//
// 					FSMCӲ��������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: FSMC_Init;
*
* Description: FSMC��ʼ������;
* 
* Input:  *pPara, ��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S FSMC_Init(FSMC_PARA *pPara);


/***********************************************************************************
* Function: FSMC_Read;
*
* Description: ���ⲿ��������;
* 
* Input:  addr, �����ݵ�ַ, ��Χ0~31(��Ի���ַ����Ե�ַ);	
*
* Output: none;
*          		
* Return: 16λ����;
*
* Note:   none;
************************************************************************************/
INT16U FSMC_Read(INT16U addr);

/***********************************************************************************
* Function: FSMC_Write;
*
* Description: ���ⲿ����д����;
* 
* Input:  addr, д���ݵ�ַ, ��Χ0~31(��Ի���ַ����Ե�ַ);	 val, Ҫд��16λ����
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void FSMC_Write(INT16U addr, INT16U val);

/***********************************************************************************
* Function: FSMC_Ctrl;
*
* Description: FSMC���ƺ���;
* 
* Input:  Cmd: CMD_FSMC_SRAM_TEST:  SRAM����
*         Para: Ĭ��0
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S FSMC_Ctrl(INT8U Cmd, INT32U Para);

#endif 