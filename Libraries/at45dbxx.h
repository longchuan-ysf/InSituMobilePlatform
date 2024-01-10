/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: AT45DBXX.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����AT45DBXXϵ��FLASH��д��������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S AT45DBXX_Init(AT45DBXX_PARA *pPara);
*          2. INT32S AT45DBXX_WritePage(INT8U *p, INT32U page, INT32U count);
*          3. INT32S AT45DBXX_ReadPage(INT8U *p, INT32U page, INT32U count);
*          4. INT32S AT45DBXX_Write(INT8U *p, INT32U addr, INT32U len);
*          5. INT32S AT45DBXX_Read(INT8U *p, INT32U addr, INT32U len);
*          6. INT32S AT45DBXX_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __AT45DBXX_H
#define __AT45DBXX_H
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// SPI FLASH���Ͷ���
#define W25QXX     0
#define AT45DBXX   1

// оƬ�ͺŶ���, ���ɸ���
#define  AT45DB081      0   // 1MB
#define  AT45DB161      1   // 2MB, Ĭ��
#define  AT45DB321      2   // 4MB

// ������ʶID 
#define  AT45DBXX_ID 0x1F

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// AT45DBXX_Ctrl() ���������
#define CMD_AT45DBXX_STATUS           0 	 // ��ȡAT45DBXX״̬
#define CMD_AT45DBXX_PAGE_ERASE       1 	 // ����ҳ 
#define CMD_AT45DBXX_BLOCK_ERASE      2 	 // ����4KB��, 8ҳ 
#define CMD_AT45DBXX_SECTOR_ERASE     3 	 // ����128KB����, 32�飬256ҳ 
#define CMD_AT45DBXX_CHIP_ERASE       4 	 // ��������оƬ 
#define CMD_AT45DBXX_RDID             5 	 // ��ȡ���̼�����ID

// Flag ��־
#define AT45DBXX_TYPE_FLAG     0x4000   // AT45DBXX���ͱ�־

//SPI Flash(AT45DBXX) ��ʼ����������  
typedef struct
{							 
	//INT8U  Type;          // оƬоƬ����, �̶�Ϊ1: AT45DBXX
    //INT8U  Model;         // оƬ�ͺ�
    INT16U Flag;          // ������־
    INT8U  SPI_ID;        // ѡ��SPI ID
	INT8U  CS_Pin;        // Ƭѡ�ܽ�

	INT16U SectorSize;	  // Flash������С(��λ���ֽ�) 
    INT32U SectorNum;	  // Flash�������� 
    INT32U FatFSSectorNum; // FatFS�ļ�ϵͳռ����������
}AT45DBXX_PARA;  

/*************************************************************************************/
//
// 				AT45DBXXϵ��FLASH��д��������
//
/*************************************************************************************/

/***********************************************************************************
* Function: AT45DBXX_Init;
*
* Description: AT45DBXX��ʼ������;
*              
* Input:  *pPara, ��ʼ������ָ��;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S AT45DBXX_Init(AT45DBXX_PARA *pPara);

/***********************************************************************************
* Function: AT45DBXX_WritePage;
*
* Description: ��ҳд��FLASH����;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; page,д��flash���ݵ���ʼҳ; count, Ҫд�����ݵ�ҳ��;
*         page��Χ: 0~4095/8191(AT45DB161/AT45DB321); count��Χ��count + page<=4095/8191;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ÿҳ��512�ֽ�;
************************************************************************************/
INT32S AT45DBXX_WritePage(INT8U *p, INT32U page, INT32U count);

/***********************************************************************************
* Function: AT45DBXX_ReadPage;
*
* Description: ��ҳ��ȡFLASH������;
*              
* Input:  *p, Ҫ��ȡ���ݴ洢��ָ��; page,��ȡflash���ݵ���ʼҳ;  count, Ҫ�������ݵ�ҳ��;
*         page/count+page��Χ: 0~4095/8191(AT45DB161/AT45DB321); 
*
* Output: *p, ���ݴ洢��ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ÿҳ512�ֽ�;
************************************************************************************/
INT32S AT45DBXX_ReadPage(INT8U *p, INT32U page, INT32U count);

/***********************************************************************************
* Function: AT45DBXX_Write;
*
* Description: д��FLASHһ������;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; addr,д��flash���ݵ���ʼ��ַ;  len,Ҫд�����ݵĳ���;
*         addr��ַ��Χ: 0x000000~0x001fffff/0x003fffff(AT45DB161/AT45DB321);
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������������ַ��Χ��Χ���,���Բ�Ҫ������Χ;
************************************************************************************/
INT32S AT45DBXX_Write(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: AT45DBXX_Read;
*
* Description: ��ȡFLASH������;
*              
* Input:  *p, Ҫ��ȡ���ݴ洢��ָ��; addr, �ڲ�FLASH��ʼ��ַ;  len,Ҫ��ȡ���ݵĳ���;
*         addr��ַ��Χ: 0x000000~0x001fffff/0x003fffff(AT45DB161/AT45DB321);
*
* Output: *p, ���ݴ洢��ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������������ַ��Χ��Χ���,���Բ�Ҫ������Χ;
************************************************************************************/
INT32S AT45DBXX_Read(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: AT45DBXX_Ctrl;
*
* Description: SPI Flash�������;
* 
* Input:  Cmd,  SPI Flash�������
*                CMD_AT45DBXX_PAGE_ERASE:      ����ҳ;  ParaΪҳ��
*                CMD_AT45DBXX_BLOCK_ERASE:     ����4KB��, 8ҳ; ParaΪ����
*                CMD_AT45DBXX_SECTOR_ERASE:    ����128KB����, 32�飬256ҳ; ParaΪ������  
*                CMD_AT45DBXX_CHIP_ERASE:      ��������оƬ;  ParaΪ0
*                CMD_AT45DBXX_RDID:            ��ȡ���̼�����ID; ParaΪ0
*         Para��SPI Flash������Ʋ���, �ο�����˵��
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������; �з��ص��������Ӧ����;
*
* Note:   none;
************************************************************************************/
INT32S AT45DBXX_Ctrl(INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
