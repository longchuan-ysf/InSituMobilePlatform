/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: NFlash.h
* Project  : STM32F107VC/103VE/103ZE/407VEģ��������
* Processor: STM32F107VC/103VE/103ZE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����Nand Flash��д��������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S NFlash_Init(NFLASH_PARA *pPara);
*          2. INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);
*          3. INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);
*          4. INT32U NFlash_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __NAND_FLASH_H 
#define __NAND_FLASH_H

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// ECCҳ���С����
#define NFLASH_ECCSIZE_256   256  // Nand Flash ECCҳ���С: 256�ֽ�
#define NFLASH_ECCSIZE_512   512  // Nand Flash ECCҳ���С: 512�ֽ�
#define NFLASH_ECCSIZE_1024  1024 // Nand Flash ECCҳ���С: 1024�ֽ�
#define NFLASH_ECCSIZE_2048  2048 // Nand Flash ECCҳ���С: 2048�ֽ�
#define NFLASH_ECCSIZE_4096  4096 // Nand Flash ECCҳ���С: 4096�ֽ�
#define NFLASH_ECCSIZE_8192  8192 // Nand Flash ECCҳ���С: 8192�ֽ�
    
// Flag������־����
typedef struct
{
    INT16U  Flag;           // ������־
    INT16U  BlkNum;         // Nand Flash �ܿ���
    INT16U  PagePerBlk;     // Nand Flash ÿ�������ҳ�� 
    INT16U  PageSize;       // ҳ��С 
    INT16U  PageNum;        // ��ҳ��
    INT16U  BadBlkNum;      // ��������
    INT8U   *pBadBlkFlag;   // ������ָ��
    INT16U  *pBadTab;	    // �����滻��ָ��
    INT8U   *pBlkBuf;       // �黺��ָ��
    INT8U   *pBlkSpareBuf;  // ��������򻺴�ָ��
}NFLASH_PARA;

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// NFlash_Ctrl() ���������
#define CMD_NFLASH_SYNC          0 	 // Nand Flashͬ������
#define CMD_NFLASH_BADBLK        1 	 // Nand Flash���鴦��, ������NFlash_APPInit()��, �������NFlash_Ctrl(CMD_NFLASH_BADBLK, 0)����������
#define CMD_NFLASH_STATUS        2 	 // ��ȡNand Flash״̬
#define CMD_NFLASH_SECTOR_COUNT  3   // ��ȡNand Flash��������
#define CMD_NFLASH_SECTOR_SIZE   4   // ��ȡNand Flash������С
#define CMD_NFLASH_BLOCK_SIZE    5   // ��ȡ���С(����������������)
#define CMD_NFLASH_RDID          6 	 // ��ȡ���̼�����ID, ��������IDָ��,5���ֽ�
#define CMD_NFLASH_FORMAT        7 	 // ��ʽ��оƬ

/*************************************************************************************/
//
// 				Nand FlashӲ����������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: NFlash_Init;
*
* Description: Nand Flash��ʼ������;
*              
* Input:  *pPara, ��ʼ������ָ��;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S NFlash_Init(NFLASH_PARA *pPara);

/***********************************************************************************
* Function: NFlash_ReadSector;
*
* Description: ��������ȡNand Flash������;
*              
* Input:  *p, Ҫ��ȡ���ݴ洢��ָ��; sector,��ȡflash���ݵ���ʼ����;  count, Ҫ�������ݵ�������;
*
* Output: *p, ���ݴ洢��ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ÿ������512�ֽ�, ������ֻ��Ӧ����FATFS��diskio.c�е���;
************************************************************************************/
INT32S NFlash_ReadSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: NFlash_WriteSector;
*
* Description: ������д��Nand Flash����;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; sector,д��flash���ݵ���ʼ����; count, Ҫд�����ݵ�������;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ÿ������512�ֽ�, ������ֻ��Ӧ����FATFS��diskio.c�е���;
************************************************************************************/
INT32S NFlash_WriteSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: NFlash_Ctrl;
*
* Description: NFlash���ƺ���;
* 
* Input:  Cmd,  ��������:  
*               CMD_NFLASH_SYNC:          Nand Flashͬ������
*               CMD_NFLASH_BADBLK:        Nand Flash���鴦��, ������NFlash_APPInit()��, �������NFlash_Ctrl(CMD_NFLASH_BADBLK, 0)����������
*               CMD_NFLASH_STATUS:        ��ȡNand Flash״̬
*               CMD_NFLASH_SECTOR_COUNT:  ��ȡNand Flash��������
*               CMD_NFLASH_SECTOR_SIZE:   ��ȡNand Flash������С
*               CMD_NFLASH_BLOCK_SIZE:    ��ȡ���С(����������������)
*               CMD_NFLASH_RDID:          ��ȡ���̼�����ID, ��������IDָ��,5���ֽ�
*               CMD_NFLASH_FORMAT:        ��ʽ��оƬ
*         Para��������Ʋ���;
*
* Output: none;
*          		
* Return: �������ͬ, ���ز�ͬ����; ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32U NFlash_Ctrl(INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
